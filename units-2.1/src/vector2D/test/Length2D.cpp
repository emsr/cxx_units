//
// $Id: Length2D.cpp,v 1.5.4.4 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Length2D.h"
#include "Unit2D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Length2D class.
//
bool Length2D_test()
{
  bool status = generic2DTest<FeetLength>("Length");


  // Test iostream ops.

#define OSTREAM_TEST(expr, units, output) \
  { \
    ostringstream testStream; \
    testStream << Length2DFormat<units>(expr); \
    if (testStream.str() != output) \
    { \
      cerr << "Length2D::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }


  OSTREAM_TEST(Length2D(FeetLength(1),
                        FeetLength(2)), FeetLength, "(1, 2) ft");

  return status;
}
