//
// $Id: MagneticFluxDensity.cpp,v 1.1.2.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the MagneticFluxDensity class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "MagneticFluxDensity.h"
#include "Force.h"
#include "MagneticField.h"


using namespace std;
using namespace Units;


//
// Test the API to the MagneticFluxDensity class.
//
bool MagneticFluxDensity_test()
{
  bool status = Unit_Tester<TeslaMagneticFluxDensity>::genericTest("MagneticFluxDensityMagneticFluxDensity");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(F, M, value, output) \
  { \
    ostringstream testStream; \
    testStream << MagneticFluxDensityFormat<F, M>(F(value)/M(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "MagneticFluxDensity::test(): " \
	   << "operator<<(ostream, MagneticFluxDensityFormat<" #F ", " #M ">(" #F "(" #value \
              ")/" #M "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(NewtonsForce, AmpsPerMeterMagneticField, 2.3, "2.3 N/A/m");
  OSTREAM_FORMAT_TEST(PoundsForce, AmpsPerMeterMagneticField, 2.3, "2.3 lb/A/m");
  OSTREAM_FORMAT_TEST(NewtonsForce, OerstedsMagneticField, 2.3, "2.3 N/Oe");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "MagneticFluxDensity::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                      Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(TeslaMagneticFluxDensity(2.3), "2.3 T");
  OSTREAM_TEST(GaussMagneticFluxDensity(2.3), "2.3 G");


#define DOUBLE_FORMAT_CONVERSION_TEST(F, M, value_) \
  { \
    MagneticFluxDensity speed(F(value_)/M(1)); \
    if (fabs(MagneticFluxDensityFormat<F, M>(speed).value() - value_) > 1e-6) \
    { \
      cerr << "MagneticFluxDensity::test(): " \
	   << "double conversion for " #F "/" #M " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(NewtonsForce, AmpsPerMeterMagneticField, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(PoundsForce, AmpsPerMeterMagneticField, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NewtonsForce, OerstedsMagneticField, 2.3);


#define COMPOSITE_TEST(S, F, M) \
  { \
    if (!similar(S(1), F(1)/M(1))) \
    { \
      cerr << "MagneticFluxDensity::test(): " \
	   << #S " != " #F "/" #M "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(TeslaMagneticFluxDensity, NewtonsForce, AmpsPerMeterMagneticField);


  // Test interaction with Force and MagneticField.

  if (!similar(TeslaMagneticFluxDensity(2)*AmpsPerMeterMagneticField(2), NewtonsForce(4)))
  {
    cerr << "MagneticFluxDensity::test(): operator*(MagneticField) failed." << endl;
    status = false;
  }

  if (!similar(AmpsPerMeterMagneticField(2)*TeslaMagneticFluxDensity(2), NewtonsForce(4)))
  {
    cerr << "MagneticFluxDensity::test(): operator*(MagneticField, MagneticFluxDensity) failed." << endl;
    status = false;
  }

  if (!similar(NewtonsForce(4)/AmpsPerMeterMagneticField(2), TeslaMagneticFluxDensity(2)))
  {
    cerr << "MagneticFluxDensity::test(): operator/(Force, MagneticField) failed." << endl;
    status = false;
  }
 
  if (!similar(NewtonsForce(4)/TeslaMagneticFluxDensity(2), AmpsPerMeterMagneticField(2)))
  {
    cerr << "MagneticFluxDensity::test(): operator/(Force, MagneticFluxDensity) failed." << endl;
    status = false;
  }

  return status;
}
