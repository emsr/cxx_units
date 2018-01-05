//
// $Id: Frequency.cpp,v 1.4.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Frequency class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "Time.h"
#include "Frequency.h"


using namespace std;
using namespace Units;


//
// Test the API to the Frequency class.
//
bool Frequency_test()
{
  bool status = Unit_Tester<HertzFrequency>::genericTest("Frequency");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Frequency::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                     Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(HertzFrequency(2.3),     "2.3 Hz");
  OSTREAM_TEST(KilohertzFrequency(2.3), "2.3 KHz");
  OSTREAM_TEST(MegahertzFrequency(2.3), "2.3 MHz");
  OSTREAM_TEST(GigahertzFrequency(2.3), "2.3 GHz");
  OSTREAM_TEST(TerahertzFrequency(2.3), "2.3 THz");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Frequency from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Frequency::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(HertzFrequency(1.0),     HertzFrequency,     1.0);
  CONVERSION_TEST(HertzFrequency(1.0e3),   KilohertzFrequency, 1.0);
  CONVERSION_TEST(HertzFrequency(1.0e6),   MegahertzFrequency, 1.0);
  CONVERSION_TEST(HertzFrequency(1.0e9),   GigahertzFrequency, 1.0);
  CONVERSION_TEST(HertzFrequency(1.0e12),  TerahertzFrequency, 1.0);

  CONVERSION_TEST(KilohertzFrequency(1.0), HertzFrequency,     1.0e3);
  CONVERSION_TEST(KilohertzFrequency(1.0), KilohertzFrequency, 1.0);
  CONVERSION_TEST(KilohertzFrequency(1.0e3), MegahertzFrequency, 1.0);
  CONVERSION_TEST(KilohertzFrequency(1.0e6), GigahertzFrequency, 1.0);
  CONVERSION_TEST(KilohertzFrequency(1.0e9), TerahertzFrequency, 1.0);

  CONVERSION_TEST(MegahertzFrequency(1.0), HertzFrequency,     1.0e6);
  CONVERSION_TEST(MegahertzFrequency(1.0), KilohertzFrequency, 1.0e3);
  CONVERSION_TEST(MegahertzFrequency(1.0), MegahertzFrequency, 1.0);
  CONVERSION_TEST(MegahertzFrequency(1.0e3), GigahertzFrequency, 1.0);
  CONVERSION_TEST(MegahertzFrequency(1.0e6), TerahertzFrequency, 1.0);

  CONVERSION_TEST(GigahertzFrequency(1.0), HertzFrequency,     1.0e9);
  CONVERSION_TEST(GigahertzFrequency(1.0), KilohertzFrequency, 1.0e6);
  CONVERSION_TEST(GigahertzFrequency(1.0), MegahertzFrequency, 1.0e3);
  CONVERSION_TEST(GigahertzFrequency(1.0), GigahertzFrequency, 1.0);
  CONVERSION_TEST(GigahertzFrequency(1.0e3), TerahertzFrequency, 1.0);

  CONVERSION_TEST(TerahertzFrequency(1.0), HertzFrequency,     1.0e12);
  CONVERSION_TEST(TerahertzFrequency(1.0), KilohertzFrequency, 1.0e9);
  CONVERSION_TEST(TerahertzFrequency(1.0), MegahertzFrequency, 1.0e6);
  CONVERSION_TEST(TerahertzFrequency(1.0), GigahertzFrequency, 1.0e3);
  CONVERSION_TEST(TerahertzFrequency(1.0), TerahertzFrequency, 1.0);

  // Test multiple conversions
 
  if (!similar(HertzFrequency(1),
               HertzFrequency(KilohertzFrequency(MegahertzFrequency(
                 GigahertzFrequency(TerahertzFrequency(HertzFrequency(1))))))
              )
     )
  {
    cerr << "Frequency::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Time.

  if (!similar(2.0/HertzFrequency(2.0), SecondsTime(1.0)))
  {
    cerr << "Frequency::test(): operator/ (double, Frequency) failed." << endl;
    cerr << "                   Expected " << SecondsTime(1.0)
         << ", but got " << SecondsTime(2.0/HertzFrequency(2.0)) << '.' << endl;
    status = false;
  }

  if (!similar(2.0/SecondsTime(1.0), HertzFrequency(2.0)))
  {
    cerr << "Frequency::test(): operator/ (double, Time) failed." << endl;
    cerr << "                   Expected " << HertzFrequency(2.0)
         << ", but got " << HertzFrequency(2.0/SecondsTime(1.0)) << '.' << endl;
    status = false;
  }


  return status;
}
