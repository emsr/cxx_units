//
// $Id: Vector3D_test.cpp,v 1.1.2.1 2007-10-01 05:44:31 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Vector3D_test_cpp
#define Units_Vector3D_test_cpp

#include <iostream>
#include <stdexcept>
#include "Vector3D.h"


namespace Units
{


//
// Test the API to the Vector3D class.
//
template<typename ValueType>
bool Vector3D<ValueType>::test()
{
  bool status = true;
  Vector3D<ValueType> vector;
  ValueType tolerance(0.000001);

  try
  {

#define UNITS_VECTOR3D_VECTOR(x, y, z)  Vector3D<ValueType>(x, y, z)


  if (!similar(UNITS_VECTOR3D_VECTOR(1, 2, 3),
               UNITS_VECTOR3D_VECTOR(1, 2, 3), tolerance))
  {
    std::cerr << "Vector3D::test(): "
              << "similar() between identical Vector3D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (!similar(UNITS_VECTOR3D_VECTOR(1, 2, 3),
               UNITS_VECTOR3D_VECTOR(1.0000005, 2, 3), tolerance))
  {
    std::cerr << "Vector3D::test(): "
              << "similar() between similar Vector3D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (!similar(UNITS_VECTOR3D_VECTOR(1, 2, 3),
               UNITS_VECTOR3D_VECTOR(1.5, 2, 3),
               ValueType(1.0)))
  {
    std::cerr << "Vector3D::test(): "
              << "similar() between similar Vector3D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (similar(UNITS_VECTOR3D_VECTOR(1, 2, 3),
              UNITS_VECTOR3D_VECTOR(3, 2, 1), tolerance))
  {
    std::cerr << "Vector3D::test(): "
              << "similar() between unsimilar Vector3D<ValueType>s failed."
              << std::endl;
    status = false;
  }

  if (UNITS_VECTOR3D_VECTOR(1, 2, 3) == UNITS_VECTOR3D_VECTOR(3, 2, 1))
  {
    std::cerr << "Vector3D::test(): operator==() failed." << std::endl;
    status = false;
  }
  if (UNITS_VECTOR3D_VECTOR(1, 2, 3) != UNITS_VECTOR3D_VECTOR(1, 2, 3))
  {
    std::cerr << "Vector3D::test(): operator!=() failed." << std::endl;
    status = false;
  }


#define UNITS_VECTOR3D_VECTOR_TEST(expr, output) \
  if (!similar(expr, output, tolerance)) \
  { \
    std::cerr << "Vector3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                Expected " << (output) \
              << ',' << std::endl; \
    std::cerr << "                but got " << (expr) \
	      << '.' << std::endl; \
    status = false; \
  }

#define UNITS_VECTOR3D_MAGNITUDE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-6) \
  { \
    std::cerr << "Vector3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                Expected " \
	      << (output) << ", but got " \
	      << (expr) << '.' << std::endl; \
    status = false; \
  }

  // Need to open up the tolerance for float angle().
#define UNITS_VECTOR3D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output, RadiansAngle(1e-3)))       \
  { \
    std::cerr << "Vector3D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                Expected " \
	      << DegreesAngle(output) << ", but got " \
	      << DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }

  // Test dot product.
  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(1, 1, 1) *
                                UNITS_VECTOR3D_VECTOR(1, 1, 1), 3);

  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(1, 1, 1) *
                                UNITS_VECTOR3D_VECTOR(1,-1, 0), 0);

  // Test cross product.
  UNITS_VECTOR3D_VECTOR_TEST(UNITS_VECTOR3D_VECTOR( 1, 1, 1) %
                             UNITS_VECTOR3D_VECTOR(-1,-1, 1),
                             UNITS_VECTOR3D_VECTOR(2, -2, 0));

  // Test arithmetic.
  UNITS_VECTOR3D_VECTOR_TEST(2.0 * UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(2, 4, 6));

  UNITS_VECTOR3D_VECTOR_TEST(UNITS_VECTOR3D_VECTOR(1, 2, 3) * 2.0,
                             UNITS_VECTOR3D_VECTOR(2, 4, 6));

  UNITS_VECTOR3D_VECTOR_TEST(UNITS_VECTOR3D_VECTOR(2, 4, 6) / 2.0,
                             UNITS_VECTOR3D_VECTOR(1, 2, 3));


  vector = UNITS_VECTOR3D_VECTOR(1, 2, 3);
  UNITS_VECTOR3D_VECTOR_TEST(vector *= 2.0, UNITS_VECTOR3D_VECTOR(2, 4, 6));
  UNITS_VECTOR3D_VECTOR_TEST(vector /= 2.0, UNITS_VECTOR3D_VECTOR(1, 2, 3));


  UNITS_VECTOR3D_VECTOR_TEST(-UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(-1, -2, -3));

  UNITS_VECTOR3D_VECTOR_TEST(UNITS_VECTOR3D_VECTOR(1, 2, 3) +
                             UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(2, 4, 6));

  UNITS_VECTOR3D_VECTOR_TEST(UNITS_VECTOR3D_VECTOR(2, 4, 6) -
                             UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(1, 2, 3));


  vector = UNITS_VECTOR3D_VECTOR(1, 2, 3);
  UNITS_VECTOR3D_VECTOR_TEST(vector += UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(2, 4, 6));

  UNITS_VECTOR3D_VECTOR_TEST(vector -= UNITS_VECTOR3D_VECTOR(1, 2, 3),
                             UNITS_VECTOR3D_VECTOR(1, 2, 3));


  UNITS_VECTOR3D_MAGNITUDE_TEST(Units::magnitude(UNITS_VECTOR3D_VECTOR(1, 2, 2)), 3);
  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(1, 2, 2).magnitude(),  3);


  UNITS_VECTOR3D_ANGLE_TEST(angle( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                   UNITS_VECTOR3D_VECTOR(1, 2, 3)),
                            DegreesAngle(0));

  UNITS_VECTOR3D_ANGLE_TEST(angle( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                   -UNITS_VECTOR3D_VECTOR(1, 2, 3)),
                            DegreesAngle(180));

  UNITS_VECTOR3D_ANGLE_TEST(angle( UNITS_VECTOR3D_VECTOR(1, 0, 0),
                                   UNITS_VECTOR3D_VECTOR(0, 1, 0)),
                            DegreesAngle(90));


  UNITS_VECTOR3D_MAGNITUDE_TEST(distance(UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                         UNITS_VECTOR3D_VECTOR(1, 2, 3)), 0);

  UNITS_VECTOR3D_VECTOR_TEST(midpoint( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                      -UNITS_VECTOR3D_VECTOR(1, 2, 3)),
                             UNITS_VECTOR3D_VECTOR(0, 0, 0));


  UNITS_VECTOR3D_VECTOR_TEST(interpolate( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                         -UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                          ValueType(0.0)),
                             UNITS_VECTOR3D_VECTOR(1, 2, 3));

  UNITS_VECTOR3D_VECTOR_TEST(interpolate( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                         -UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                          ValueType(0.5)),
                             UNITS_VECTOR3D_VECTOR(0, 0, 0));

  UNITS_VECTOR3D_VECTOR_TEST(interpolate( UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                         -UNITS_VECTOR3D_VECTOR(1, 2, 3),
                                          ValueType(1.0)),
                             -UNITS_VECTOR3D_VECTOR(1, 2, 3));


  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(2, 4, 6).distanceToLine(UNITS_VECTOR3D_VECTOR(0, 0, 0),
                                                                              UNITS_VECTOR3D_VECTOR(1, 2, 3)), 0);

  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(2, 3, 4).distanceToLine(UNITS_VECTOR3D_VECTOR(0, 0, 0),
                                                                              UNITS_VECTOR3D_VECTOR(1, 0, 0)), 5);


  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(2, 4, 6).distanceToSegment(UNITS_VECTOR3D_VECTOR(0, 0, 0),
                                                                                 UNITS_VECTOR3D_VECTOR(1, 2, 3)),
                                Units::magnitude(UNITS_VECTOR3D_VECTOR(1, 2, 3)));

  UNITS_VECTOR3D_MAGNITUDE_TEST(UNITS_VECTOR3D_VECTOR(0.5, 3, 4).distanceToSegment(UNITS_VECTOR3D_VECTOR(0, 0, 0),
                                                                                   UNITS_VECTOR3D_VECTOR(1, 0, 0)), 5);


  UNITS_VECTOR3D_VECTOR_TEST(planeNormal(UNITS_VECTOR3D_VECTOR(0, 0, 0),
                                         UNITS_VECTOR3D_VECTOR(1, 0, 0),
                                         UNITS_VECTOR3D_VECTOR(0, 1, 0)),
                             UNITS_VECTOR3D_VECTOR(0, 0, 1));

  }
  catch (std::exception const & ex)
  {
    std::cerr << "Vector3D::test(): Exception: " << ex.what() << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units


#endif // Units_Vector3D_test_cpp
