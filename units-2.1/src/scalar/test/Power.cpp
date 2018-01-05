//
// $Id: Power.cpp,v 1.5.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Power class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Power.h"
#include "Current.h"
#include "Voltage.h"

 
using namespace std;
using namespace Units;


//
// Test the API to the Power class.
//
bool Power_test()
{
  bool status = Unit_Tester<WattsPower>::genericTest("Power");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Power::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                     Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MilliwattsPower(2.3), "2.3 mW");
  OSTREAM_TEST(WattsPower(2.3),      "2.3 W");
  OSTREAM_TEST(KilowattsPower(2.3),  "2.3 kW");
  OSTREAM_TEST(MegawattsPower(2.3),  "2.3 MW");
  OSTREAM_TEST(GigawattsPower(2.3),  "2.3 GW");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Power from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Power::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(WattsPower(1.0),       MilliwattsPower, 1.0e3);
  CONVERSION_TEST(WattsPower(1.0),       WattsPower,      1.0);
  CONVERSION_TEST(WattsPower(1.0e3),     KilowattsPower,  1.0);
  CONVERSION_TEST(WattsPower(1.0e6),     MegawattsPower,  1.0);
  CONVERSION_TEST(WattsPower(1.0e9),     GigawattsPower,  1.0);

  CONVERSION_TEST(KilowattsPower(1.0),   MilliwattsPower, 1.0e6);
  CONVERSION_TEST(KilowattsPower(1.0),   WattsPower,      1.0e3);
  CONVERSION_TEST(KilowattsPower(1.0),   KilowattsPower,  1.0);
  CONVERSION_TEST(KilowattsPower(1.0e3), MegawattsPower,  1.0);
  CONVERSION_TEST(KilowattsPower(1.0e6), GigawattsPower,  1.0);

  CONVERSION_TEST(MegawattsPower(1.0),   WattsPower,     1.0e6);
  CONVERSION_TEST(MegawattsPower(1.0),   KilowattsPower, 1.0e3);
  CONVERSION_TEST(MegawattsPower(1.0),   MegawattsPower, 1.0);
  CONVERSION_TEST(MegawattsPower(1.0e3), GigawattsPower, 1.0);

  CONVERSION_TEST(GigawattsPower(1.0),   WattsPower,     1.0e9);
  CONVERSION_TEST(GigawattsPower(1.0),   KilowattsPower, 1.0e6);
  CONVERSION_TEST(GigawattsPower(1.0),   MegawattsPower, 1.0e3);
  CONVERSION_TEST(GigawattsPower(1.0),   GigawattsPower, 1.0);


  // Test multiple conversions
 
  if (!similar(WattsPower(1000),
               WattsPower(KilowattsPower(MegawattsPower(GigawattsPower(
                 MilliwattsPower(WattsPower(1000))))))
              )
     )
  {
    cerr << "Power::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Current and Voltage.

  if (!similar(AmpsCurrent(2)*VoltsVoltage(2), WattsPower(4)))
  {
    cerr << "Power::test(): operator*(Current, Voltage) failed." << endl;
    status = false;
  }

  if (!similar(VoltsVoltage(2)*AmpsCurrent(2), WattsPower(4)))
  {
    cerr << "Power::test(): operator*(Voltage, Current) failed." << endl;
    status = false;
  }

  if (!similar(WattsPower(4)/VoltsVoltage(2), AmpsCurrent(2)))
  {
    cerr << "Power::test(): operator/(Voltage) failed." << endl;
    status = false;
  }

  if (!similar(WattsPower(4)/AmpsCurrent(2), VoltsVoltage(2)))
  {
    cerr << "Power::test(): operator/(Current) failed." << endl;
    status = false;
  }


  return status;
}
