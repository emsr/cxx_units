//
// $Id: Speed2D.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Speed2D.h"
#include "Length2D.h"
#include "scalar/Time.h"
#include "Unit2D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Speed2D class.
//
bool Speed2D_test()
{
  bool status = generic2DTest<FeetPerSecondSpeed>("Speed");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << Speed2DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Speed2D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define VECTOR(x, y)  Speed2D(MetersPerSecondSpeed(x), \
                              MetersPerSecondSpeed(y))


  OSTREAM_TEST(VECTOR(1, 2),
	       MetersLength, SecondsTime, "(1, 2) m/s");
  OSTREAM_TEST(VECTOR(1, 2) * MetersLength(FeetLength(1)).value(),
	       FeetLength, SecondsTime, "(1, 2) ft/s");

  //
  // Test interaction operators.
  //
  Speed2D vector = VECTOR(1, 2);
  Length2D length = vector*SecondsTime(1);
  if (!similar(length, Length2D(MetersLength(1), MetersLength(2))))
  {
    cerr << "Speed2D::test(): operator*(Time) failed." << endl;
    status = false;
  }
  length = SecondsTime(1)*vector;
  if (!similar(length, Length2D(MetersLength(1), MetersLength(2))))
  {
    cerr << "Speed2D::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }
  length = Length2D(MetersLength(1), MetersLength(2));
  vector = length/SecondsTime(1);
  if (!similar(vector, VECTOR(1, 2)))
  {
    cerr << "Speed2D::test(): operator Length/(Time) failed." << endl;
    status = false;
  }

  return status;
}
