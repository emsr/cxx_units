//
// $Id: MatrixRotation3D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_MatrixRotation3D_test_cpp
#define Units_MatrixRotation3D_test_cpp

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "MatrixRotation3D.h"
#include "QuaternionRotation3D.h"
#include "Rotation3D_convert.h"


namespace Units
{


//
// Test the proper operation of the public API.
//
template<typename ValueType>
bool _MatrixRotation3D<ValueType>::test()
{
  bool status = true;


  try
  {

#define UNITS_MATIXROTATION_VECTOR_TEST(expr, output) \
  if (!similar(expr, output, ValueType(1e-6))) \
  { \
    std::cerr << "MatrixRotation3D::test(): " << #expr " failed." \
              << std::endl; \
    std::cerr << "                    Expected " << (output) \
	      << ',' << std::endl; \
    std::cerr << "                    but got " << (expr) \
	      << '.' << std::endl; \
    status = false; \
  }

#define UNITS_MATIXROTATION_MATRIX_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "MatrixRotation3D::test(): " << #expr " failed." \
              << std::endl; \
    std::cerr << "                    Expected " << output \
	      << ',' << std::endl; \
    std::cerr << "                    but got " << expr \
	      << '.' << std::endl; \
    status = false; \
  }

  srand((unsigned)time(NULL));

  for (int j = 1; j < 1000; j++)
  {
    // Pick a random axis and angle (and insure we can never get zero-length).
    _Direction3D<ValueType> axis(2*((rand() + 1)/(ValueType)RAND_MAX) - 1,
                                 2*((rand() + 1)/(ValueType)RAND_MAX) - 1,
                                 2*((rand() + 1)/(ValueType)RAND_MAX) - 1);

    // Don't pick 0 or 360 -- they're degenerate (identity).
    _Angle angle = _DegreesAngle(358*(rand()/((ValueType)RAND_MAX)) + 1);

    // 180 degis singular -- it has two solutions
    if (similar(angle, _DegreesAngle(180), _DegreesAngle(0.1)))
    {
      continue;
    }

    _MatrixRotation3D matrix = _MatrixRotation3D(axis, angle);

    // Test that we can get what we construct.
    if (angle > _DegreesAngle(180))
    {
      axis  = -axis;
      angle = _DegreesAngle(360) - angle;
    }
    if (!similar(matrix.axis(), axis, _DegreesAngle(1)))  // HACK for float
    {
      std::cerr << "MatrixRotation3D::test(): Could not get back axis."
                << std::endl;
      std::cerr << "                    Expected " << axis
                << ',' << std::endl;
      std::cerr << "                    but got " << matrix.axis()
                << '.' << std::endl;
      std::cerr << "                    angle = "
                << _DegreesAngle(angle) << std::endl;
      _Angle error = matrix.axis().angleTo(axis);
      std::cerr << "                    error = "
                << _DegreesAngle(error) << std::endl;
      status = false;
    }
    if (!similar(matrix.angle(), angle, defaultTolerance()))
    {
      std::cerr << "MatrixRotation3D::test(): Could not get back angle."
                << std::endl;
      std::cerr << "                    Expected " << _DegreesAngle(angle)
                << ", but got " << _DegreesAngle(matrix.angle())
                << '.' << std::endl;
      status = false;
    }

    _MatrixRotation3D minv = matrix.inverse();

    // Test some identities.
    UNITS_MATIXROTATION_MATRIX_TEST(matrix*(matrix*minv), matrix);
    UNITS_MATIXROTATION_MATRIX_TEST(matrix*(minv*matrix), matrix);
    UNITS_MATIXROTATION_MATRIX_TEST((matrix*minv)*matrix, matrix);

    // Test conversion to/from unit quaternion.
    UNITS_MATIXROTATION_MATRIX_TEST(convert(convert(matrix)),
                                    matrix);

    // Test back/forth rotations.
    Vector3D<ValueType> vector(1, 1, 1);
    UNITS_MATIXROTATION_VECTOR_TEST(minv*(matrix*vector), vector);
  }

  // Test simple rotations.
  {
    _MatrixRotation3D matrix;
    matrix = _MatrixRotation3D(_Direction3D<ValueType> (0, 0, 1),
                               _DegreesAngle( 90));
    UNITS_MATIXROTATION_VECTOR_TEST(matrix*Vector3D<ValueType>( 1, 1, 0),
                                    Vector3D<ValueType>(-1, 1, 0));

    matrix = _MatrixRotation3D(_Direction3D<ValueType> (0, 0, 1),
                               _DegreesAngle(180));
    UNITS_MATIXROTATION_VECTOR_TEST(matrix*Vector3D<ValueType>( 1, 1, 0),
                                    Vector3D<ValueType>(-1,-1, 0));

    matrix = _MatrixRotation3D(_Direction3D<ValueType> (0, 0, 1),
                               _DegreesAngle(-90));
    UNITS_MATIXROTATION_VECTOR_TEST(matrix*Vector3D<ValueType>( 1, 1, 0),
                                    Vector3D<ValueType>( 1,-1, 0));
  }

  // TODO: Test matrix interpolation.


  }
  catch (std::exception const & ex)
  {
    std::cerr << "MatrixRotation3D::test(): Exception: "
              << ex.what() << std::endl;
    status = false;
  }
  catch (...)
  {
    std::cerr << "MatrixRotation3D::test(): Unknown exception!" << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units

#endif  // Units_MatrixRotation3D_test_cpp
