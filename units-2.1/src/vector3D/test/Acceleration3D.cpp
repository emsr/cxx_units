//
// $Id: Acceleration3D.cpp,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Acceleration3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Acceleration3D.h"
#include "Speed3D.h"
#include "scalar/Time.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Acceleration3D class.
//
bool Acceleration3D_test()
{
  bool status = generic3DTest<FeetSecondAcceleration>("Acceleration");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << Acceleration3DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Acceleration3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define VECTOR(x, y, z)  Acceleration3D(MetersSecondAcceleration(x), \
                                        MetersSecondAcceleration(y), \
                                        MetersSecondAcceleration(z))


  OSTREAM_TEST(VECTOR(1, 2, 3),
	       MetersLength, SecondsTime, "(1, 2, 3) m/s^2");
  OSTREAM_TEST(VECTOR(1, 2, 3) * MetersLength(FeetLength(1)).value(),
	       FeetLength, SecondsTime, "(1, 2, 3) ft/s^2");

  //
  // Test interaction operators.
  //
  Acceleration3D vector = VECTOR(1, 2, 3);
  Speed3D speed = vector*SecondsTime(1);
  if (!similar(speed, Speed3D(MetersPerSecondSpeed(1),
                              MetersPerSecondSpeed(2),
                              MetersPerSecondSpeed(3))))
  {
    cerr << "Acceleration3D::test(): operator*(Time) failed." << endl;
    status = false;
  }
  speed = SecondsTime(1)*vector;
  if (!similar(speed, Speed3D(MetersPerSecondSpeed(1),
                              MetersPerSecondSpeed(2),
                              MetersPerSecondSpeed(3))))
  {
    cerr << "Acceleration3D::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }
  speed = Speed3D(MetersPerSecondSpeed(1),
                  MetersPerSecondSpeed(2),
                  MetersPerSecondSpeed(3));
  vector = speed/SecondsTime(1);
  if (!similar(vector, VECTOR(1, 2, 3)))
  {
    cerr << "Acceleration3D::test(): operator Speed/(Time) failed." << endl;
    status = false;
  }

  return status;
}
