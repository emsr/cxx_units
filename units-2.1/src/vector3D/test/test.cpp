//
// $Id: test.cpp,v 1.4.4.5 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Test all the 3D vector library components.
//

#include <iostream>
#include <string>

#include "Vector3D_test.cpp"
#include "Direction3D_test.cpp"
#include "QuaternionRotation3D_test.cpp"
#include "MatrixRotation3D_test.cpp"
#include "Length3D.h"
#include "Speed3D.h"
#include "Acceleration3D.h"
#include "AngularSpeed3D.h"
#include "AngularAcceleration3D.h"
#include "Force3D.h"
#include "Torque3D.h"


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

bool Length3D_test();
bool Speed3D_test();
bool Acceleration3D_test();
bool AngularSpeed3D_test();
bool AngularAcceleration3D_test();
bool Force3D_test();
bool Torque3D_test();


ClassTest classTestList[] =
{
  ClassTest("Vector3D<double>",      &Vector3D<double>      ::test),
  ClassTest("Vector3D<float>",       &Vector3D<float>       ::test),
  ClassTest("dDirection3D",          &dDirection3D          ::test),
  ClassTest("fDirection3D",          &fDirection3D          ::test),
  ClassTest("dQuaternionRotation3D", &dQuaternionRotation3D ::test),
  ClassTest("fQuaternionRotation3D", &fQuaternionRotation3D ::test),
  ClassTest("dMatrixRotation3D",     &dMatrixRotation3D     ::test),
  ClassTest("fMatrixRotation3D",     &fMatrixRotation3D     ::test),
  ClassTest("Length3D",              &Length3D_test),
  ClassTest("Speed3D",               &Speed3D_test),
  ClassTest("Acceleration3D",        &Acceleration3D_test),
  ClassTest("AngularSpeed3D",        &AngularSpeed3D_test),
  ClassTest("AngularAcceleration3D", &AngularAcceleration3D_test),
  ClassTest("Force3D",               &Force3D_test),
  ClassTest("Torque3D",              &Torque3D_test)
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
