//
// $Id: Time.cpp,v 1.5.4.4 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Time class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "Time.h"


using namespace std;
using namespace Units;


//
// Test the API to the Time class.
//
bool Time_test()
{
  // Make sure unitless conversion works.
  Time x = SecondsTime(1)*(SecondsTime(1)/SecondsTime(2));

  bool status = Unit_Tester<SecondsTime>::genericTest("Time");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Time::test(): " \
	   << "operator<<(ostream, " #expr ") failed, got `" \
           << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MicrosecondsTime(2.3), "2.3 us");
  OSTREAM_TEST(MillisecondsTime(2.3), "2.3 ms");
  OSTREAM_TEST(SecondsTime(2.3),      "2.3 s");
  OSTREAM_TEST(MinutesTime(2.3),      "2.3 min");
  OSTREAM_TEST(HoursTime(2.3),        "2.3 hr");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Time from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Time::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(MicrosecondsTime(1000.0), MillisecondsTime, 1.0);
  CONVERSION_TEST(MillisecondsTime(1000.0), SecondsTime,      1.0);

  CONVERSION_TEST(SecondsTime(1.0),    SecondsTime, 1.0);
  CONVERSION_TEST(SecondsTime(60),     MinutesTime, 1.0);
  CONVERSION_TEST(SecondsTime(3600.0), HoursTime,   1.0);

  CONVERSION_TEST(MinutesTime(1.0),  SecondsTime, 60.0);
  CONVERSION_TEST(MinutesTime(1.0),  MinutesTime,  1.0);
  CONVERSION_TEST(MinutesTime(60.0), HoursTime,    1.0);

  CONVERSION_TEST(HoursTime(1.0), SecondsTime, 3600.0);
  CONVERSION_TEST(HoursTime(1.0), MinutesTime,   60.0);
  CONVERSION_TEST(HoursTime(1.0), HoursTime,      1.0);


  // Test multiple conversions
 
  if (!similar(SecondsTime(1),
               SecondsTime(MinutesTime(HoursTime(SecondsTime(1))))))
  {
    cerr << "Time::test(): multiple conversions failed." << endl;
    status = false;
  }

  return status;
}
