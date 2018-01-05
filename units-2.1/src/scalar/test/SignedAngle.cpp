//
// $Id: SignedAngle.cpp,v 1.6.4.3 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the SignedAngle class.
//

#include <iostream>
#include <sstream>
#include "Unit.h"
#include "SignedAngle.h"


using namespace std;
using namespace Units;


//
// Test the API to the Angle class.
//
bool SignedAngle_test()
{
  bool status = true;

  // Test ostream ops.

#define SignedAngle_OSTREAM_TEST(expr, output) \
  { \
    ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      cerr << "SignedAngle::test(): " \
	   << "operator<<(ostream, " #expr ") failed." << endl; \
      cerr << "                     Expected `" << output \
	   << "', but got `" << testStream.str() << "'." << endl; \
      status = false; \
    } \
  }

  SignedAngle_OSTREAM_TEST(SignedDegreesAngle(  10.0), "10 deg");
  SignedAngle_OSTREAM_TEST(SignedDegreesAngle( 370.0), "10 deg");
  SignedAngle_OSTREAM_TEST(SignedDegreesAngle( -10.0), "-10 deg");
  SignedAngle_OSTREAM_TEST(SignedDegreesAngle(-370.0), "-10 deg");

  SignedAngle_OSTREAM_TEST(SignedRadiansAngle(          1.0), "1 rad");
  SignedAngle_OSTREAM_TEST(SignedRadiansAngle( 2*M_PI + 1.0), "1 rad");
  SignedAngle_OSTREAM_TEST(SignedRadiansAngle(         -1.0), "-1 rad");
  SignedAngle_OSTREAM_TEST(SignedRadiansAngle(-2*M_PI - 1.0), "-1 rad");


#define SignedAngle_ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    cerr << "SignedAngle::test(): " << #expr " failed." << endl; \
    cerr << "                     Expected " << (output) \
	 << ", but got " << DegreesAngle(expr) << "." << endl; \
    status = false; \
  }

#define SignedAngle_BOOL_TEST(expr, output) \
  if ((expr) ^ (output)) \
  { \
    cerr << "SignedAngle::test(): " << #expr " failed." << endl; \
    cerr << "                     Expected " << ((output) ? "true" : "false") \
	 << ", but got " << ((expr) ? "true" : "false") << "." << endl; \
    status = false; \
  }

#define SignedAngle_DOUBLE_TEST(expr, output) \
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

  SignedAngle_BOOL_TEST(similar(SignedAngle(SignedDegreesAngle(-179)),
                                SignedAngle(SignedDegreesAngle( 179)),
                                Angle(DegreesAngle(3))), true);

  SignedAngle_BOOL_TEST(similar(SignedDegreesAngle( 185),
                                SignedDegreesAngle(-175)), true);
  SignedAngle_BOOL_TEST(similar(SignedDegreesAngle(-185),
                                SignedDegreesAngle( 175)), true);

  SignedAngle_BOOL_TEST(SignedDegreesAngle( 185) <
                        SignedDegreesAngle( 0), true);
  SignedAngle_BOOL_TEST(SignedDegreesAngle(-185) >
                        SignedDegreesAngle( 0), true);

  SignedAngle_BOOL_TEST(SignedDegreesAngle( 185) <=
                        SignedDegreesAngle( 0), true);
  SignedAngle_BOOL_TEST(SignedDegreesAngle(-185) >=
                        SignedDegreesAngle( 0), true);

  //
  // Test wrap-around arithmetic.
  //

  SignedAngle_ANGLE_TEST(SignedDegreesAngle( 170) -
                         SignedDegreesAngle(-170), SignedDegreesAngle(-20));

  SignedAngle_ANGLE_TEST(SignedDegreesAngle(-170) -
                         SignedDegreesAngle( 170), SignedDegreesAngle( 20));

  //
  // Test +=, -= ops.
  //
  SignedAngle_ANGLE_TEST(SignedDegreesAngle(170) += DegreesAngle(20),
                         SignedDegreesAngle(-170));
  SignedAngle_ANGLE_TEST(SignedDegreesAngle(-170) -= DegreesAngle(20),
                         SignedDegreesAngle(170));

  return status;
}
