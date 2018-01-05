//
// $Id: Acceleration.cpp,v 1.4.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Acceleration class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Length.h"
#include "Time.h"
#include "Speed.h"
#include "Acceleration.h"


using namespace std;
using namespace Units;


//
// Test the API to the Acceleration class.
//
bool Acceleration_test()
{
  bool status = Unit_Tester<MetersSecondAcceleration>::genericTest("Acceleration");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(L, T, value, output) \
  { \
    ostringstream testStream; \
    testStream << AccelerationFormat<L, T>((L(value)/T(1))/T(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "Acceleration::test(): " \
	   << "operator<<(ostream, AccelerationFormat<" #L ", " #T ">(" \
	   << #L "(" #value ")/" #T "(1)^2)) failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(FeetLength, SecondsTime, 2.3, "2.3 ft/s^2");
  OSTREAM_FORMAT_TEST(MetersLength, SecondsTime, 2.3, "2.3 m/s^2");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, SecondsTime, 2.3, "2.3 nmi/s^2");

  OSTREAM_FORMAT_TEST(FeetLength, MinutesTime, 2.3, "2.3 ft/min^2");
  OSTREAM_FORMAT_TEST(MetersLength, MinutesTime, 2.3, "2.3 m/min^2");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, MinutesTime, 2.3, "2.3 nmi/min^2");

  OSTREAM_FORMAT_TEST(FeetLength, HoursTime, 2.3, "2.3 ft/hr^2");
  OSTREAM_FORMAT_TEST(MetersLength, HoursTime, 2.3, "2.3 m/hr^2");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, HoursTime, 2.3, "2.3 nmi/hr^2");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Acceleration::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MetersSecondAcceleration(2.3), "2.3 m/s^2");
  OSTREAM_TEST(FeetSecondAcceleration(2.3), "2.3 ft/s^2");
  OSTREAM_TEST(GsAcceleration(2.3), "2.3 g");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    Acceleration from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Acceleration::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "                      Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(MetersSecondAcceleration(1),
                         MetersSecondAcceleration,    1);

  DOUBLE_CONVERSION_TEST(FeetSecondAcceleration(1),
                         MetersSecondAcceleration,    0.3048);

  DOUBLE_CONVERSION_TEST(GsAcceleration(1),
                         MetersSecondAcceleration,    9.80665);


#define COMPOSITE_TEST(A, S, T) \
  { \
    if (!similar(A(1), S(1)/T(1))) \
    { \
      cerr << "Acceleration::test(): " \
	   << #A " != " #S "/" #T "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(MetersSecondAcceleration, MetersPerSecondSpeed, SecondsTime);
  COMPOSITE_TEST(FeetSecondAcceleration,   FeetPerSecondSpeed,   SecondsTime);


#define DOUBLE_FORMAT_CONVERSION_TEST(L, T, value_) \
  { \
    Acceleration acceleration((L(value_)/T(1))/T(1)); \
    if (fabs(AccelerationFormat<L, T>(acceleration).value() - value_) > 1e-6) \
    { \
      cerr << "Acceleration::test(): " \
	   << "double conversion for " #L "/" #T " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(FeetLength, SecondsTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MetersLength, SecondsTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NauticalMilesLength, SecondsTime, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(FeetLength, MinutesTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MetersLength, MinutesTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NauticalMilesLength, MinutesTime, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(FeetLength, HoursTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MetersLength, HoursTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NauticalMilesLength, HoursTime, 2.3);

  // Test multiple conversions

  if (!similar(MetersSecondAcceleration(1),
               MetersSecondAcceleration(FeetSecondAcceleration(
                 GsAcceleration(MetersSecondAcceleration(1))))
              )
     )
  {
    cerr << "Acceleration::test(): multiple conversions failed." << endl;
    status = false;
  }

  // Test interaction with Time and Speed.

  if (!similar(MetersSecondAcceleration(2)*SecondsTime(2),
               MetersPerSecondSpeed(4)))
  {
    cerr << "Acceleration::test(): operator*(Time) failed." << endl;
    status = false;
  }

  if (!similar(SecondsTime(2)*MetersSecondAcceleration(2),
               MetersPerSecondSpeed(4)))
  {
    cerr << "Acceleration::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }

  if (!similar(MetersPerSecondSpeed(4)/SecondsTime(2),
               MetersSecondAcceleration(2)))
  {
    cerr << "Acceleration::test(): operator/(Length, Time) failed." << endl;
    status = false;
  }
 
  if (!similar(MetersPerSecondSpeed(4)/MetersSecondAcceleration(2),
               SecondsTime(2)))
  {
    cerr << "Acceleration::test(): operator/(Length, Speed) failed." << endl;
    status = false;
  }


  return status;
}
