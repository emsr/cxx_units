//
// $Id: Direction2D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Direction2D_test_cpp
#define Units_Direction2D_test_cpp

#include <iostream>
#include <sstream>
#include "Direction2D.h"


namespace Units
{


//
// Test the API to the _Direction2D class.
//
template <typename ValueType>
bool _Direction2D<ValueType>::test()
{
  bool status = true;

  try
  {

  // Test iostream ops.

#define UNITS_DIRECTION2D_OSTREAM_TEST(expr, output) \
  { \
    std::ostringstream testStream; \
    testStream << (expr); \
    if (testStream.str() != output) \
    { \
      std::cerr << "Direction2D::test(): " \
	        << "operator<<(ostream, " #expr ") failed." << std::endl; \
      std::cerr << "                     Expected `" << output \
	        << "', but got `" << testStream.str() << "'." << std::endl; \
      status = false; \
    } \
  }

  UNITS_DIRECTION2D_OSTREAM_TEST(_Direction2D(1, 0), "(1, 0)");
  UNITS_DIRECTION2D_OSTREAM_TEST(_Direction2D(0, 1), "(0, 1)");


  if (!similar(_Direction2D(1, 1),
	       _Direction2D(1, 1)))
  {
    std::cerr << "Direction2D::test(): "
              << "similar() between identical Direction2Ds failed." 
              << std::endl;
    status = false;
  }
  if (!similar(_Direction2D(1, 1),
	       _Direction2D(1.0000005, 1)))
  {
    std::cerr << "Direction2D::test(): "
              << "similar() between similar Direction2Ds failed."
              << std::endl;
    status = false;
  }
  if (similar(_Direction2D(1, 1),
	      _Direction2D(0, 1)))
  {
    std::cerr << "Direction2D::test(): "
              << "similar() between unsimilar Direction2Ds failed."
              << std::endl;
    status = false;
  }

  if (_Direction2D(1, 1) == _Direction2D(0, 1))
  {
    std::cerr << "Direction2D::test(): operator==() failed." << std::endl;
    status = false;
  }
  if (_Direction2D(1, 1) != _Direction2D(1, 1))
  {
    std::cerr << "Direction2D::test(): operator!=() failed." << std::endl;
    status = false;
  }


#define UNITS_DIRECTION2D_VECTOR_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Direction2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " << output \
	      << ", but got " << (expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_DIRECTION2D_DOUBLE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-6) \
  { \
    std::cerr << "Direction2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " << output \
	      << ", but got " << (expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_DIRECTION2D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output, _Direction2D::defaultTolerance())) \
  { \
    std::cerr << "Direction2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                     Expected " \
	      << _DegreesAngle(output) << ", but got " \
	      << _DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }


  UNITS_DIRECTION2D_VECTOR_TEST(-_Direction2D( 1, 1),
                                _Direction2D(-1,-1));

  UNITS_DIRECTION2D_DOUBLE_TEST(_Direction2D(1, 1) *
                                _Direction2D(1, 1), 1);

  UNITS_DIRECTION2D_DOUBLE_TEST(_Direction2D(1, 1) *
                                _Direction2D(1,-1), 0);

  UNITS_DIRECTION2D_DOUBLE_TEST(_Direction2D(1, 1) %
                                _Direction2D(1,-1), -1);

  _Direction2D testVector(3, 4);
  testVector._vector *= 2; // Double it to force a non-unit magnitude.
  UNITS_DIRECTION2D_VECTOR_TEST(testVector.normalize(),
                                _Direction2D(3, 4));

  UNITS_DIRECTION2D_ANGLE_TEST(angle(_Direction2D( 1, 1),
                                     _Direction2D( 1, 1)), _DegreesAngle(0));
  UNITS_DIRECTION2D_ANGLE_TEST(angle(_Direction2D( 1, 1),
                                     _Direction2D(-1,-1)), _DegreesAngle(180));
  UNITS_DIRECTION2D_ANGLE_TEST(angle(_Direction2D( 1, 1),
                                     _Direction2D( 1,-1)), _DegreesAngle(90));

  UNITS_DIRECTION2D_VECTOR_TEST(midpoint(_Direction2D(1, 1),
                                         _Direction2D(1,-1)),
                                _Direction2D(1, 0));

  UNITS_DIRECTION2D_VECTOR_TEST(interpolate(_Direction2D(1, 1),
                                            _Direction2D(1,-1),
                                            ValueType(0.0)),
                                _Direction2D(1, 1));

  UNITS_DIRECTION2D_VECTOR_TEST(interpolate(_Direction2D(1, 1),
                                            _Direction2D(1,-1),
                                            ValueType(0.5)),
                                _Direction2D(1, 0));

  UNITS_DIRECTION2D_VECTOR_TEST(interpolate(_Direction2D(1, 1),
                                            _Direction2D(1,-1),
                                            ValueType(1.0)),
                                _Direction2D(1,-1));

  }
  catch (std::exception const & ex)
  {
    std::cerr << "Direction2D::test(): Exception: " << ex.what() << std::endl;
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


#endif  // Units_Direction2D_test_cpp
