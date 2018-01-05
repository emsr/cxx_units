//
// $Id: Angle2D.cpp,v 1.5.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Angle2D.h"
#include "Unit2D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Angle2D class.
//
bool Angle2D_test()
{
  bool status = generic2DTest<DegreesAngle>("Angle");


  // Test iostream ops.

#define OSTREAM_TEST(expr, units, output) \
  { \
    ostringstream testStream; \
    testStream << Angle2DFormat<units>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Angle2D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                 Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }


  OSTREAM_TEST(Unit2D<Angle>(DegreesAngle(1),
			     DegreesAngle(2)), DegreesAngle, "(1, 2) deg");


  return status;
}
