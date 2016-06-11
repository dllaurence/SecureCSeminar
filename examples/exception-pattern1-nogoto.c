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
*/


/**********************************************************************
  Version 1--a literal structured translation of the canonical
  implementation.

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
  thought I would.
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
