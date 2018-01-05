//
// $Id: Inertia.cpp,v 1.3.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Inertia class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Inertia.h"
#include "Area.h"


using namespace std;
using namespace Units;


//
// Test the API to the Inertia class.
//
bool Inertia_test()
{
  bool status = Unit_Tester<KilogramsMeterInertia>::genericTest("Inertia");


  // Test ostream ops.

#define OSTREAM_TEST(M, L, value, output) \
  { \
    ostringstream testStream; \
    testStream << InertiaFormat<M, L>(M(value)*(L(1)*L(1))); \
    if (testStream.str() != output) \
    { \
      cerr << "Inertia::test(): " \
	   << "operator<<(ostream, InertiaFormat<" #M ", " #L ">(" \
	   << #M "(" #value ")*" #L "(1)*" #L "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(KilogramsMass, FeetLength,   2.3, "2.3 kg-ft^2");
  OSTREAM_TEST(KilogramsMass, MetersLength, 2.3, "2.3 kg-m^2");

  OSTREAM_TEST(PoundsMass, FeetLength,   2.3, "2.3 lb-ft^2");
  OSTREAM_TEST(PoundsMass, MetersLength, 2.3, "2.3 lb-m^2");


#define DOUBLE_CONVERSION_TEST(M, L, value_) \
  { \
    Inertia inertia (M(value_)*(L(1)*L(1))); \
    if (fabs(InertiaFormat<M, L>(inertia).value() - value_) > 1e-6) \
    { \
      cerr << "Inertia::test(): " \
	   << "double conversion for " #M "-" #L "^2 failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(KilogramsMass, FeetLength,   2.3);
  DOUBLE_CONVERSION_TEST(KilogramsMass, MetersLength, 2.3);

  DOUBLE_CONVERSION_TEST(PoundsMass, FeetLength,   2.3);
  DOUBLE_CONVERSION_TEST(PoundsMass, MetersLength, 2.3);


  // Test interaction operators.

  Area area = MetersArea(1);
  Inertia inertia = KilogramsMass(1.23)*area;

  // Can't really test operator*(Mass, Area) directly ...
  // There's nothing with which to compare the answer.

  if (!similar(inertia/area, KilogramsMass(1.23)))
  {
    cerr << "Inertia::test(): operator*(Inertia, Area) failed." << endl;
    status = false;
  }
  if (!similar(inertia/KilogramsMass(1.23), area))
  {
    cerr << "Inertia::test(): operator/(Mass, Inertia) failed." << endl;
    status = false;
  }


  return status;
}
