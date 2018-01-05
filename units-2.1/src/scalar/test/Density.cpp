//
// $Id: Density.cpp,v 1.4.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Density class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Density.h"
#include "Mass.h"
#include "Volume.h"


using namespace std;
using namespace Units;


//
// Test the API to the Density class.
//
bool Density_test()
{
  bool status = Unit_Tester<KilogramsMeterDensity>::genericTest("Density");


  // Test ostream ops.

#define OSTREAM_TEST(M, L, value, output) \
  { \
    ostringstream testStream; \
    testStream << DensityFormat<M, L>(M(value)/(L(1)*L(1)*L(1))); \
    if (testStream.str() != output) \
    { \
      cerr << "Density::test(): " \
	   << "operator<<(ostream, DensityFormat<" #M ", " #L ">(" \
	   << #M "(" #value ")/" #L "(1)^3)) failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(KilogramsMass, FeetLength, 2.3, "2.3 kg/ft^3");
  OSTREAM_TEST(KilogramsMass, MetersLength, 2.3, "2.3 kg/m^3");
  OSTREAM_TEST(KilogramsMass, NauticalMilesLength, 2.3, "2.3 kg/nmi^3");

  OSTREAM_TEST(PoundsMass, FeetLength, 2.3, "2.3 lb/ft^3");
  OSTREAM_TEST(PoundsMass, MetersLength, 2.3, "2.3 lb/m^3");
  OSTREAM_TEST(PoundsMass, NauticalMilesLength, 2.3, "2.3 lb/nmi^3");


#define DOUBLE_CONVERSION_TEST(M, L, value_) \
  { \
    Density density (M(value_)/(L(1)*L(1)*L(1))); \
    if (fabs(DensityFormat<M, L>(density).value() - value_) > 1e-6) \
    { \
      cerr << "Density::test(): " \
	   << "double conversion for " #M "/" #L " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(KilogramsMass, FeetLength, 2.3);
  DOUBLE_CONVERSION_TEST(KilogramsMass, MetersLength, 2.3);
  DOUBLE_CONVERSION_TEST(KilogramsMass, NauticalMilesLength, 2.3);

  DOUBLE_CONVERSION_TEST(PoundsMass, FeetLength, 2.3);
  DOUBLE_CONVERSION_TEST(PoundsMass, MetersLength, 2.3);
  DOUBLE_CONVERSION_TEST(PoundsMass, NauticalMilesLength, 2.3);


  // Test interaction operators.

  Volume  volume  = MetersVolume(1);
  Density density = KilogramsMass(1.23)/volume;

  // Can't really test operator/(Mass, Volume) directly ...
  // There's nothing with which to compare the answer.

  if (!similar(density*volume, KilogramsMass(1.23)))
  {
    cerr << "Density::test(): operator*(Volume) failed." << endl;
    status = false;
  }
  if (!similar(volume*density, KilogramsMass(1.23)))
  {
    cerr << "Density::test(): operator*(Volume, Density) failed." << endl;
    status = false;
  }

  if (!similar(KilogramsMass(1.23)/density, volume))
  {
    cerr << "Density::test(): operator/(Mass, Density) failed." << endl;
    status = false;
  }


  return status;
}
