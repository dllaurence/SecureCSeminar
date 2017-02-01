/*
  exception-pattern1-nogoto.c

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  "C Exception Pattern" example using Exception interface pattern 1,
  modified to avoid goto.

  This satisfies a request for a version which will fly by typical
  coding standards.  There are multiple alternative proposals
  depending on the strictness of the coding standards, importance of
  performance vs clarity, and your personal opinions on what actually
  is clear and what isn't.  Pick your poison.

  NONE of these versions are recommended unless you have coding
  standards or pointy-haired bosses that forbid goto without
  understanding the idiomatic exceptions in C and you can't fix them
  or the pointy-haired boss.

  WARNING: these haven't been compiled, I'm sure there are small
  syntactic errors.  This is only for trying out ideas.
*/


/**********************************************************************
  Versions constructed with a single control structure

  Nested ifs are the only structured control structure in C capable of the
  correct behavior in a single structure (essentially the ability to
  conditionally not execute the central part of the structure but pick up
  execution after the removed section, so this group only has one basic idea.
 **********************************************************************/

/**********************************************************************
  Version 1

  A literal structured translation of the canonical implementation.

  Advantages:

  1. Probably compiles to about the same assembly as the original, and
  so is probably just as efficient.

  2. Uses only if, so should pass every set of coding standards in the
  world in terms of language constructs used.

  3. Actually does a decent job of showing the control flow structure
  in spite of the nesting depth and length.  I guess that's a point
  for the structured programming crowd.

  Disadvantages: Holy Nested If Blocks, Batman!

  Far less readable and maintainable:

  1. The actual work is inside a deeply nested structure (imagine a
  case where there are half a dozen resources to be acquired).  Will
  not pass coding standards that limit nesting depth ("if you need
  more than 3 levels of indentation, you're screwed anyway, and should
  fix your program" -- Linus Torvalds).

  In this one case it wouldn't be entirely crazy to de-structure the
  whole thing and *not* indent the blocks that only serve to hide the
  assembly language jumps (you'd still indent blocks in the actual
  work section normally), but I can't imagine the ensuing howls of
  rage.  Anyone who would except that as a legitimate exception would
  accept the canonical version in the first place.

  2. The blocks are long enough that the eye cannot easily match up
  corresponding allocation and deallocation code.  In serious code
  they are liable to more than a screenful, which is a pretty good
  measure of when a block is too long.

  3. (2) is made worse by the fact that the corresponding allocation
  and deallocation code appears at different indent levels.

  In spite of all that whining, I don't mind this nearly as much as I
  thought I would.  The biggest objection is just that the length of the
  blocks and the depth of the nesting is going to make it harder to
  match everything up and maintain.  And, of course, more than two
  resources are going to make it much worse.
 **********************************************************************/


int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

        MoreStuff *more_stuff = NULL;
        if ( (!(err = get_more_stuff(...))) ) {

            // Do work

            // ...

            // On error during the main work section, need to ensure all
            // resources are released without committing
            if (!err) {
                // ...

                // We don't set until completely finished so the function either
                // succeeds or does nothing at all.

                // Commit result
                *result = <final result>;
            }

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************
  Version 1a

  Exactly the same as 1, but as an experiment in layout destructure it by
  removing the indentation so that conceptually it is one large control
  structure rather than nested ifs (there is precedent; this is precisely how
  everyone indents "else if" in C, which is syntactically nested ifs but
  conceptually a single compound if.

  While I like the look more than I thought I would, I think it's not practical
  since keeping everything balanced while writing and maintaining it will be
  too hard.

 **********************************************************************/


int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

    MoreStuff *more_stuff = NULL;
    if ( (!(err = get_more_stuff(...))) ) {

    // Do work

    // ...

    // On error during the main work section, need to ensure all
    // resources are released without committing
    if (!err) {

    // ...

    // We don't set until completely finished so the function either
    // succeeds or does nothing at all.

    // Commit result
    *result = <final result>;
    }

    free(more_stuff);
    more_stuff = NULL;
    }

    free(stuff);
    stuff = NULL;
    }

    return err;
}


/**********************************************************************

  Versions constructed with more than one control structure in series

  The concept behind these versions is as follows:

  Observation: the pattern is basically a chiastic structure or arch form that
  consists of a block of code with multiple exits (the aquisition, work, and
  commit sections) followed by a block with multiple entrances (the release
  section).  The canonical pattern combines these into a single large control
  structure that outlines the entire function.  Naturally if and goto can do
  it, since they can mimic any control structure.  Because the structure is
  inherently nested, ifs can also do it, as in alternative 1.

  To implement it with standard constructs and not create such long, deep
  nesting, we have to break it into at least two control structures with both a
  C construct with multiple exits and one with multiple entrances.  (I suppose
  that's why this technique isn't universal in every language: those are
  precisely the properties that Structured Programming forbade.) Since the
  entrance chosen in the deallocation construct depends on the exit chosen in
  the allocation/work construct (because the true structure is inherently
  nested), we'll also have to use a variable to communicate between the
  structures.  This is a disadvantage, though perhaps not a large one.

  Since we must create a variable to track allocations anyway, it turns out
  that we can factor out further pieces, at the cost of more tests.

  C structures with multiple exits:

      Nested ifs (effectively)
      Functions
      Loops

      Switch (but has no advantage over using a loop, so we'll ignore)

  C structures with multiple entrances:

      Nested ifs (effectively)
      Switch

  There are essentially six ways to do this: choose one from column A for the
  acquisition/work/commit section and one from column B for the release
  section.

 **********************************************************************/


/**********************************************************************
  Version 2--ifs

  For easy comparison with Version 1, here is how this works with nested
  ifs for both blocks.

  Advantages: the only thing we've accomplished is shortening the long
  if blocks.

  Disadvantages:
      * The allocated variable, as with all multiple-structure versions.
      * The blocks are still very long--the release section we've
        factored out was the shortest piece.
      * Extra tests, not just the minimum single test for
 **********************************************************************/


int foo(float *result)
{
    int err = 0;
    unsigned allocated = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

        ++allocated;

        MoreStuff *more_stuff = NULL;
        if ( (!(err = get_more_stuff(...))) ) {

            ++allocated;

            // Do work

            // ...

            // On error during the main work section, need to ensure all
            // resources are released without committing
            if (!err) {
                // ...

                // We don't set until completely finished so the function either
                // succeeds or does nothing at all.

                // Commit result
                *result = <final result>;
            }
        }
    }

    // Release acquired resources
    if (acquired > 0) {

        if (acquired > 1) {

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************
  Version 3--sneaky ifs

  The one place every set of coding standards will permit not indenting
  to reflect the syntax is else if, so here we take advantage of that
  for some perfectly legal non-indentation.  Of course, we have to abuse
  the comma operator to do it, but that might be too obscure for your
  coding standards to forbid.  We also had to have indentation in the
  work section, since this only works for resources that take a single
  function call to allocate.  Still, it does reduce the indentation.

 **********************************************************************/


int foo(float *result)
{
    int err = 0;
    unsigned allocated = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    MoreStuff *more_stuff = NULL;

    if ( (err = get_stuff(&stuff)) );
    else if ( (++allocated, err = get_more_stuff(...)) );
    else {
        ++allocated;

        // Do work

        // ...

        // On error during the main work section, need to ensure all
        // resources are released without committing
        if (!err) {
            // ...

            // We don't set until completely finished so the function either
            // succeeds or does nothing at all.

            // Commit result
            *result = <final result>;
        }
    }

    // Release acquired resources
    if (acquired > 0) {

        if (acquired > 1) {

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************
  Version 3--naked cheating

  The concept behind this version is as follows:

  Observation: the pattern is basically a chiastic structure or arch form that
  consists of a block of code with multiple exits (the aquisition, work, and
  commit sections) followed by a block with multiple entrances (the release
  section) all bracketing the commit section.  The canonical pattern combines
  these into a single large control structure that outlines the entire
  function.  Naturally if and goto can do it, since they can mimic any control
  structure.  Because the structure is inherently nested, ifs can also do it,
  as in alternative 1.

  To implement it with standard constructs and not create such long, deep
  nesting, we have to break it in two with both a C construct with multiple
  exits and one with multiple entrances.  (I suppose that's why this technique
  isn't universal in every language: those are precisely the properties that
  Structured Programming forbade.) Since the entrance chosen in the
  deallocation construct depends on the exit chosen in the allocation/work
  construct (because the true structure is inherently nested), we'll also have
  to use a variable to communicate between the structures.

  C structures with multiple exits:

      Nested ifs (effectively)
      Functions
      Loops

      Switch (but has no advantage over using a loop, so we'll ignore)

  C structures with multiple entrances:

      Nested ifs (effectively)
      Switch`

 **********************************************************************/


int foo(float *result)
{
    int err = 0;
    unsigned allocated = 0;

    do {
        // Acquire resources
        Stuff *stuff = NULL;
        if ( (err = get_stuff(&stuff)) ) {
            break;
        }

        ++allocated;

        MoreStuff *more_stuff = NULL;
        if ( (err = get_more_stuff(...)) ) {
            break;
        }

        ++allocated;

        // Do work

        // ...

        // On error need to ensure all resources are released
        if (err) {
            break;
        }

        // ...

        // We don't set until completely finished so the function either
        // succeeds or does nothing at all.

        // Commit result
        *result = <final result>;

    } while (0);


    switch (allocated) {
    2:
        // Release resources
        free(more_stuff);
        more_stuff = NULL;
        // fallthrough
    1:
        // Partial tear-down
        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************

  Versions constructed with more than one nested control structure

  The concept here is that while it requires nested ifs or gotos to match
  allocation and cleanup, the work portion has no additional cleanup
  and therefore only requires multiple exits.  Therefore we can nest
  any structure with that property inside ifs for acquisition and
  release.  However, nested ifs just reproduces the pure if form, so
  the only choices are loops that we can break out of and functions.

 **********************************************************************/


/**********************************************************************
  Block inside--ideal, illegal form

  This would be the cleanest, we just create an inner block and break out
  of it on error.  If only it were legal C.
 **********************************************************************/


int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

        MoreStuff *more_stuff = NULL;
        if ( (!(err = get_more_stuff(...))) ) {

            {
                // Do work

                // ...

                // On error during the main work section, need to ensure all
                // resources are released without committing
                if (err) {
                    break;
                }

                // ...

                // We don't set until completely finished so the function either
                // succeeds or does nothing at all.

                // Commit result
                *result = <final result>;
            }

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************
  Loop inside

  This is the standard way to turn a block into a statement, and it
  happens to allow break as well.

  Mainly, we've reduced the nesting level in the case of errors in
  the work section, which is modest but worthwhile if it has a lot of
  error handling to do.

 **********************************************************************/


int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

        MoreStuff *more_stuff = NULL;
        if ( (!(err = get_more_stuff(...))) ) {

            do {
                // Do work

                // ...

                // On error during the main work section, need to ensure all
                // resources are released without committing
                if (err) {
                    break;
                }

                // ...

                // We don't set until completely finished so the function either
                // succeeds or does nothing at all.

                // Commit result
                *result = <final result>;
            } while (0);

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


/**********************************************************************
  Factor out the work into a function

  Advantages

    * Factors acquisition and release out of the main body of the work,
      which is good design.  The work function can be written assuming all
      allocation succeeds, which is what we want from language exception
      handling constructs.  Basically the body function is the function
      we actually wanted to write in the first place.

    * Shortens the if blocks greatly, which is a major win.  Now the
      indentation is doing what it is supposed to do, and the correspondence
      between allocation and deallocation is evident.

    * Slight reduction in nesting depth, in that there are only indents
      for each acquision and nothing else.

    * No bookkeeping "allocated" variable.

    * Widely legal; the early returns are probably acceptible most places
      where 'break' is not.  Even if early return is forbidden, we're no
      worse off than before and can fix by the methods identified earlier;
      factor out more functions.

    * Deep nesting prohibitions are fixable by the same method--factor
      out extra functions.  At the extreme, one could make an extra function
      per allocation and never indent.

  Disadvantages

    * Extra function call.

  I think this is the preferred non-goto solution, and not a bad alternative at
  that.

 **********************************************************************/


int foo(float *result)
{
    int err = 0;

    // Acquire resources
    Stuff *stuff = NULL;
    if ( (!(err = get_stuff(&stuff))) ) {

        MoreStuff *more_stuff = NULL;
        if ( (!(err = get_more_stuff(...))) ) {

            err = foo_body(result, stuff, more_stuff);

            free(more_stuff);
            more_stuff = NULL;
        }

        free(stuff);
        stuff = NULL;
    }

    return err;
}


static int foo_body(float *result, Stuff *stuff, MoreStuff *more_stuff) {
    // Do work

    // ...

    // On error during the main work section, need to ensure all
    // resources are released without committing
    if (err) {
        return err;
    }

    // ...

    *result = <final result>;
}
