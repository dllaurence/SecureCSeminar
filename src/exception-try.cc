/*
  exception-try.cc

  Copyright Dustin Laurence, 2016.  This file may be used and/or
  redistributed for any purpose in any form.

  Demonstrate a poor solution using try/catch.
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
    char *myData;

public:

    Throws(size_t size) : myData(NULL)
    {
        // Simulate ctor failure
        throw "Throws::Throws() failed!";
        
        myData = new char[size];
    }

    virtual ~Throws()
    {
        delete[] myData;
        myData = NULL;
    }
};


class ExceptionLeak
{
private:

    Succeeds *mySucceeds;
    Throws   *myThrows;

public:

    ExceptionLeak() : mySucceeds(new Succeeds), myThrows(NULL)
    {
        try {
            myThrows = new Throws(100);
        }
        catch (...) {
            delete mySucceeds;
            mySucceeds = NULL;

            throw;
        }
    }

    virtual ~ExceptionLeak()
    {
        delete myThrows;
        myThrows = NULL;

        delete mySucceeds;
        mySucceeds = NULL;
    }
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
