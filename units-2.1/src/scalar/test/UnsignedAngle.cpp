//
// $Id: UnsignedAngle.cpp,v 1.7.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the UnsignedAngle class.
//

#include <iostream>
#include <sstream>
#include "Unit.cpp"
#include "UnsignedAngle.h"


using namespace std;
using namespace Units;


//
// Test the API to the Angle class.
//
bool UnsignedAngle_test()
{
  bool status = true;

  // Test ostream ops.

#define UnsignedAngle_OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "UnsignedAngle::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                       Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  UnsignedAngle_OSTREAM_TEST(UnsignedDegreesAngle(  10.0), "10 deg");
  UnsignedAngle_OSTREAM_TEST(UnsignedDegreesAngle( 370.0), "10 deg");
  UnsignedAngle_OSTREAM_TEST(UnsignedDegreesAngle( -10.0), "350 deg");
  UnsignedAngle_OSTREAM_TEST(UnsignedDegreesAngle(-370.0), "350 deg");

  UnsignedAngle_OSTREAM_TEST(UnsignedRadiansAngle(          1.0), "1 rad");
  UnsignedAngle_OSTREAM_TEST(UnsignedRadiansAngle( 2*M_PI + 1.0), "1 rad");
  UnsignedAngle_OSTREAM_TEST(UnsignedRadiansAngle( 6.0 - 2*M_PI), "6 rad");
  UnsignedAngle_OSTREAM_TEST(UnsignedRadiansAngle( 6.0 - 4*M_PI), "6 rad");

#define UnsignedAngle_ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    cerr << "UnsignedAngle::test(): " << #expr " failed." << endl; \
    cerr << "                     Expected " << (output) \
	 << ", but got " << (DegreesAngle const &)(expr) << "." << endl; \
    status = false; \
  }

#define UnsignedAngle_BOOL_TEST(expr, output) \
  if ((expr) ^ (output)) \
  { \
    cerr << "UnsignedAngle::test(): " << #expr " failed." << endl; \
    cerr << "                     Expected " << ((output) ? "true" : "false") \
	 << ", but got " << ((expr) ? "true" : "false") << "." << endl; \
    status = false; \
  }

#define UnsignedAngle_DOUBLE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-5) \
  { \
    cerr << "SignedDegreesAngle::test(): " << #expr " failed." << endl; \
    cerr << "                            Expected " << (output) \
	 << ", but got " << (expr) << "." << endl; \
    status = false; \
  }

  //
  // Test wrap-around comparisons.
  //

  UnsignedAngle_BOOL_TEST(similar(UnsignedAngle(UnsignedDegreesAngle(359)),
                                  UnsignedAngle(UnsignedDegreesAngle(  1)),
                                  Angle(DegreesAngle(3))), true);

  UnsignedAngle_BOOL_TEST(similar(UnsignedDegreesAngle(370),
                                  UnsignedDegreesAngle( 10)), true);

  UnsignedAngle_BOOL_TEST(similar(UnsignedDegreesAngle(-10),
                                  UnsignedDegreesAngle(350)), true);

  UnsignedAngle_BOOL_TEST(UnsignedDegreesAngle(370) <
                          UnsignedDegreesAngle(180), true);
  UnsignedAngle_BOOL_TEST(UnsignedDegreesAngle(-10) >
                          UnsignedDegreesAngle(180), true);

  UnsignedAngle_BOOL_TEST(UnsignedDegreesAngle(370) <=
                          UnsignedDegreesAngle(180), true);
  UnsignedAngle_BOOL_TEST(UnsignedDegreesAngle(-10) >=
                          UnsignedDegreesAngle(180), true);

  //
  // Test wrap-around arithmetic.
  //
  UnsignedAngle_ANGLE_TEST(UnsignedDegreesAngle( 10) -
                           UnsignedDegreesAngle(350), SignedDegreesAngle( 20));

  UnsignedAngle_ANGLE_TEST(UnsignedDegreesAngle(350) -
                           UnsignedDegreesAngle( 10), SignedDegreesAngle(-20));

  return status;
}
