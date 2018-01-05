//
// $Id: Angle.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Angle class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "Angle.h"
#include "Length.h"

 
using namespace std;
using namespace Units;


//
// Test the API to the Angle class.
//
bool Angle_test()
{
  bool status = Unit_Tester<RadiansAngle>::genericTest("Angle");


  // Test ostream ops.

#define OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Angle::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "               Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(DegreesAngle(2.3), "2.3 deg");
  OSTREAM_TEST(RadiansAngle(2.3), "2.3 rad");


  // Test conversions.

#define CONVERSION_TEST(from, To, value_) \
  if (fabs(To(from).value() - value_) > 1e-6) \
  { \
    cerr << "Angle::test(): " \
	 << #from " => " #To " conversion failed." << endl; \
    cerr << "               Expected " << (value_) \
	 << ", but got " << To(from).value() << "." << endl; \
    status = false; \
  }

  CONVERSION_TEST(DegreesAngle(1.0),   DegreesAngle, 1.0);
  CONVERSION_TEST(DegreesAngle(180.0), RadiansAngle, M_PI);

  CONVERSION_TEST(RadiansAngle(M_PI),  DegreesAngle, 180.0);
  CONVERSION_TEST(RadiansAngle(1.0),   RadiansAngle, 1.0);


  // Test multiple conversions
 
  if (!similar(DegreesAngle(1),
               DegreesAngle(RadiansAngle(DegreesAngle(1)))
              )
     )
  {
    cerr << "Angle::test(): multiple conversions failed." << endl;
    status = false;
  }


#define DOUBLE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-5) \
  { \
    cerr << "Angle::test(): " << #expr " failed." << endl; \
    cerr << "               Expected " << (output) \
	 << ", but got " << (expr) << "." << endl; \
    status = false; \
  }

#define ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    cerr << "Angle::test(): " << #expr " failed." << endl; \
    cerr << "               Expected " << (output) \
	 << ", but got " << DegreesAngle(expr) << "." << endl; \
    status = false; \
  }

  // Test trigonometric functions.

  DOUBLE_TEST(sin  (DegreesAngle(90)), 1);
  DOUBLE_TEST(cos  (DegreesAngle(90)), 0);
  DOUBLE_TEST(tan  (DegreesAngle(45)), 1);

  ANGLE_TEST(arcsin (sin(DegreesAngle(12.3))),  DegreesAngle(12.3));
  ANGLE_TEST(arccos (cos(DegreesAngle(12.3))),  DegreesAngle(12.3));
  ANGLE_TEST(arctan (tan(DegreesAngle(12.3))),  DegreesAngle(12.3));
  ANGLE_TEST(arctan (tan(DegreesAngle(12.3))),  DegreesAngle(12.3));
  ANGLE_TEST(arctan2(tan(DegreesAngle(45)), 1.0), DegreesAngle(45));


  //
  // Test renormalization.
  //
  Angle a;
  a = DegreesAngle(  10); ANGLE_TEST(normalize(a), DegreesAngle( 10));
  a = DegreesAngle( -10); ANGLE_TEST(normalize(a), DegreesAngle(-10));
  a = DegreesAngle( 370); ANGLE_TEST(normalize(a), DegreesAngle( 10));
  a = DegreesAngle(-370); ANGLE_TEST(normalize(a), DegreesAngle(-10));


#define LENGTH_TEST(expr, output) \
  if (!similar(expr, Length(output))) \
  { \
    cerr << "Angle::test(): " << #expr " failed." << endl; \
    cerr << "               Expected " << (output) \
	 << ", but got " << MetersLength(expr) << "." << endl; \
    status = false; \
  }

  LENGTH_TEST(MetersLength(1) * DegreesAngle(180), MetersLength(M_PI));
  LENGTH_TEST(DegreesAngle(180) * MetersLength(1), MetersLength(M_PI));

  return status;
}
