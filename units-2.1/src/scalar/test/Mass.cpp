//
// $Id: Mass.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Mass class.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include "Unit.cpp"
#include "Mass.h"


using namespace std;
using namespace Units;


//
// Test the API to the Mass class.
//
bool Mass_test()
{
  bool status = Unit_Tester<KilogramsMass>::genericTest("Mass");

  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Mass::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(KilogramsMass(2.3), "2.3 kg");
  OSTREAM_TEST(PoundsMass(2.3),    "2.3 lb");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Mass from(From); \
    if (fabs(To(from).value() - value_) > 1e-6) \
    { \
      cerr << "Mass::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(PoundsMass(1.0), PoundsMass, 1.0);
  CONVERSION_TEST(PoundsMass(2.204622622), KilogramsMass, 1.0);

  CONVERSION_TEST(KilogramsMass(1.0), PoundsMass, 2.204622622);
  CONVERSION_TEST(KilogramsMass(1.0), KilogramsMass, 1.0);


  // Test multiple conversions
 
  if (!similar(KilogramsMass(1),
               PoundsMass(KilogramsMass(1))
              )
     )
  {
    cerr << "Mass::test(): multiple conversions failed." << endl;
    status = false;
  }

  return status;
}
