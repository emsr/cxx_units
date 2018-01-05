//
// $Id: Voltage.cpp,v 1.3.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Voltage class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Voltage.h"


using namespace std;
using namespace Units;


//
// Test the API to the Voltage class.
//
bool Voltage_test()
{
  bool status = Unit_Tester<VoltsVoltage>::genericTest("Voltage");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Voltage::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MicrovoltsVoltage(2.3), "2.3 uV");
  OSTREAM_TEST(MillivoltsVoltage(2.3), "2.3 mV");
  OSTREAM_TEST(VoltsVoltage(2.3),      "2.3 V");
  OSTREAM_TEST(KilovoltsVoltage(2.3),  "2.3 kV");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Voltage from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Voltage::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(VoltsVoltage(1.0),       MicrovoltsVoltage, 1.0e6);
  CONVERSION_TEST(VoltsVoltage(1.0),       MillivoltsVoltage, 1.0e3);
  CONVERSION_TEST(VoltsVoltage(1.0),       VoltsVoltage,      1.0);
  CONVERSION_TEST(VoltsVoltage(1.0e3),     KilovoltsVoltage,  1.0);


  // Test multiple conversions
 
  if (!similar(VoltsVoltage(1), MicrovoltsVoltage(VoltsVoltage(1)))
     )
  {
    cerr << "Voltage::test(): multiple conversions failed." << endl;
    status = false;
  }

  return status;
}
