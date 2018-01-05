//
// $Id: Volume.cpp,v 1.5.4.2 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Volume class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Area.h"
#include "Volume.h"

 
using namespace std;
using namespace Units;


//
// Test the API to the Volume class.
//
bool Volume_test()
{
  bool status = Unit_Tester<MetersVolume>::genericTest("Volume");

  // Test ostream ops.
 
#define OSTREAM_FORMAT_TEST(L, value, output) \
  { \
    ostringstream testStream; \
    testStream << VolumeFormat<L>(L(value)*L(1.0)*L(1.0)); \
    if (testStream.str() != output) \
    { \
      cerr << "Volume::test(): " \
           << "operator<<(ostream, VolumeFormat<" #L ">(" #L "(" #value \
              ")" " failed." << endl; \
      cerr << "               Expected `" << output \
           << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }
 
  OSTREAM_FORMAT_TEST(FeetLength,          2.3, "2.3 ft^3");
  OSTREAM_FORMAT_TEST(MetersLength,        2.3, "2.3 m^3");
  OSTREAM_FORMAT_TEST(NauticalMilesLength, 2.3, "2.3 nmi^3");


#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Volume::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(InchesVolume(2.3),    "2.3 in^3");
  OSTREAM_TEST(FeetVolume(2.3),      "2.3 ft^3");
  OSTREAM_TEST(MetersVolume(2.3),    "2.3 m^3");
  OSTREAM_TEST(LitersVolume(2.3),    "2.3 L");
  OSTREAM_TEST(USGallonsVolume(2.3), "2.3 US gal");
  OSTREAM_TEST(BIGallonsVolume(2.3), "2.3 BI gal");


#define DOUBLE_CONVERSION_TEST(From, To, value_) \
  { \
    Volume from(From); \
    if (fabs(To(from).value() - value_) > 1e-3) \
    { \
      cerr << "Volume::test(): " \
	   << #From " => " #To " conversion failed." << endl; \
      cerr << "                Expected " << value_ << ", got " \
	   << To(from).value() << '.' << endl; \
      status = false; \
    } \
  }

  DOUBLE_CONVERSION_TEST(MetersVolume(1), LitersVolume,    1000);
  DOUBLE_CONVERSION_TEST(MetersVolume(1), USGallonsVolume,  61023.74409/231.0);
  DOUBLE_CONVERSION_TEST(MetersVolume(1), BIGallonsVolume,  61023.74409/277.4);


#define COMPOSITE_TEST(V, A) \
  { \
    if (!similar(V(1), A(1)*A(1))) \
    { \
      cerr << "Volume::test(): " \
	   << #V " != " #A "*" #A "." << endl; \
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
    Volume volume(L(value_)*L(1.0)*L(1.0)); \
    if (fabs(VolumeFormat<L>(volume).value() - value_) > 1e-6) \
    { \
      cerr << "Volume::test(): " \
           << "double conversion for " #L " failed." << endl; \
      status = false; \
    } \
  }
 
  DOUBLE_FORMAT_CONVERSION_TEST(FeetLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(MetersLength, 2.3);
  DOUBLE_FORMAT_CONVERSION_TEST(NauticalMilesLength, 2.3);

  // Test multiple conversions
 
  if (!similar(MetersVolume(1),
               MetersVolume(LitersVolume(USGallonsVolume(BIGallonsVolume(
                 MetersVolume(1)))))
              )
     )
  {
    cerr << "Volume::test(): multiple conversions failed." << endl;
    status = false;
  }

 
  // Test interaction with Length and Area.

  if (!similar(MetersLength(2)*MetersArea(2), MetersVolume(4)))
  {
    cerr << "Volume::test(): operator* (Length, Area) failed." << endl;
    status = false;
  }
  if (!similar(MetersArea(2)*MetersLength(2), MetersVolume(4)))
  {
    cerr << "Volume::test(): operator* (Area, Length) failed." << endl;
    status = false;
  }
  if (!similar(MetersVolume(8)/MetersLength(2), MetersArea(4)))
  {
    cerr << "Volume::test(): operator/(Length) failed." << endl;
    status = false;
  }
  if (!similar(MetersVolume(8)/MetersArea(4), MetersLength(2)))
  {
    cerr << "Volume::test(): operator/(Area) failed." << endl;
    status = false;
  }


  return status;
}
