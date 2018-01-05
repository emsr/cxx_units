//
// $Id: MagneticField.cpp,v 1.1.2.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the MagneticField class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "MagneticField.h"
#include "Current.h"
#include "Length.h"


using namespace std;
using namespace Units;


//
// Test the API to the MagneticField class.
//
bool MagneticField_test()
{
  bool status = Unit_Tester<AmpsPerMeterMagneticField>::genericTest("MagneticField");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(C, L, value, output) \
  { \
    ostringstream testStream; \
    testStream << MagneticFieldFormat<C, L>(C(value)/L(1)); \
    if (testStream.str() != output) \
    { \
      cerr << "MagneticField::test(): " \
	   << "operator<<(ostream, MagneticFieldFormat<" #C ", " #L ">(" #C "(" #value \
              ")/" #L "(1))) failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(AmpsCurrent, MetersLength, 2.3, "2.3 A/m");
  OSTREAM_FORMAT_TEST(MilliampsCurrent, MetersLength, 2.3, "2.3 mA/m");

  OSTREAM_FORMAT_TEST(AmpsCurrent, MillimetersLength, 2.3, "2.3 A/mm");
  OSTREAM_FORMAT_TEST(MilliampsCurrent, MillimetersLength, 2.3, "2.3 mA/mm");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "MagneticField::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(AmpsPerMeterMagneticField(2.3), "2.3 A/m");
  OSTREAM_TEST(OerstedsMagneticField(2.3),     "2.3 Oe");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    MagneticField from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "MagneticField::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "               Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(AmpsPerMeterMagneticField(1),   
                         AmpsPerMeterMagneticField,       1);
  DOUBLE_CONVERSION_TEST(OerstedsMagneticField(1),
			 AmpsPerMeterMagneticField,
                         1000.0/(4*3.14159265358979323846));


#define COMPOSITE_TEST(F, C, L) \
  { \
    if (!similar(F(1), C(1)/L(1))) \
    { \
      cerr << "MagneticField::test(): " \
	   << #F " != " #C "/" #L "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(AmpsPerMeterMagneticField, AmpsCurrent, MetersLength);


#define DOUBLE_FORMAT_CONVERSION_TEST(C, L, value_) \
  { \
    MagneticField magneticField(C(value_)/L(1)); \
    if (fabs(MagneticFieldFormat<C, L>(magneticField).value() - value_) > 1e-6) \
    { \
      cerr << "MagneticField::test(): " \
	   << "double conversion for " #C "/" #L " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(AmpsCurrent, MetersLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MilliampsCurrent, MetersLength, 2.3);

  DOUBLE_FORMAT_CONVERSION_TEST(AmpsCurrent, MillimetersLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MilliampsCurrent, MillimetersLength, 2.3);

  // Test multiple conversions
 
  if (!similar(AmpsPerMeterMagneticField(1),
               AmpsPerMeterMagneticField(OerstedsMagneticField
                                         (AmpsPerMeterMagneticField(1)))))
  {
    cerr << "MagneticField::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Length and Current.

  if (!similar(AmpsPerMeterMagneticField(2)*MetersLength(2), AmpsCurrent(4)))
  {
    cerr << "MagneticField::test(): operator*(Length) failed." << endl;
    status = false;
  }

  if (!similar(MetersLength(2)*AmpsPerMeterMagneticField(2), AmpsCurrent(4)))
  {
    cerr << "MagneticField::test(): operator*(Length, MagneticField) failed." << endl;
    status = false;
  }

  if (!similar(AmpsCurrent(4)/MetersLength(2), AmpsPerMeterMagneticField(2)))
  {
    cerr << "MagneticField::test(): operator/(Current, Length) failed." << endl;
    status = false;
  }
 
  if (!similar(AmpsCurrent(4)/AmpsPerMeterMagneticField(2), MetersLength(2)))
  {
    cerr << "MagneticField::test(): operator/(Current, MagneticField) failed." << endl;
    status = false;
  }


  return status;
}
