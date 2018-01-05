//
// $Id: Temperature.cpp,v 1.4.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Temperature class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Temperature.h"
#include "Length.h"


using namespace std;
using namespace Units;


//
// Test the API to the Temperature class.
//
bool Temperature_test()
{
  bool status = Unit_Tester<CelsiusTemperature>::genericTest("Temperature");


  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Temperature::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                     Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(CelsiusTemperature(2.3),    "2.3 C");
  OSTREAM_TEST(KelvinTemperature(2.3),     "2.3 K");
  OSTREAM_TEST(FahrenheitTemperature(2.3), "2.3 F");
  OSTREAM_TEST(RankineTemperature(2.3),    "2.3 R");

  OSTREAM_TEST(AbsCelsiusTemperature(2.3),    "2.3 C");
  OSTREAM_TEST(AbsKelvinTemperature(2.3),     "2.3 K");
  OSTREAM_TEST(AbsFahrenheitTemperature(2.3), "2.3 F");
  OSTREAM_TEST(AbsRankineTemperature(2.3),    "2.3 R");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Temperature from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Temperature::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "                     Expected " << value_ \
	   << " but got " << To(from).value() << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(CelsiusTemperature(  1.0), CelsiusTemperature,         1.0);
  CONVERSION_TEST(CelsiusTemperature(  0.0), FahrenheitTemperature,      0.0);
  CONVERSION_TEST(CelsiusTemperature(  0.0), KelvinTemperature,          0.0);
  CONVERSION_TEST(CelsiusTemperature(100.0), FahrenheitTemperature,    180.0);

  CONVERSION_TEST(FahrenheitTemperature(180.0), CelsiusTemperature,    100.0);
  CONVERSION_TEST(FahrenheitTemperature(  0.0), CelsiusTemperature,      0.0);
  CONVERSION_TEST(FahrenheitTemperature(  1.0), FahrenheitTemperature,   1.0);
  CONVERSION_TEST(FahrenheitTemperature(  0.0), RankineTemperature,      0.0);

  CONVERSION_TEST(KelvinTemperature (  1.0),  KelvinTemperature,         1.0);
  CONVERSION_TEST(KelvinTemperature (273.15), CelsiusTemperature,      273.15);

  CONVERSION_TEST(RankineTemperature(  1.0),  RankineTemperature,        1.0);
  CONVERSION_TEST(RankineTemperature(459.67), FahrenheitTemperature,   459.67);

#define ABS_CONVERSION_TEST(From, To, value_) \
  { \
    AbsTemperature from(Abs##From); \
    if (fabs(Abs##To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Temperature::test(): " \
	   << #From " => " #To " abs conversion failed." << endl; \
      cerr << "                     Expected " << value_ \
	   << " but got " << Abs##To(from).value() << endl; \
      status = false; \
    } \
  }

  ABS_CONVERSION_TEST(CelsiusTemperature(  1.0), CelsiusTemperature,         1.0);
  ABS_CONVERSION_TEST(CelsiusTemperature(  0.0), FahrenheitTemperature,     32.0);
  ABS_CONVERSION_TEST(CelsiusTemperature(  0.0), KelvinTemperature,        273.15);
  ABS_CONVERSION_TEST(CelsiusTemperature(100.0), FahrenheitTemperature,    212.0);

  ABS_CONVERSION_TEST(FahrenheitTemperature(212.0), CelsiusTemperature,    100.0);
  ABS_CONVERSION_TEST(FahrenheitTemperature( 32.0), CelsiusTemperature,      0.0);
  ABS_CONVERSION_TEST(FahrenheitTemperature(  1.0), FahrenheitTemperature,   1.0);
  ABS_CONVERSION_TEST(FahrenheitTemperature(  0.0), RankineTemperature,    459.67);

  ABS_CONVERSION_TEST(KelvinTemperature (  1.0),  KelvinTemperature,        1.0);
  ABS_CONVERSION_TEST(KelvinTemperature (273.15), CelsiusTemperature,       0.0);

  ABS_CONVERSION_TEST(RankineTemperature(  1.0),  RankineTemperature,       1.0);
  ABS_CONVERSION_TEST(RankineTemperature(459.67), FahrenheitTemperature,    0.0);


  // Test multiple conversions
 
  if (!similar(CelsiusTemperature(1),
               CelsiusTemperature(FahrenheitTemperature(CelsiusTemperature(1)))
              )
     )
  {
    cerr << "Temperature::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test absolute-relative operations.

#define TEMPERATURE_TEST(expression, expect) \
  if (!similar(expression, \
               expect)) \
  { \
    cerr << "Temperature::test(): " #expression " failed." << endl; \
    cerr << "                     Expected " << expect \
         << " but got " << expression << endl; \
    status = false; \
  }

  TEMPERATURE_TEST(FahrenheitTemperature(AbsFahrenheitTemperature(72.0) -
                                         AbsFahrenheitTemperature(32.0)),
                   FahrenheitTemperature(40.0));

  TEMPERATURE_TEST(AbsFahrenheitTemperature(AbsFahrenheitTemperature(32.0) +
                                            FahrenheitTemperature(40.0)),
                   AbsFahrenheitTemperature(72.0));

  TEMPERATURE_TEST(RankineTemperature(AbsRankineTemperature(72.0) -
                                      AbsRankineTemperature(32.0)),
                   RankineTemperature(40.0));

  TEMPERATURE_TEST(AbsRankineTemperature(AbsRankineTemperature(32.0) +
                                         RankineTemperature(40.0)),
                   AbsRankineTemperature(72.0));

  return status;
}
