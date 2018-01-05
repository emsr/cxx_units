//
// $Id: Speed.cpp,v 1.4.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Speed class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Length.h"
#include "Time.h"
#include "Speed.h"


using namespace std;
using namespace Units;


//
// Test the API to the Speed class.
//
bool Speed_test()
{
  bool status = Unit_Tester<MetersPerSecondSpeed>::genericTest("Speed");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(L, T, value, output) \
  { \
    ostringstream testStream; \
    testStream << SpeedFormat<L, T>(L(value)/T(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "Speed::test(): " \
	   << "operator<<(ostream, SpeedFormat<" #L ", " #T ">(" #L "(" #value \
              ")/" #T "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(FeetLength, SecondsTime, 2.3, "2.3 ft/s");
  OSTREAM_FORMAT_TEST(MetersLength, SecondsTime, 2.3, "2.3 m/s");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, SecondsTime, 2.3, "2.3 nmi/s");

  OSTREAM_FORMAT_TEST(FeetLength, MinutesTime, 2.3, "2.3 ft/min");
  OSTREAM_FORMAT_TEST(MetersLength, MinutesTime, 2.3, "2.3 m/min");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, MinutesTime, 2.3, "2.3 nmi/min");

  OSTREAM_FORMAT_TEST(FeetLength, HoursTime, 2.3, "2.3 ft/hr");
  OSTREAM_FORMAT_TEST(MetersLength, HoursTime, 2.3, "2.3 m/hr");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, HoursTime, 2.3, "2.3 nmi/hr");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Speed::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MetersPerSecondSpeed(2.3),   "2.3 m/s");
  OSTREAM_TEST(FeetPerSecondSpeed(2.3),     "2.3 fps");
  OSTREAM_TEST(KilometersPerHourSpeed(2.3), "2.3 kph");
  OSTREAM_TEST(MilesPerHourSpeed(2.3),      "2.3 mph");
  OSTREAM_TEST(KnotsSpeed(2.3),             "2.3 kts");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    Speed from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "Speed::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "               Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(MetersPerSecondSpeed(1),   
                         MetersPerSecondSpeed,       1);
  DOUBLE_CONVERSION_TEST(FeetPerSecondSpeed(1),     
                         MetersPerSecondSpeed,       0.3048);
  DOUBLE_CONVERSION_TEST(KilometersPerHourSpeed(1), 
                         MetersPerSecondSpeed,       1/3.6);
  DOUBLE_CONVERSION_TEST(MilesPerHourSpeed(1),
			 MetersPerSecondSpeed,       1/2.236936292);
  DOUBLE_CONVERSION_TEST(KnotsSpeed(1),
			 MetersPerSecondSpeed,       1852/3600.0);


#define COMPOSITE_TEST(S, L, T) \
  { \
    if (!similar(S(1), L(1)/T(1))) \
    { \
      cerr << "Speed::test(): " \
	   << #S " != " #L "/" #T "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(MetersPerSecondSpeed,   MetersLength,        SecondsTime);
  COMPOSITE_TEST(FeetPerSecondSpeed,     FeetLength,          SecondsTime);
  COMPOSITE_TEST(KilometersPerHourSpeed, KilometersLength,    HoursTime);
  COMPOSITE_TEST(MilesPerHourSpeed,      StatuteMilesLength,  HoursTime);
  COMPOSITE_TEST(KnotsSpeed,             NauticalMilesLength, HoursTime);


#define DOUBLE_FORMAT_CONVERSION_TEST(L, T, value_) \
  { \
    Speed speed(L(value_)/T(1)); \
    if (fabs(SpeedFormat<L, T>(speed).value() - value_) > 1e-6) \
    { \
      cerr << "Speed::test(): " \
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
 
  if (!similar(MetersPerSecondSpeed(1),
               MetersPerSecondSpeed(FeetPerSecondSpeed(KilometersPerHourSpeed(
                 MilesPerHourSpeed(KnotsSpeed(MetersPerSecondSpeed(1))))))
              )
     )
  {
    cerr << "Speed::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Time and Length.

  if (!similar(MetersPerSecondSpeed(2)*SecondsTime(2), MetersLength(4)))
  {
    cerr << "Speed::test(): operator*(Time) failed." << endl;
    status = false;
  }

  if (!similar(SecondsTime(2)*MetersPerSecondSpeed(2), MetersLength(4)))
  {
    cerr << "Speed::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }

  if (!similar(MetersLength(4)/SecondsTime(2), MetersPerSecondSpeed(2)))
  {
    cerr << "Speed::test(): operator/(Length, Time) failed." << endl;
    status = false;
  }
 
  if (!similar(MetersLength(4)/MetersPerSecondSpeed(2), SecondsTime(2)))
  {
    cerr << "Speed::test(): operator/(Length, Speed) failed." << endl;
    status = false;
  }


  return status;
}
