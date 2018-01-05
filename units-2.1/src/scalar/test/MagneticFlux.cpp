//
// $Id: MagneticFlux.cpp,v 1.1.2.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the MagneticFlux class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "MagneticFlux.h"
#include "MagneticFluxDensity.h"
#include "Area.h"


using namespace std;
using namespace Units;


//
// Test the API to the MagneticFlux class.
//
bool MagneticFlux_test()
{
  bool status = Unit_Tester<WebersMagneticFlux>::genericTest("MagneticFlux");


  // Test ostream ops.

#define OSTREAM_TEST(D, A, value, output) \
  { \
    ostringstream testStream; \
    testStream << MagneticFluxFormat<D, A>(D(value)*A(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "MagneticFlux::test(): " \
	   << "operator<<(ostream, MagneticFluxFormat<" #D ", " #A ">(" \
	   << #D "(" #value ")*" #A "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(TeslaMagneticFluxDensity, MetersArea, 2.3, "2.3 T-m^2");
  OSTREAM_TEST(GaussMagneticFluxDensity, FeetArea, 2.3, "2.3 G-ft^2");


#define DOUBLE_CONVERSION_TEST(D, A, value_) \
  { \
    MagneticFlux magneticFlux (D(value_)*A(1)); \
    if (fabs(MagneticFluxFormat<D, A>(magneticFlux).value() - value_) > 1e-6) \
    { \
      cerr << "MagneticFlux::test(): " \
	   << "double conversion for " #D "-" #A " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(TeslaMagneticFluxDensity, MetersArea, 2.3);
  DOUBLE_CONVERSION_TEST(GaussMagneticFluxDensity, FeetArea, 2.3);


  // Test interaction with magneticFluxDensity and area.

  MagneticFluxDensity magneticFluxDensity = TeslaMagneticFluxDensity(1);
  MagneticFlux magneticFlux = MetersArea(1.23)*magneticFluxDensity;

  // Can't really test operator*(Area, MagneticFluxDensity) directly ...
  // There's nothing with which to compare the answer.

  if (!similar(magneticFlux/magneticFluxDensity, MetersArea(1.23)))
  {
    cerr << "MagneticFlux::test(): operator*(MagneticFlux, MagneticFluxDensity) failed." << endl;
    status = false;
  }
  if (!similar(magneticFlux/MetersArea(1.23), magneticFluxDensity))
  {
    cerr << "MagneticFlux::test(): operator/(Area, MagneticFlux) failed." << endl;
    status = false;
  }

  return status;
}
