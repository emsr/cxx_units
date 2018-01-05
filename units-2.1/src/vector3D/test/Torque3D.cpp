//
// $Id: Torque3D.cpp,v 1.6.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Torque3D class.
//

#include <math.h>
#include <iostream>
#include <sstream>
#include "Torque3D.h"
#include "Force3D.h"
#include "Length3D.h"
#include "Unit3D.cpp"


using namespace Units;
using namespace std;



//
// Test the API to the Torque3D class.
//
bool Torque3D_test()
{
  //
  // There is no specific torque class to use with the genericTest.
  //
  bool status = true;


  // Test iostream ops.

#define OSTREAM_TEST(F, L, x, y, z, output) \
  { \
    ostringstream testStream; \
    Torque3D torque3D(F(x)*L(1), F(y)*L(1), F(z)*L(1)); \
    testStream << Torque3DFormat<F, L>(torque3D); \
    if (testStream.str() != output) \
    { \
      cerr << "Torque3D::test(): " \
	   << "operator<<(ostream, " #F ", " #L ") failed." << endl; \
      cerr << "                  Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  OSTREAM_TEST(NewtonsForce, FeetLength,   1, 2, 3, "(1, 2, 3) N-ft");
  OSTREAM_TEST(NewtonsForce, MetersLength, 1, 2, 3, "(1, 2, 3) N-m");

  OSTREAM_TEST(PoundsForce, FeetLength,    1, 2, 3, "(1, 2, 3) lb-ft");
  OSTREAM_TEST(PoundsForce, MetersLength,  1, 2, 3, "(1, 2, 3) lb-m");

  //
  // Test interaction with Length and Force.
  //
  Length3D length(MetersLength(1),
                  MetersLength(1),
                  MetersLength(1));

  Force3D force(NewtonsForce(-1),
                NewtonsForce(-1),
                NewtonsForce( 1));

  Torque3D torque(MetersLength(2)*NewtonsForce(1),
                  MetersLength(-2)*NewtonsForce(1),
                  Torque(zero()));

  if (!similar(length%force, torque))
  {
    cerr << "Torque3D::test(): operator%(Length, Force) failed." << endl;
    status = false;
  }
  if (!similar(force%length, -torque))
  {
    cerr << "Torque3D::test(): operator%(Force, Length) failed." << endl;
    status = false;
  }

  return status;
}
