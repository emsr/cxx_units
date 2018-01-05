//
// $Id: Acceleration2D.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Acceleration2D.h"
#include "Speed2D.h"
#include "scalar/Time.h"
#include "Unit2D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Acceleration2D class.
//
bool Acceleration2D_test()
{
  bool status = generic2DTest<FeetSecondAcceleration>("Acceleration");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << Acceleration2DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Acceleration2D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define VECTOR(x, y)  Acceleration2D(MetersSecondAcceleration(x), \
                                     MetersSecondAcceleration(y))


  OSTREAM_TEST(VECTOR(1, 2),
	       MetersLength, SecondsTime, "(1, 2) m/s^2");
  OSTREAM_TEST(VECTOR(1, 2) * MetersLength(FeetLength(1)).value(),
	       FeetLength, SecondsTime, "(1, 2) ft/s^2");

  //
  // Test interaction operators.
  //
  Acceleration2D vector = VECTOR(1, 2);
  Speed2D speed = vector*SecondsTime(1);
  if (!similar(speed, Speed2D(MetersPerSecondSpeed(1),
                              MetersPerSecondSpeed(2))))
  {
    cerr << "Acceleration2D::test(): operator*(Time) failed." << endl;
    status = false;
  }
  speed = SecondsTime(1)*vector;
  if (!similar(speed, Speed2D(MetersPerSecondSpeed(1),
                              MetersPerSecondSpeed(2))))
  {
    cerr << "Acceleration2D::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }
  speed = Speed2D(MetersPerSecondSpeed(1),
                  MetersPerSecondSpeed(2));
  vector = speed/SecondsTime(1);
  if (!similar(vector, VECTOR(1, 2)))
  {
    cerr << "Acceleration2D::test(): operator Speed/(Time) failed." << endl;
    status = false;
  }

  return status;
}
