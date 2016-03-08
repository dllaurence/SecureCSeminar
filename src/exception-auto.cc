/*
  exception-auto.cc

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Demonstrate a better solution using std::auto_ptr.
*/


#include <iostream>
#include <memory>
#include <vector>


// A class whose ctor succeeds
class Succeeds
{
private:
    std::auto_ptr<std::vector<int> > myData;

public:

    Succeeds() : myData(new std::vector<int>) { }

    virtual ~Succeeds() { }
};


// A class whose ctor throws
class Throws
{
private:
    std::auto_ptr<std::vector<int> > myData;

public:

    Throws() : myData()
    {
        // Simulate ctor failure
        throw "Throws::Throws() failed!";
        
        myData.reset( new std::vector<int>);
    }

    virtual ~Throws() { }
};


class ExceptionLeak
{
private:

    std::auto_ptr<Succeeds> mySucceeds;
    std::auto_ptr<Throws>   myThrows;

public:

    ExceptionLeak()
        : mySucceeds(new Succeeds),
          myThrows(new Throws)
    { }

    virtual ~ExceptionLeak() { };
};


int main()
{
    try {
        ExceptionLeak leak;
    }
    catch (const char *err) {
        std::cout << "Caught exception '" << err << "'" << std::endl;
    }

    return 0;
}
