//
// $Id: Force2D.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Force2D.h"
#include "Acceleration2D.h"
#include "scalar/Mass.h"
#include "Unit2D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Force2D class.
//
bool Force2D_test()
{
  bool status = generic2DTest<PoundsForce>("Force");


  // Test iostream ops.

#define OSTREAM_TEST(expr, units, output) \
  { \
    ostringstream testStream; \
    testStream << Force2DFormat<units>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Force2D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(Force2D(NewtonsForce(1),
                       NewtonsForce(2)), NewtonsForce, "(1, 2) N");
  OSTREAM_TEST(Force2D(PoundsForce(1),
                       PoundsForce(2)), PoundsForce, "(1, 2) lb");

#define VECTOR(x, y)  Force2D(NewtonsForce(x), \
                              NewtonsForce(y))

  // Test interaction with Mass and Acceleration.
  Mass mass = KilogramsMass(2);
  Acceleration2D acceleration(MetersSecondAcceleration(1),
                              MetersSecondAcceleration(2));

  if (!similar(mass*acceleration, VECTOR(2, 4)))
  {
    cerr << "Force2D::test(): operator*(Mass, Acceleration) failed." << endl;
    status = false;
  }
  if (!similar(acceleration*mass, VECTOR(2, 4)))
  {
    cerr << "Force2D::test(): operator*(Acceleration, Mass) failed." << endl;
    status = false;
  }

  acceleration = VECTOR(2, 4)/KilogramsMass(2);
  if (!similar(acceleration, Acceleration2D(MetersSecondAcceleration(1),
                                            MetersSecondAcceleration(2))))
  {
    cerr << "Force2D::test(): operator/(Mass) failed." << endl;
    status = false;
  }

  return status;
}
