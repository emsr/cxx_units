//
// $Id: Force3D.cpp,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Force3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "scalar/Mass.h"
#include "Force3D.h"
#include "Acceleration3D.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Force3D class.
//
bool Force3D_test()
{
  bool status = generic3DTest<PoundsForce>("Force");


  // Test iostream ops.

#define OSTREAM_TEST(expr, units, output) \
  { \
    ostringstream testStream; \
    testStream << Force3DFormat<units>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Force3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(Force3D(NewtonsForce(1),
                       NewtonsForce(2),
                       NewtonsForce(3)), NewtonsForce, "(1, 2, 3) N");
  OSTREAM_TEST(Force3D(PoundsForce(1),
                       PoundsForce(2),
                       PoundsForce(3)), PoundsForce, "(1, 2, 3) lb");

#define VECTOR(x, y, z)  Force3D(NewtonsForce(x), \
                                 NewtonsForce(y), \
                                 NewtonsForce(z))

  // Test interaction with Mass and Acceleration.
  Mass mass = KilogramsMass(2);
  Acceleration3D acceleration(MetersSecondAcceleration(1),
                              MetersSecondAcceleration(2),
                              MetersSecondAcceleration(3));

  if (!similar(mass*acceleration, VECTOR(2, 4, 6)))
  {
    cerr << "Force3D::test(): operator*(Mass, Acceleration) failed." << endl;
    status = false;
  }
  if (!similar(acceleration*mass, VECTOR(2, 4, 6)))
  {
    cerr << "Force3D::test(): operator*(Acceleration, Mass) failed." << endl;
    status = false;
  }

  acceleration = VECTOR(2, 4, 6)/KilogramsMass(2);
  if (!similar(acceleration, Acceleration3D(MetersSecondAcceleration(1),
                                            MetersSecondAcceleration(2),
                                            MetersSecondAcceleration(3))))
  {
    cerr << "Force3D::test(): operator/(Mass) failed." << endl;
    status = false;
  }

  return status;
}
