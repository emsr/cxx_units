//
// $Id: Current.cpp,v 1.3.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Current class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Current.h"


using namespace std;
using namespace Units;


//
// Test the API to the Current class.
//
bool Current_test()
{
  bool status = Unit_Tester<AmpsCurrent>::genericTest("Current");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Current::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MicroampsCurrent(2.3), "2.3 uA");
  OSTREAM_TEST(MilliampsCurrent(2.3), "2.3 mA");
  OSTREAM_TEST(AmpsCurrent(2.3),      "2.3 A");
  OSTREAM_TEST(KiloampsCurrent(2.3),  "2.3 kA");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Current from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Current::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(AmpsCurrent(1.0),       MicroampsCurrent, 1.0e6);
  CONVERSION_TEST(AmpsCurrent(1.0),       MilliampsCurrent, 1.0e3);
  CONVERSION_TEST(AmpsCurrent(1.0),       AmpsCurrent,      1.0);
  CONVERSION_TEST(AmpsCurrent(1.0e3),     KiloampsCurrent,  1.0);


  // Test multiple conversions
 
  if (!similar(AmpsCurrent(1), MicroampsCurrent(AmpsCurrent(1)))
     )
  {
    cerr << "Current::test(): multiple conversions failed." << endl;
    status = false;
  }

  return status;
}
