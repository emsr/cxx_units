//
// $Id: Torque.cpp,v 1.6.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Torque class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Torque.h"
#include "Force.h"
#include "Length.h"
#include "Inertia.h"
#include "Area.h"
#include "AngularAcceleration.h"

 
using namespace std;
using namespace Units;


//
// Test the API to the Torque class.
//
bool Torque_test()
{
  bool status = Unit_Tester<NewtonMeterTorque>::genericTest("Torque");


  // Test ostream ops.

#define OSTREAM_TEST(F, L, value, output) \
  { \
    ostringstream testStream; \
    testStream << TorqueFormat<F, L>(F(value)*L(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "Torque::test(): " \
	   << "operator<<(ostream, TorqueFormat<" #F ", " #L ">(" \
	   << #F "(" #value ")*" #L "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(NewtonsForce, FeetLength, 2.3, "2.3 N-ft");
  OSTREAM_TEST(NewtonsForce, MetersLength, 2.3, "2.3 N-m");

  OSTREAM_TEST(PoundsForce, FeetLength, 2.3, "2.3 lb-ft");
  OSTREAM_TEST(PoundsForce, MetersLength, 2.3, "2.3 lb-m");


#define DOUBLE_CONVERSION_TEST(F, L, value_) \
  { \
    Torque torque (F(value_)*L(1)); \
    if (fabs(TorqueFormat<F, L>(torque).value() - value_) > 1e-6) \
    { \
      cerr << "Torque::test(): " \
	   << "double conversion for " #F "-" #L " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(NewtonsForce, FeetLength, 2.3);
  DOUBLE_CONVERSION_TEST(NewtonsForce, MetersLength, 2.3);

  DOUBLE_CONVERSION_TEST(PoundsForce, FeetLength, 2.3);
  DOUBLE_CONVERSION_TEST(PoundsForce, MetersLength, 2.3);


  // Test interaction with length and force.

  Length length = MetersLength(1);
  Torque torque = NewtonsForce(1.23)*length;

  // Can't really test operator*(Force, Length) directly ...
  // There's nothing with which to compare the answer.

  if (!similar(torque/length, NewtonsForce(1.23)))
  {
    cerr << "Torque::test(): operator*(Torque, Length) failed." << endl;
    status = false;
  }
  if (!similar(torque/NewtonsForce(1.23), length))
  {
    cerr << "Torque::test(): operator/(Force, Torque) failed." << endl;
    status = false;
  }


  // Test interaction with Inertia and AngularAcceleration.

  Inertia             inertia      = KilogramsMass(2)*MetersArea(1);
  AngularAcceleration acceleration = RadiansSecondAngularAcceleration(2);
  torque = NewtonsForce(4)*MetersLength(1);

  if (!similar(inertia*acceleration, torque))
  {
    cerr << "Torque::test(): operator*(Inertia, AngularAcceleration) failed."
         << endl;
    status = false;
  }

  if (!similar(acceleration*inertia, torque))
  {
    cerr << "Torque::test(): operator*(AngularAcceleration, Inertia) failed."
         << endl;
    status = false;
  }

#if 0
  // DEPRECATED
  if (!similar(torque/acceleration, inertia))
  {
    cerr << "Torque::test(): operator/(AngularAcceleration) failed." << endl;
    status = false;
  }

  // DEPRECATED
  if (!similar(torque/inertia, acceleration))
  {
    cerr << "Torque::test(): operator/(Inertia) failed." << endl;
    status = false;
  }
#endif


  return status;
}
