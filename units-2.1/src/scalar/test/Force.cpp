//
// $Id: Force.cpp,v 1.5.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Force class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Mass.h"
#include "Acceleration.h"
#include "Force.h"

 
using namespace std;
using namespace Units;


//
// Test the API to the Force class.
//
bool Force_test()
{
  bool status = Unit_Tester<NewtonsForce>::genericTest("Force");


  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Force::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(NewtonsForce(2.3), "2.3 N");
  OSTREAM_TEST(PoundsForce(2.3),  "2.3 lb");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Force from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Force::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "               Expected " << value_ << ", got " \
	   << To(from) << '.' << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(PoundsForce(1.0),        PoundsForce,  1.0);
  CONVERSION_TEST(PoundsForce(1.0),        NewtonsForce, 4.4482216);

  CONVERSION_TEST(NewtonsForce(4.4482216), PoundsForce,  1.0);
  CONVERSION_TEST(NewtonsForce(1.0),       NewtonsForce, 1.0);


#define COMPOSITE_TEST(F, M, A) \
  { \
    if (!similar(F(1), M(1)*A)) \
    { \
      cerr << "Force::test(): " \
	   << #F " != " #M "*" #A "." << endl; \
      cerr << "               Expected " << F(1) << ", but got " \
	   << F(M(1)*A) << '.' << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(NewtonsForce, KilogramsMass, MetersSecondAcceleration(1));
  COMPOSITE_TEST(PoundsForce,  PoundsMass,    GsAcceleration(1));


  // Test multiple conversions
 
  if (!similar(PoundsForce(1),
               PoundsForce(NewtonsForce(PoundsForce(1)))
              )
     )
  {
    cerr << "Force::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Mass and Acceleration.

  if (!similar(KilogramsMass(2)*MetersSecondAcceleration(2), NewtonsForce(4)))
  {
    cerr << "Force::test(): operator*(Mass, Acceleration) failed." << endl;
    status = false;
  }

  if (!similar(MetersSecondAcceleration(2)*KilogramsMass(2), NewtonsForce(4)))
  {
    cerr << "Force::test(): operator*(Acceleration, Mass) failed." << endl;
    status = false;
  }

  if (!similar(NewtonsForce(4)/MetersSecondAcceleration(2), KilogramsMass(2)))
  {
    cerr << "Force::test(): operator/(Acceleration) failed." << endl;
    status = false;
  }

  if (!similar(NewtonsForce(4)/KilogramsMass(2), MetersSecondAcceleration(2)))
  {
    cerr << "Force::test(): operator/(Mass) failed." << endl;
    status = false;
  }


  return status;
}
