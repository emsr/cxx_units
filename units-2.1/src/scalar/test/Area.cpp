//
// $Id: Area.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Area class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Area.h"


using namespace std;
using namespace Units;


//
// Test the API to the Area class.
//
bool Area_test()
{
  bool status = Unit_Tester<MetersArea>::genericTest("Area");

  // Test ostream ops.

#define OSTREAM_FORMAT_TEST(L, value, output) \
  { \
    ostringstream testStream; \
    testStream << AreaFormat<L>(L(value)*L(1.0)); \
    if (testStream.str() != output) \
    { \
      cerr << "Area::test(): " \
	   << "operator<<(ostream, AreaFormat<" #L ">(" #L "(" #value \
              ")) failed." << endl; \
      cerr << "              Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_FORMAT_TEST(FeetLength,          2.3, "2.3 ft^2");
  OSTREAM_FORMAT_TEST(MetersLength,        2.3, "2.3 m^2");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, 2.3, "2.3 nmi^2");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Area::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "              Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(InchesArea(2.3),        "2.3 in^2");
  OSTREAM_TEST(FeetArea(2.3),          "2.3 ft^2");
  OSTREAM_TEST(MetersArea(2.3),        "2.3 m^2");
  OSTREAM_TEST(KilometersArea(2.3),    "2.3 km^2");
  OSTREAM_TEST(NauticalMilesArea(2.3), "2.3 nmi^2");
  OSTREAM_TEST(StatuteMilesArea(2.3),  "2.3 mi^2");
  OSTREAM_TEST(AcresArea(2.3),         "2.3 acres");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    Area from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "Area::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "              Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(StatuteMilesArea(1), AcresArea, 640.0);


#define COMPOSITE_TEST(A, L) \
  { \
    if (!A(1).similarTo(L(1)*L(1))) \
    { \
      cerr << "Area::test(): " \
	   << #A " != " #L "*" #L "." << endl; \
      status = false; \
    } \
  }

  // Test that composite subclasses are correctly defined.
  COMPOSITE_TEST(InchesArea,        InchesLength);
  COMPOSITE_TEST(FeetArea,          FeetLength);
  COMPOSITE_TEST(MetersArea,        MetersLength);
  COMPOSITE_TEST(KilometersArea,    KilometersLength);
  COMPOSITE_TEST(NauticalMilesArea, NauticalMilesLength);
  COMPOSITE_TEST(StatuteMilesArea,  StatuteMilesLength);


#define DOUBLE_FORMAT_CONVERSION_TEST(L, value_) \
  { \
    Area area(L(value_)*L(1.0)); \
    if (fabs(AreaFormat<L>(area).value() - value_) > 1e-6) \
    { \
      cerr << "Area::test(): " \
	   << "double conversion for " #L " failed." << endl; \
      status = false; \
    } \
  }

  DOUBLE_FORMAT_CONVERSION_TEST(FeetLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MetersLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NauticalMilesLength, 2.3);

  // Test multiple conversions
 
  if (!similar(MetersArea(1),
               MetersArea(KilometersArea(NauticalMilesArea(
                 StatuteMilesArea(AcresArea(MetersArea(1))))))
              )
     )
  {
    cerr << "Area::test(): multiple conversions failed." << endl;
    status = false;
  }


  // Test interaction with Length.

  if (!similar(MetersLength(2) * MetersLength(2), MetersArea(4)) )
  {
    cerr << "Area::test(): operator* (Length, Length) failed." << endl;
    status = false;
  }

  if (!similar(MetersArea(4) / MetersLength(2), MetersLength(2)) )
  {
    cerr << "Area::test(): operator/ (Length) failed." << endl;
    status = false;
  }


  return status;
}
