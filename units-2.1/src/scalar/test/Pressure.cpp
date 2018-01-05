//
// $Id: Pressure.cpp,v 1.5.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Pressure class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Pressure.h"
#include "Force.h"
#include "Area.h"
 

using namespace std;
using namespace Units;


//
// Test the API to the Pressure class.
//
bool Pressure_test()
{
  bool status = Unit_Tester<PascalsPressure>::genericTest("Pressure");


  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Pressure::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(PascalsPressure(2.3),     "2.3 Pa");
  OSTREAM_TEST(AtmospheresPressure(2.3), "2.3 atm");
  OSTREAM_TEST(PsiPressure(2.3),         "2.3 psi");
  OSTREAM_TEST(InchesHgPressure(2.3),    "2.3 inches Hg");


  // Test conversions.

#define CONVERSION_TEST(From, To, value_) \
  { \
    Pressure from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "Pressure::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "                  Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  CONVERSION_TEST(PascalsPressure(1.0),      PascalsPressure,     1.0);
  CONVERSION_TEST(PascalsPressure(101325.0), AtmospheresPressure, 1.0);
  CONVERSION_TEST(PascalsPressure(6894.757), PsiPressure,         1.0);
  CONVERSION_TEST(PascalsPressure(3386.38),  InchesHgPressure,    1.0);

  CONVERSION_TEST(AtmospheresPressure(1.0),     PascalsPressure,     101325.0);
  CONVERSION_TEST(AtmospheresPressure(1.0),     AtmospheresPressure, 1.0);
  CONVERSION_TEST(AtmospheresPressure(0.06804), PsiPressure,         1.0);
  CONVERSION_TEST(AtmospheresPressure(0.03342), InchesHgPressure,    1.0);

  CONVERSION_TEST(PsiPressure(1.0), PascalsPressure,     6894.757);
  CONVERSION_TEST(PsiPressure(1.0), AtmospheresPressure, 0.06804);
  CONVERSION_TEST(PsiPressure(1.0), PsiPressure,         1.0);
  CONVERSION_TEST(PsiPressure(1.0), InchesHgPressure,    2.035906643);

  CONVERSION_TEST(InchesHgPressure(1.0),         PascalsPressure,     3386.38);
  CONVERSION_TEST(InchesHgPressure(1.0),         AtmospheresPressure, 0.03342);
  CONVERSION_TEST(InchesHgPressure(2.035906643), PsiPressure,         1.0);
  CONVERSION_TEST(InchesHgPressure(1.0),         InchesHgPressure,    1.0);


#define COMPOSITE_TEST(P, F, A) \
  { \
    if (!similar(P(1), F(1)/A)) \
    { \
      cerr << "Pressure::test(): " \
	   << #P " != " #F "/" #A "." << endl; \
      cerr << "                  Expected " << P(1) << ", but got " \
	   << P(F(1)/A) << '.' << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(PascalsPressure, NewtonsForce, MetersArea(1));
  COMPOSITE_TEST(PsiPressure,     PoundsForce,  FeetArea(1.0/(12*12)));


  // Test multiple conversions
 
  if (!similar(PascalsPressure(1),
               PascalsPressure(AtmospheresPressure(InchesHgPressure(
                 PsiPressure(PascalsPressure(1)))))
              )
     )
  {
    cerr << "Pressure::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction operators.

  if (!similar(NewtonsForce(4)/MetersArea(2), PascalsPressure(2)))
  {
    cerr << "Pressure::test(): operator/(Force, Area) failed." << endl;
    status = false;
  }

  if (!similar(NewtonsForce(4)/PascalsPressure(2), MetersArea(2)))
  {
    cerr << "Pressure::test(): operator/(Force, Pressure) failed." << endl;
    status = false;
  }

  if (!similar(PascalsPressure(2)*MetersArea(2), NewtonsForce(4)))
  {
    cerr << "Pressure::test(): operator*(Area) failed." << endl;
    status = false;
  }
  if (!similar(MetersArea(2)*PascalsPressure(2), NewtonsForce(4)))
  {
    cerr << "Pressure::test(): operator*(Area, Pressure) failed." << endl;
    status = false;
  }


  return status;
}
