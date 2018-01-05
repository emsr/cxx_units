//
// $Id: AngularSpeed.cpp,v 1.5.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the AngularSpeed class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Angle.h"
#include "Time.h"
#include "Length.h"
#include "Speed.h"
#include "AngularSpeed.h"


using namespace std;
using namespace Units;


//
// Test the API to the AngularSpeed class.
//
bool AngularSpeed_test()
{
  bool status = Unit_Tester<RadiansPerSecondAngularSpeed>::genericTest("AngularSpeed");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(L, T, value, output) \
  { \
    ostringstream testStream; \
    testStream << AngularSpeedFormat<L, T>(L(value)/T(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularSpeed::test(): " \
	   << "operator<<(ostream, AngularSpeedFormat<" #L ", " #T ">(" #L "(" #value \
              ")/" #T "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(DegreesAngle, SecondsTime, 2.3, "2.3 deg/s");
  OSTREAM_FORMAT_TEST(RadiansAngle, SecondsTime, 2.3, "2.3 rad/s");

  OSTREAM_FORMAT_TEST(DegreesAngle, MinutesTime, 2.3, "2.3 deg/min");
  OSTREAM_FORMAT_TEST(RadiansAngle, MinutesTime, 2.3, "2.3 rad/min");

  OSTREAM_FORMAT_TEST(DegreesAngle, HoursTime,   2.3, "2.3 deg/hr");
  OSTREAM_FORMAT_TEST(RadiansAngle, HoursTime,   2.3, "2.3 rad/hr");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularSpeed::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(RpmAngularSpeed(2.3), "2.3 rpm");


#define DOUBLE_FORMAT_CONVERSION_TEST(L, T, value_) \
  { \
    AngularSpeed speed(L(value_)/T(1)); \
    if (fabs(AngularSpeedFormat<L, T>(speed).value() - value_) > 1e-6) \
    { \
      cerr << "AngularSpeed::test(): " \
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


#define COMPOSITE_TEST(S, L, T) \
  { \
    if (!similar(S(1), L/T(1))) \
    { \
      cerr << "AngularSpeed::test(): " \
	   << #S " != " #L "/" #T "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(RpmAngularSpeed, DegreesAngle(360), MinutesTime);


  // Test interaction with Time and Angle.

  AngularSpeed speed = DegreesAngle(1.0)/SecondsTime(1.0);
  Angle angle = speed*SecondsTime(1.0);
  if (fabs(DegreesAngle(angle).value() - 1.0) > 1e-6)
  {
    cerr << "AngularSpeed::test(): operator*(Time) failed." << endl;
    status = false;
  }
  angle = SecondsTime(1.0)*speed;
  if (fabs(DegreesAngle(angle).value() - 1.0) > 1e-6)
  {
    cerr << "AngularSpeed::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }

  angle = DegreesAngle(1.0);
  speed = angle/SecondsTime(1.0);
  if (fabs(AngularSpeedFormat<DegreesAngle,
                              SecondsTime>(speed).value() - 1.0) > 1e-6)
  {
    cerr << "Angle::test(): operator/(Time) failed." << endl;
    status = false;
  }

  Time time = angle/speed;
  if (fabs(SecondsTime(time).value() - 1.0) > 1e-6)
  {
    cerr << "Angle::test(): operator/(AngularSpeed) failed." << endl;
    status = false;
  }


  //
  // Test interaction with linear Speed.
  //
#define LINSPEED_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    cerr << "Angle::test(): " << #expr " failed." << endl; \
    cerr << "               Expected " << (output) \
	 << ", but got " \
         << SpeedFormat<MetersLength, SecondsTime>(expr) << "." << endl; \
    status = false; \
  }

  LINSPEED_TEST(MetersLength(1) * (DegreesAngle(180)/SecondsTime(1)),
                MetersPerSecondSpeed(M_PI));
  LINSPEED_TEST((DegreesAngle(180)/SecondsTime(1)) * MetersLength(1),
                MetersPerSecondSpeed(M_PI));


  return status;
}
