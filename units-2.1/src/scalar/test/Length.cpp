//
// $Id: Length.cpp,v 1.4.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Length class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "Length.h"


using namespace std;
using namespace Units;


//
// Test the API to the Length class.
//
bool Length_test()
{
  bool status = Unit_Tester<MetersLength>::genericTest("Length");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Length::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(MicrometersLength(2.3),   "2.3 um");
  OSTREAM_TEST(MillimetersLength(2.3),   "2.3 mm");
  OSTREAM_TEST(CentimetersLength(2.3),   "2.3 cm");
  OSTREAM_TEST(InchesLength(2.3),        "2.3 in");
  OSTREAM_TEST(FeetLength(2.3),          "2.3 ft");
  OSTREAM_TEST(MetersLength(2.3),        "2.3 m");
  OSTREAM_TEST(KilometersLength(2.3),    "2.3 km");
  OSTREAM_TEST(NauticalMilesLength(2.3), "2.3 nmi");
  OSTREAM_TEST(StatuteMilesLength(2.3),  "2.3 mi");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Length from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Length::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(MicrometersLength(1000.0), MillimetersLength, 1.0);
  CONVERSION_TEST(MillimetersLength(1000.0), MetersLength,      1.0);
  CONVERSION_TEST(CentimetersLength(100.0),  MetersLength,      1.0);

  CONVERSION_TEST(InchesLength(1.0),  InchesLength, 1.0);
  CONVERSION_TEST(InchesLength(12.0), FeetLength,   1.0);

  CONVERSION_TEST(FeetLength(1.0), FeetLength, 1.0);
  CONVERSION_TEST(FeetLength(1.0), InchesLength, 12.0);
  CONVERSION_TEST(FeetLength(1.0), MetersLength, 0.3048);
  CONVERSION_TEST(FeetLength(6076.115485564), NauticalMilesLength, 1.0);

  CONVERSION_TEST(MetersLength(0.3048), FeetLength, 1.0);
  CONVERSION_TEST(MetersLength(1.0), MetersLength, 1.0);
  CONVERSION_TEST(MetersLength(1852.0), NauticalMilesLength, 1.0);

  CONVERSION_TEST(NauticalMilesLength(1.0), FeetLength, 6076.115485564);
  CONVERSION_TEST(NauticalMilesLength(1.0), MetersLength, 1852.0);
  CONVERSION_TEST(NauticalMilesLength(1.0), NauticalMilesLength, 1.0);

  // Test multiple conversions
 
  if (!similar(FeetLength(1),
               MetersLength(KilometersLength
                            (NauticalMilesLength
                             (StatuteMilesLength(FeetLength(1)))))))
  {
    cerr << "Length::test(): multiple conversions failed." << endl;
    status = false;
  }

  return status;
}
