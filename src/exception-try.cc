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
    std::vector<int> *myData;

public:

    Succeeds() : myData(new std::vector<int>) { }

    virtual ~Succeeds()
    {
        delete myData;
        myData = NULL;
    }
};


// A class whose ctor throws
class Throws
{
private:
    std::vector<int> *myData;

public:

    Throws() : myData(NULL)
    {
        // Simulate ctor failure
        throw "Throws::Throws() failed!";
        
        myData = new std::vector<int>;
    }

    virtual ~Throws()
    {
        delete myData;
        myData = NULL;
    }
};


class ExceptionNoleak
{
private:

    Succeeds *mySucceeds;
    Throws   *myThrows;

public:

    ExceptionNoleak() : mySucceeds(new Succeeds), myThrows(NULL)
    {
        try {
            myThrows = new Throws;
        }
        catch (...) {
            delete mySucceeds;
            mySucceeds = NULL;

            throw;
        }
    }

    virtual ~ExceptionNoleak()
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
        ExceptionNoleak noleak;
    }
    catch (const char *err) {
        std::cout << "Caught exception '" << err << "'" << std::endl;
    }

    return 0;
}
