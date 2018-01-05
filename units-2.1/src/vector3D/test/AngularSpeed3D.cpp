//
// $Id: AngularSpeed3D.cpp,v 1.7.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Angle3D class.
//

#ifdef _MSC_VER
#define M_PI  3.14159265358979323846
#endif
#include <math.h>
#include <iostream>
#include <sstream>
#include "AngularSpeed3D.h"
#include "scalar/Time.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Angle3D class.
//
bool AngularSpeed3D_test()
{
  bool status = generic3DTest<RpmAngularSpeed>("AngularSpeed");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << AngularSpeed3DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularSpeed3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                        Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define DEG_SPEED(value)  AngularSpeed(DegreesAngle(value) / SecondsTime(1))

#define VECTOR(x, y, z)   Unit3D<AngularSpeed>(DEG_SPEED(x), \
					       DEG_SPEED(y), \
					       DEG_SPEED(z))


  OSTREAM_TEST(VECTOR(1, 2, 3),
	       DegreesAngle, SecondsTime, "(1, 2, 3) deg/s");
  OSTREAM_TEST(VECTOR(1, 2, 3) * 180/M_PI,
	       RadiansAngle, SecondsTime, "(1, 2, 3) rad/s");


  return status;
}
