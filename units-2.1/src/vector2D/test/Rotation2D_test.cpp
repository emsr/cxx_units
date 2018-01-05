//
// $Id: Rotation2D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Rotation2D_test_cpp
#define Units_Rotation2D_test_cpp

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Rotation2D.h"


namespace Units
{


///
/// Test the proper operation of the public API.
///
template <typename ValueType>
bool _Rotation2D<ValueType>::test()
{
  bool status = true;


#define TEST(expr, output, tolerance) \
  if (!similar(expr, output, tolerance)) \
  { \
    std::cerr << "Rotation2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                    Expected " << (output) << ',' << std::endl; \
    std::cerr << "                    but got "  << (expr)   << '.' << std::endl; \
    status = false; \
  }

  // Test simple rotations.
  {
    _Rotation2D rotation = _Rotation2D::identity();
    rotation = _Rotation2D(_DegreesAngle( 90));
    TEST(rotation*Vector2D<ValueType>( 1, 1),
         Vector2D<ValueType>(-1, 1),
         ValueType(1e-6));

    rotation = _Rotation2D(_DegreesAngle(180));
    TEST(rotation*Vector2D<ValueType>( 1, 1),
         Vector2D<ValueType>(-1,-1),
         ValueType(1e-6));

    rotation = _Rotation2D(_DegreesAngle(-90));
    TEST(rotation*Vector2D<ValueType>( 1, 1),
         Vector2D<ValueType>( 1,-1),
         ValueType(1e-6));
  }

  // Seed the random number generator.
  srand((unsigned)time(NULL));

  for (int i = 0; i < 1000; i++)
  {
    _Angle angle = _DegreesAngle(360*(rand()*1/(double)RAND_MAX));

    _Rotation2D rotation = _Rotation2D(angle);

    // Test that we can get what we construct.
    if (!similar(_SignedAngle(rotation.angle()),
		 _SignedAngle(angle)))
    {
      std::cerr << "Rotation2D::test(): Could not get back angle." << std::endl;
      std::cerr << "                    Expected " << _DegreesAngle(angle)
                << ", but got " << _DegreesAngle(rotation.angle())
                << '.' << std::endl;
      status = false;
    }

    _Rotation2D rinv  = rotation.inverse();

    // Test some identities.
    TEST(rotation*(rotation*rinv), rotation, _Angle::defaultTolerance());
    TEST(rotation*(rinv*rotation), rotation, _Angle::defaultTolerance());
    TEST((rotation*rinv)*rotation, rotation, _Angle::defaultTolerance());

    // Test back/forth rotations.
    Vector2D<ValueType> vector(1, 1);
    TEST(rinv*(rotation*vector), vector, ValueType(1e-6));
  }

  return status;
}


} // namespace Units


#endif  // Units_Rotation2D_test_cpp
