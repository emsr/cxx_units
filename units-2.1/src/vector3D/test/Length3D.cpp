//
// $Id: Length3D.cpp,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Length3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Length3D.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Length3D class.
//
bool Length3D_test()
{
  bool status = generic3DTest<FeetLength>("Length");


  // Test iostream ops.

#define OSTREAM_TEST(expr, units, output) \
  { \
    ostringstream testStream; \
    testStream << Length3DFormat<units>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Length3D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(Unit3D<Length>(MetersLength(1),
			      MetersLength(2),
			      MetersLength(3)), MetersLength, "(1, 2, 3) m");

  OSTREAM_TEST(Unit3D<Length>(FeetLength(1),
			      FeetLength(2),
			      FeetLength(3)), FeetLength, "(1, 2, 3) ft");

  return status;
}
