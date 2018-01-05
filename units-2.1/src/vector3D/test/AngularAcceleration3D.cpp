//
// $Id: AngularAcceleration3D.cpp,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the AngularAcceleration3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "AngularAcceleration3D.h"
#include "AngularSpeed3D.h"
#include "Acceleration3D.h"
#include "Length3D.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the AngularAcceleration3D class.
//
bool AngularAcceleration3D_test()
{
  bool status = generic3DTest<DegreesSecondAngularAcceleration>
    ("AngularAcceleration");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << AngularAcceleration3DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "AngularAcceleration3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define VECTOR(x, y, z) \
  AngularAcceleration3D(DegreesSecondAngularAcceleration(x), \
                        DegreesSecondAngularAcceleration(y), \
                        DegreesSecondAngularAcceleration(z))


  OSTREAM_TEST(VECTOR(1, 2, 3) * DegreesAngle(RadiansAngle(1)).value(),
	       RadiansAngle, SecondsTime, "(1, 2, 3) rad/s^2");
  OSTREAM_TEST(VECTOR(1, 2, 3),
	       DegreesAngle, SecondsTime, "(1, 2, 3) deg/s^2");

  //
  // Test interaction operators.
  //
  AngularAcceleration3D vector = VECTOR(1, 2, 3);
  AngularSpeed3D        speed  = vector*SecondsTime(1);
  if (!similar(speed, AngularSpeed3D(RpmAngularSpeed(1),
                                     RpmAngularSpeed(2),
                                     RpmAngularSpeed(3))*60/360.0))
  {
    cerr << "AngularAcceleration3D::test(): operator*(Time) failed." << endl;
    status = false;
  }
  speed = SecondsTime(1)*vector;
  if (!similar(speed, AngularSpeed3D(RpmAngularSpeed(1),
                                     RpmAngularSpeed(2),
                                     RpmAngularSpeed(3))*60/360.0))
  {
    cerr << "AngularAcceleration3D::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }
  speed = AngularSpeed3D(RpmAngularSpeed(1),
                         RpmAngularSpeed(2),
                         RpmAngularSpeed(3))*60/360.0;
  vector = speed/SecondsTime(1);
  if (!similar(vector, VECTOR(1, 2, 3)))
  {
    cerr << "AngularAcceleration3D::test(): operator Speed/(Time) failed." << endl;
    status = false;
  }

  AngularAcceleration3D rads(RadiansSecondAngularAcceleration(1),
                             RadiansSecondAngularAcceleration(1),
                             RadiansSecondAngularAcceleration(1));
  Acceleration3D acc = rads % Length3D(MetersLength(1),
                                       MetersLength(2),
                                       MetersLength(3));
  if (!similar(acc, Acceleration3D(MetersSecondAcceleration(1),
                                   MetersSecondAcceleration(-2),
                                   MetersSecondAcceleration(1))))
  {
    cerr << "AngularAcceleration3D::test(): "
         << "operator AngularAcceleration3D%Length3D failed." << endl;
    cerr << "  got "
         << Acceleration3DFormat<MetersLength, SecondsTime>(acc) << endl;
    status = false;
  }
     

  return status;
}
