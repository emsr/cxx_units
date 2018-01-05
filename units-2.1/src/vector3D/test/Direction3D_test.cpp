//
// $Id: Direction3D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Direction3D_test_cpp
#define Units_Direction3D_test_cpp

#include <math.h>
#include <iostream>
#include <sstream>
#include "Direction3D.h"


namespace Units
{


//
// Test the API to the Length class.
//
template <typename ValueType>
bool _Direction3D<ValueType>::test()
{
  bool status = true;

  try
  {

  // Test iostream ops.

#define UNITS_DIRECTION3D_OSTREAM_TEST(expr, output) \
  { \
    std::ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      std::cerr << "Direction3D::test(): " \
	        << "operator<<(ostream, " #expr ") failed." << std::endl; \
      std::cerr << "                     Expected `" << output \
	        << "', but got `" << testStream.str() << "'." << std::endl; \
      status = false; \
    } \
  }

  UNITS_DIRECTION3D_OSTREAM_TEST(_Direction3D(1, 0, 0), "(1, 0, 0)");
  UNITS_DIRECTION3D_OSTREAM_TEST(_Direction3D(0, 1, 0), "(0, 1, 0)");
  UNITS_DIRECTION3D_OSTREAM_TEST(_Direction3D(0, 0, 1), "(0, 0, 1)");


  if (!similar(_Direction3D(1, 1, 1),
	       _Direction3D(1, 1, 1)))
  {
    std::cerr << "Direction3D::test(): "
	      << "similar() between identical Direction3Ds failed."
              << std::endl;
    status = false;
  }
  if (!similar(_Direction3D(1, 1, 1),
	       _Direction3D(1.0000005, 1, 1)))
  {
    std::cerr << "Direction3D::test(): "
              << "similar() between similar Direction3Ds failed."
              << std::endl;
    status = false;
  }
  if (similar(_Direction3D(1, 1, 1),
	      _Direction3D(0, 0, 1)))
  {
    std::cerr << "Direction3D::test(): "
              << "similar() between unsimilar Direction3Ds failed."
              << std::endl;
    status = false;
  }

  if (_Direction3D(1, 1, 1) == _Direction3D(0, 0, 1))
  {
    std::cerr << "Direction3D::test(): operator==() failed." << std::endl;
    status = false;
  }
  if (_Direction3D(1, 1, 1) != _Direction3D(1, 1, 1))
  {
    std::cerr << "Direction3D::test(): operator!=() failed." << std::endl;
    status = false;
  }


#define UNITS_DIRECTION3D_DIR_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Direction3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " << (output) \
	      << ", but got " << (expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_DIRECTION3D_VECTOR_TEST(expr, output) \
  if (!similar(expr, output, ValueType(1e-6))) \
  { \
    std::cerr << "Direction3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " << (output) \
	      << ", but got " << (expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_DIRECTION3D_DOUBLE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-6) \
  { \
    std::cerr << "Direction3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " << output \
	      << ", but got " << (expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_DIRECTION3D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output, _Direction3D::defaultTolerance())) \
  { \
    std::cerr << "Direction3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " \
	      << _DegreesAngle(output) << ", but got " \
	      << _DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }


  UNITS_DIRECTION3D_DIR_TEST(-_Direction3D( 1, 1, 1),
                             _Direction3D(-1,-1,-1));

  UNITS_DIRECTION3D_DOUBLE_TEST(_Direction3D(1, 1, 1) *
                                _Direction3D(1, 1, 1), 1);

  UNITS_DIRECTION3D_DOUBLE_TEST(_Direction3D(1, 1, 1) *
                                _Direction3D(1,-1, 0), 0);

  UNITS_DIRECTION3D_DIR_TEST(_Direction3D( 1, 1, 1) %
                             _Direction3D(-1,-1, 1),
                             _Direction3D(1, -1, 0));

  _Direction3D testVector(1, 2, 3);
  testVector._vector *= 2; // Double it to force a non-unit magnitude.
  UNITS_DIRECTION3D_DIR_TEST(testVector.normalize(), _Direction3D(1, 2, 3));

  UNITS_DIRECTION3D_DIR_TEST(Units::direction(Vector3D<ValueType>(2, 2, 2)),
                                _Direction3D(1, 1, 1));

  UNITS_DIRECTION3D_VECTOR_TEST(Units::direction(Vector3D<ValueType>(1, 2, 2)) *
                                ValueType(3.0),
                                Vector3D<ValueType>(1, 2, 2));

  UNITS_DIRECTION3D_ANGLE_TEST(angle(_Direction3D( 1, 1, 1),
                                     _Direction3D( 1, 1, 1)),
                               _DegreesAngle(0));
  UNITS_DIRECTION3D_ANGLE_TEST(angle(_Direction3D( 1, 1, 1),
                                     _Direction3D(-1,-1,-1)),
                               _DegreesAngle(180));
  UNITS_DIRECTION3D_ANGLE_TEST(angle(_Direction3D( 1, 1, 1),
                                     _Direction3D( 1,-1, 0)),
                               _DegreesAngle(90));

  UNITS_DIRECTION3D_DIR_TEST(midpoint(_Direction3D( 1, 1, 1),
                                      _Direction3D(-1,-1, 1)),
                             _Direction3D(0, 0, 1));

  UNITS_DIRECTION3D_DIR_TEST(interpolate(_Direction3D( 1, 1, 1),
                                         _Direction3D(-1,-1, 1),
                                         ValueType(0.0)),
                             _Direction3D(1, 1, 1));

  UNITS_DIRECTION3D_DIR_TEST(interpolate(_Direction3D( 1, 1, 1),
                                         _Direction3D(-1,-1, 1),
                                         ValueType(0.5)),
                             _Direction3D(0, 0, 1));

  UNITS_DIRECTION3D_DIR_TEST(interpolate(_Direction3D( 1, 1, 1),
                                         _Direction3D(-1,-1, 1),
                                         ValueType(1.0)),
                             _Direction3D(-1,-1, 1));

  }
  catch (std::exception const & ex)
  {
    std::cerr << "Direction3D::test(): Exception: " << ex.what() << std::endl;
    status = false;
  }
  catch (...)
  {
    std::cerr << "Unknown exception!" << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units

#endif  // Units_Direction3D_test_cpp
