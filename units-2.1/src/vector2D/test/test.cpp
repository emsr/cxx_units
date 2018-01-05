//
// $Id: test.cpp,v 1.1.4.7 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Test all the 2D vector library components.
//

#include <iostream>
#include <string>
#include "Vector2D_test.cpp"
#include "Direction2D_test.cpp"
#include "Rotation2D_test.cpp"
#include "Length2D.h"
#include "Speed2D.h"
#include "Acceleration2D.h"
#include "Force2D.h"
#include "Angle2D.h"


using namespace Units;
using namespace std;



struct ClassTest
{
  string   className;
  bool   (*testFunc)();

  ClassTest(string   className_,
            bool   (*testFunc_)()):
    className(className_),
    testFunc(testFunc_)
  {}
};

bool Length2D_test();
bool Speed2D_test();
bool Acceleration2D_test();
bool Force2D_test();
bool Angle2D_test();

ClassTest classTestList[] =
{
  ClassTest("Vector2D<double>", &Vector2D<double> ::test),
  ClassTest("Vector2D<float>",  &Vector2D<float>  ::test),
  ClassTest("dDirection2D",     &dDirection2D     ::test),
  ClassTest("fDirection2D",     &fDirection2D     ::test),
  ClassTest("dRotation2D",      &dRotation2D      ::test),
  ClassTest("fRotation2D",      &fRotation2D      ::test),
  ClassTest("Length2D",         &Length2D_test),
  ClassTest("Speed2D",          &Speed2D_test),
  ClassTest("Acceleration2D",   &Acceleration2D_test),
  ClassTest("Force2D",          &Force2D_test),
  ClassTest("Angle2D",          &Angle2D_test)
};



int main(int    argc,
         char * argv[])
{
  cout << endl;

  //
  // If no arguments were given, default to testing all classes.
  //
  if (argc == 1)
  {
    unsigned numFailed = 0;
    for (unsigned i = 0; i < sizeof(classTestList)/sizeof(ClassTest); i++)
    {
      bool status = (*classTestList[i].testFunc)();
      cout << classTestList[i].className << "::test() "
           << (status ? "passed" : "failed") << '.' << endl;
      if (!status)
      {
        numFailed++;
      }
    }

    cout << "\n************************************\n" << endl;
    cout << "   " << numFailed << " classes failed.\n" << endl;

    return 0;
  }

  //
  // Loop through each argument and run its test from the class table.
  //
  for (int argument = 1; argument < argc; argument++)
  {
    for (unsigned i = 0; i < sizeof(classTestList)/sizeof(ClassTest); i++)
    {
      if (classTestList[i].className == argv[argument])
      {
        bool status = (*classTestList[i].testFunc)();
        cout << classTestList[i].className << "::test() "
             << (status ? "passed" : "failed") << '.' << endl;
      }
    }
  }

  return 0;
}
