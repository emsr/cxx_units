//
// $Id: Speed3D.cpp,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Speed3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Speed3D.h"
#include "Length3D.h"
#include "scalar/Time.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Speed3D class.
//
bool Speed3D_test()
{
  bool status = generic3DTest<FeetPerSecondSpeed>("Speed");


  // Test iostream ops.

#define OSTREAM_TEST(expr, L, T, output) \
  { \
    ostringstream testStream; \
    testStream << Speed3DFormat<L, T>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Speed3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

#define VECTOR(x, y, z)  Speed3D(MetersPerSecondSpeed(x), \
                                 MetersPerSecondSpeed(y), \
                                 MetersPerSecondSpeed(z))


  OSTREAM_TEST(VECTOR(1, 2, 3),
	       MetersLength, SecondsTime, "(1, 2, 3) m/s");
  OSTREAM_TEST(VECTOR(1, 2, 3) * MetersLength(FeetLength(1)).value(),
	       FeetLength, SecondsTime, "(1, 2, 3) ft/s");

  //
  // Test interaction operators.
  //
  Speed3D vector = VECTOR(1, 2, 3);
  Length3D length = vector*SecondsTime(1);
  if (!similar(length,
               Length3D(MetersLength(1), MetersLength(2), MetersLength(3))))
  {
    cerr << "Speed3D::test(): operator*(Time) failed." << endl;
    status = false;
  }
  length = SecondsTime(1)*vector;
  if (!similar(length,
               Length3D(MetersLength(1), MetersLength(2), MetersLength(3))))
  {
    cerr << "Speed3D::test(): operator*(Time, Speed) failed." << endl;
    status = false;
  }
  length = Length3D(MetersLength(1), MetersLength(2), MetersLength(3));
  vector = length/SecondsTime(1);
  if (!similar(vector, VECTOR(1, 2, 3)))
  {
    cerr << "Speed3D::test(): operator Length/(Time) failed." << endl;
    status = false;
  }

  return status;
}
