//
// $Id: MassFlowRate.cpp,v 1.4.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the MassFlowRate class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "Mass.h"
#include "Time.h"
#include "MassFlowRate.h"


using namespace std;
using namespace Units;


//
// Test the API to the MassFlowRate class.
//
bool MassFlowRate_test()
{
  bool status = Unit_Tester<KilogramsPerHourMassFlowRate>::genericTest("MassFlowRate");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(M, T, value, output) \
  { \
    ostringstream testStream; \
    testStream << MassFlowRateFormat<M, T>(M(value)/T(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "MassFlowRate::test(): " \
	   << "operator<<(ostream, MassFlowRateFormat<" #M ", " #T ">(" #M "(" #value \
              ")/" #T "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(PoundsMass,    SecondsTime, 2.3, "2.3 lb/s");
  OSTREAM_FORMAT_TEST(KilogramsMass, SecondsTime, 2.3, "2.3 kg/s");

  OSTREAM_FORMAT_TEST(PoundsMass,    MinutesTime, 2.3, "2.3 lb/min");
  OSTREAM_FORMAT_TEST(KilogramsMass, MinutesTime, 2.3, "2.3 kg/min");

  OSTREAM_FORMAT_TEST(PoundsMass,    HoursTime,   2.3, "2.3 lb/hr");
  OSTREAM_FORMAT_TEST(KilogramsMass, HoursTime,   2.3, "2.3 kg/hr");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "MassFlowRate::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(PoundsPerHourMassFlowRate(2.3),    "2.3 lb/hr");
  OSTREAM_TEST(KilogramsPerHourMassFlowRate(2.3), "2.3 kg/hr");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    MassFlowRate from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "MassFlowRate::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "               Expected " << value_ << ", got " \
	   << To(from) << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(PoundsPerHourMassFlowRate(1),   
                         PoundsPerHourMassFlowRate,        1);
  DOUBLE_CONVERSION_TEST(KilogramsPerHourMassFlowRate(1),   
                         KilogramsPerHourMassFlowRate,     1);
  DOUBLE_CONVERSION_TEST(PoundsPerHourMassFlowRate(2.204622622), 
                         KilogramsPerHourMassFlowRate,     1);
  DOUBLE_CONVERSION_TEST(KilogramsPerHourMassFlowRate(1),
			 PoundsPerHourMassFlowRate,        2.204622622);


#define COMPOSITE_TEST(R, M, T) \
  { \
    if (!similar(R(1), M(1)/T(1))) \
    { \
      cerr << "MassFlowRate::test(): " \
	   << #R " != " #M "/" #T "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(PoundsPerHourMassFlowRate,    PoundsMass,    HoursTime);
  COMPOSITE_TEST(KilogramsPerHourMassFlowRate, KilogramsMass, HoursTime);


#define DOUBLE_FORMAT_CONVERSION_TEST(M, T, value_) \
  { \
    MassFlowRate massFlowRate(M(value_)/T(1)); \
    if (fabs(MassFlowRateFormat<M, T>(massFlowRate).value() - value_) > 1e-6) \
    { \
      cerr << "MassFlowRate::test(): " \
	   << "double conversion for " #M "/" #T " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(PoundsMass, SecondsTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(KilogramsMass, SecondsTime, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(PoundsMass, MinutesTime, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(KilogramsMass, MinutesTime, 2.3);


  // Test interaction with Time and Mass.

  if (!similar(PoundsPerHourMassFlowRate(2)*HoursTime(2), PoundsMass(4)))
  {
    cerr << "MassFlowRate::test(): operator*(Time) failed." << endl;
    status = false;
  }
  if (!similar(HoursTime(2)*PoundsPerHourMassFlowRate(2), PoundsMass(4)))
  {
    cerr << "MassFlowRate::test(): operator*(Time, MassFlowRate) failed." << endl;
    status = false;
  }

  if (!similar(PoundsMass(4)/HoursTime(2), PoundsPerHourMassFlowRate(2)))
  {
    cerr << "MassFlowRate::test(): operator/(Mass, Time) failed." << endl;
    status = false;
  }
  if (!similar(PoundsMass(4)/PoundsPerHourMassFlowRate(2), HoursTime(2)))
  {
    cerr << "MassFlowRate::test(): operator/(Mass, MassFlowRate) failed." << endl;
    status = false;
  }
 

  return status;
}
