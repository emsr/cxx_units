//
// $Id: QuaternionRotation3D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_QuaternionRotation3D_test_cpp
#define Units_QuaternionRotation3D_test_cpp

#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "QuaternionRotation3D.h"
#include "MatrixRotation3D.h"


namespace Units
{


//
// Test the proper operation of the public API.
//
template<typename ValueType>
bool _QuaternionRotation3D<ValueType>::test()
{
  bool status = true;


  try
  {

#define UNITS_QUATERNION_VECTOR_TEST(expr, output) \
  if (!similar(expr, output, ValueType(1e-5))) \
  { \
    std::cerr << "QuaternionRotation3D::test(): " << #expr " failed." \
              << std::endl; \
    std::cerr << "                    Expected " << (output) \
	      << ',' << std::endl; \
    std::cerr << "                    but got " << (expr) \
	      << '.' << std::endl; \
    status = false; \
  }

#define UNITS_QUATERNION_QUAT_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "QuaternionRotation3D::test(): " << #expr " failed." \
              << std::endl; \
    std::cerr << "                    Expected " << output \
	      << ',' << std::endl; \
    std::cerr << "                    but got " << expr \
	      << '.' << std::endl; \
    status = false; \
  }

  srand((unsigned)time(NULL));

  for (int i = 0; i < 1000; i++)
  {
    // Pick a random axis and angle (and insure we can never get zero-length).
    _Direction3D<ValueType> axis(2*((rand() + 1)/(ValueType)RAND_MAX) - 1,
                                 2*((rand() + 1)/(ValueType)RAND_MAX) - 1,
                                 2*((rand() + 1)/(ValueType)RAND_MAX) - 1);

    // Don't pick 0 or 360 -- they're degenerate (identity).
    _Angle angle = _DegreesAngle(358*(rand()/((ValueType)RAND_MAX)) + 1);

    _QuaternionRotation3D quat = _QuaternionRotation3D(axis, angle);

    // Test that we can get what we construct.
    if (!similar(quat.axis(), axis))
    {
      std::cerr << "QuaternionRotation3D::test(): Could not get back axis."
                << std::endl;
      std::cerr << "                    Expected " << axis
                << ',' << std::endl;
      std::cerr << "                    but got " << quat.axis()
                << '.' << std::endl;
      std::cerr << "                    (angle = "
                << _DegreesAngle(angle) << ')' << std::endl;
      status = false;
    }
    if (!similar(quat.angle(), angle, defaultTolerance()))
    {
      std::cerr << "QuaternionRotation3D::test(): Could not get back angle."
                << std::endl;
      std::cerr << "                    Expected " << _DegreesAngle(angle)
                << ", but got " << _DegreesAngle(quat.angle())
                << '.' << std::endl;
      status = false;
    }

    _QuaternionRotation3D qinv = quat.inverse();

    // Test some identities.
    UNITS_QUATERNION_QUAT_TEST(quat*(quat*qinv), quat);
    UNITS_QUATERNION_QUAT_TEST(quat*(qinv*quat), quat);
    UNITS_QUATERNION_QUAT_TEST((quat*qinv)*quat, quat);

    // Test conversion to/from cosine matrix.
    UNITS_QUATERNION_QUAT_TEST(convert(convert(quat)),
                               quat);

    // Test back/forth rotations.
    Vector3D<ValueType> vector(1, 1, 1);
    UNITS_QUATERNION_VECTOR_TEST(qinv*(quat*vector), vector);
  }

  // Test simple rotations.
  {
    _QuaternionRotation3D quat;
    quat = _QuaternionRotation3D(_Direction3D<ValueType>(0, 0, 1),
                                 _DegreesAngle( 90));
    UNITS_QUATERNION_VECTOR_TEST(quat*Vector3D<ValueType>( 1, 1, 0),
                                 Vector3D<ValueType>(-1, 1, 0));

    quat = _QuaternionRotation3D(_Direction3D<ValueType>(0, 0, 1),
                                 _DegreesAngle(180));
    UNITS_QUATERNION_VECTOR_TEST(quat*Vector3D<ValueType>( 1, 1, 0),
                                 Vector3D<ValueType>(-1,-1, 0));

    quat = _QuaternionRotation3D(_Direction3D<ValueType> (0, 0, 1),
                                 _DegreesAngle(-90));
    UNITS_QUATERNION_VECTOR_TEST(quat*Vector3D<ValueType>( 1, 1, 0),
                                 Vector3D<ValueType>( 1,-1, 0));
  }

  // TODO: Test quaternion interpolation.


  }
  catch (std::exception const & ex)
  {
    std::cerr << "QuaternionRotation3D::test(): Exception: "
              << ex.what() << std::endl;
    status = false;
  }
  catch (...)
  {
    std::cerr << "QuaternionRotation3D::test(): Unknown exception!"
              << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units

#endif  // Units_QuaternionRotation3D_test_cpp
