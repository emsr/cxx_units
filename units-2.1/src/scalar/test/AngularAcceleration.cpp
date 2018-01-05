//
// $Id: AngularAcceleration.cpp,v 1.3.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the AngularAcceleration class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "AngularAcceleration.h"
#include "AngularSpeed.h"


using namespace std;
using namespace Units;


//
// Test the API to the AngularAcceleration class.
//
bool AngularAcceleration_test()
{
  bool status = Unit_Tester<RadiansSecondAngularAcceleration>::genericTest("AngularAcceleration");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(L, T, value, output) \
  { \
    ostringstream testStream; \
    testStream << AngularAccelerationFormat<L, T>((L(value)/T(1))/T(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularAcceleration::test(): " \
	   << "operator<<(ostream, AngularAccelerationFormat<" #L ", " #T ">(" \
	   << #L "(" #value ")/" #T "(1)^2)) failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(DegreesAngle, SecondsTime, 2.3, "2.3 deg/s^2");
  OSTREAM_FORMAT_TEST(RadiansAngle, SecondsTime, 2.3, "2.3 rad/s^2");

  OSTREAM_FORMAT_TEST(DegreesAngle, MinutesTime, 2.3, "2.3 deg/min^2");
  OSTREAM_FORMAT_TEST(RadiansAngle, MinutesTime, 2.3, "2.3 rad/min^2");

  OSTREAM_FORMAT_TEST(DegreesAngle, HoursTime,   2.3, "2.3 deg/hr^2");
  OSTREAM_FORMAT_TEST(RadiansAngle, HoursTime,   2.3, "2.3 rad/hr^2");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularAcceleration::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(RadiansSecondAngularAcceleration(2.3), "2.3 rad/s^2");
  OSTREAM_TEST(DegreesSecondAngularAcceleration(2.3), "2.3 deg/s^2");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    AngularAcceleration from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "AngularAcceleration::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "                      Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(RadiansSecondAngularAcceleration(1),
                         RadiansSecondAngularAcceleration, 1);

  DOUBLE_CONVERSION_TEST(DegreesSecondAngularAcceleration(1),
                         RadiansSecondAngularAcceleration, M_PI/180);


#define COMPOSITE_TEST(A, S, T) \
  { \
    if (!similar(A(1), S/T(1))) \
    { \
      cerr << "AngularAcceleration::test(): " \
	   << #A " != " #S "/" #T "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(RadiansSecondAngularAcceleration,
                 (RadiansAngle(1)/SecondsTime(1)), SecondsTime);

  COMPOSITE_TEST(DegreesSecondAngularAcceleration,
                 (DegreesAngle(1)/SecondsTime(1)), SecondsTime);


#define DOUBLE_FORMAT_CONVERSION_TEST(L, T, value_) \
  { \
    AngularAcceleration acceleration((L(value_)/T(1))/T(1)); \
    if (fabs(AngularAccelerationFormat<L, T>(acceleration).value() - value_) > 1e-6) \
    { \
      cerr << "AngularAcceleration::test(): " \
	   << "double conversion for " #L "/" #T " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(DegreesAngle, SecondsTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(RadiansAngle, SecondsTime, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(DegreesAngle, MinutesTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(RadiansAngle, MinutesTime, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(DegreesAngle, HoursTime,   2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(RadiansAngle, HoursTime,   2.3);

  // Test multiple conversions

  if (!similar(RadiansSecondAngularAcceleration(1),
               RadiansSecondAngularAcceleration(DegreesSecondAngularAcceleration(RadiansSecondAngularAcceleration(1)))))
  {
    cerr << "AngularAcceleration::test(): multiple conversions failed." << endl;
    status = false;
  }

  // Test interaction with Time and AngularSpeed.

  if (!similar(DegreesSecondAngularAcceleration(2)*SecondsTime(2),
               RpmAngularSpeed(4*60/360.0)))
  {
    cerr << "AngularAcceleration::test(): operator*(Time) failed." << endl;
    status = false;
  }

  if (!similar(SecondsTime(2)*DegreesSecondAngularAcceleration(2),
               RpmAngularSpeed(4*60/360.0)))
  {
    cerr << "AngularAcceleration::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }

  if (!similar(RpmAngularSpeed(4*60/360.0)/SecondsTime(2),
               DegreesSecondAngularAcceleration(2)))
  {
    cerr << "AngularAcceleration::test(): operator/(Angle, Time) failed." << endl;
    status = false;
  }
 
  if (!similar(RpmAngularSpeed(4*60/360.0)/DegreesSecondAngularAcceleration(2),
               SecondsTime(2)))
  {
    cerr << "AngularAcceleration::test(): operator/(Angle, Speed) failed." << endl;
    status = false;
  }


  return status;
}
