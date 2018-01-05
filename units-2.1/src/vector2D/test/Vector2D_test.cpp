//
// $Id: Vector2D_test.cpp,v 1.1.2.1 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Vector2D_test_cpp
#define Units_Vector2D_test_cpp

#include <iostream>
#include "Vector2D.h"


namespace Units
{


//
// Test the API to the Vector2D class.
//
template <typename ValueType>
bool Vector2D<ValueType>::test()
{
  bool status = true;
  Vector2D<ValueType> vector;
  ValueType tolerance(0.000001);

  try
  {

#define UNITS_VECTOR2D_VECTOR(x, y)  Vector2D<ValueType>(x, y)


  if (!similar(UNITS_VECTOR2D_VECTOR(1, 2),
               UNITS_VECTOR2D_VECTOR(1, 2), tolerance))
  {
    std::cerr << "Vector2D::test(): "
              << "similar() between identical Vector2D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (!similar(UNITS_VECTOR2D_VECTOR(1, 2),
               UNITS_VECTOR2D_VECTOR(1.0000005, 2), tolerance))
  {
    std::cerr << "Vector2D::test(): "
              << "similar() between similar Vector2D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (!similar(UNITS_VECTOR2D_VECTOR(1, 2),
               UNITS_VECTOR2D_VECTOR(1.5, 2),
               ValueType(1.0)))
  {
    std::cerr << "Vector2D::test(): "
              << "similar() between similar Vector2D<ValueType>s failed."
              << std::endl;
    status = false;
  }
  if (similar(UNITS_VECTOR2D_VECTOR(1, 2),
              UNITS_VECTOR2D_VECTOR(3, 2), tolerance))
  {
    std::cerr << "Vector2D::test(): "
              << "similar() between unsimilar Vector2D<ValueType>s failed."
              << std::endl;
    status = false;
  }

  if (UNITS_VECTOR2D_VECTOR(1, 2) == UNITS_VECTOR2D_VECTOR(3, 2))
  {
    std::cerr << "Vector2D::test(): operator==() failed." << std::endl;
    status = false;
  }
  if (UNITS_VECTOR2D_VECTOR(1, 2) != UNITS_VECTOR2D_VECTOR(1, 2))
  {
    std::cerr << "Vector2D::test(): operator!=() failed." << std::endl;
    status = false;
  }


#define UNITS_VECTOR2D_VECTOR_TEST(expr, output) \
  if (!(expr).similarTo(output, tolerance)) \
  { \
    std::cerr << "Vector2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                      Expected " << (output) \
              << ',' << std::endl; \
    std::cerr << "                      but got " << (expr) \
	      << '.' << std::endl; \
    status = false; \
  }

#define UNITS_VECTOR2D_MAGNITUDE_TEST(expr, output) \
  if (fabs((expr) - (output)) > 1e-6) \
  { \
    std::cerr << "Vector2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                      Expected " \
	      << (output) << ", but got " \
	      << (expr) << '.' << std::endl; \
    status = false; \
  }

#define UNITS_VECTOR2D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Vector2D::test(): " << #expr " failed." << std::endl; \
    std::cerr << "                      Expected " \
	      << DegreesAngle(output) << ", but got " \
	      << DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }

  // Test dot product.
  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(1, 1) *
                                UNITS_VECTOR2D_VECTOR(1, 1), 2);

  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(1, 1) *
                                UNITS_VECTOR2D_VECTOR(1,-1), 0);

  // Test cross product.
  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(1, 1) %
                                UNITS_VECTOR2D_VECTOR(1,-1), -2);

  // Test arithmetic.
  UNITS_VECTOR2D_VECTOR_TEST(2.0 * UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(2, 4));

  UNITS_VECTOR2D_VECTOR_TEST(UNITS_VECTOR2D_VECTOR(1, 2) * 2.0,
                             UNITS_VECTOR2D_VECTOR(2, 4));

  UNITS_VECTOR2D_VECTOR_TEST(UNITS_VECTOR2D_VECTOR(2, 4) / 2.0,
                             UNITS_VECTOR2D_VECTOR(1, 2));


  vector = UNITS_VECTOR2D_VECTOR(1, 2);
  UNITS_VECTOR2D_VECTOR_TEST(vector *= 2.0, UNITS_VECTOR2D_VECTOR(2, 4));
  UNITS_VECTOR2D_VECTOR_TEST(vector /= 2.0, UNITS_VECTOR2D_VECTOR(1, 2));

  UNITS_VECTOR2D_VECTOR_TEST(-UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(-1, -2));

  UNITS_VECTOR2D_VECTOR_TEST(UNITS_VECTOR2D_VECTOR(1, 2) +
                             UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(2, 4));

  UNITS_VECTOR2D_VECTOR_TEST(UNITS_VECTOR2D_VECTOR(2, 4) -
                             UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(1, 2));


  vector = UNITS_VECTOR2D_VECTOR(1, 2);
  UNITS_VECTOR2D_VECTOR_TEST(vector += UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(2, 4));

  UNITS_VECTOR2D_VECTOR_TEST(vector -= UNITS_VECTOR2D_VECTOR(1, 2),
                             UNITS_VECTOR2D_VECTOR(1, 2));


  UNITS_VECTOR2D_MAGNITUDE_TEST(Units::magnitude(UNITS_VECTOR2D_VECTOR(3, 4)),
                                5);
  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(3, 4).magnitude(),  5);


  UNITS_VECTOR2D_ANGLE_TEST(angle(UNITS_VECTOR2D_VECTOR(1, 2),
                                  UNITS_VECTOR2D_VECTOR(1, 2)),
                            DegreesAngle(0));

  UNITS_VECTOR2D_ANGLE_TEST(angle(UNITS_VECTOR2D_VECTOR(1, 2),
                                  -UNITS_VECTOR2D_VECTOR(1, 2)),
                            DegreesAngle(180));

  UNITS_VECTOR2D_ANGLE_TEST(angle(UNITS_VECTOR2D_VECTOR(1, 0),
                                  UNITS_VECTOR2D_VECTOR(0, 1)),
                            DegreesAngle(90));


  UNITS_VECTOR2D_MAGNITUDE_TEST(distance(UNITS_VECTOR2D_VECTOR(1, 2),
                                         UNITS_VECTOR2D_VECTOR(1, 2)), 0);

  UNITS_VECTOR2D_VECTOR_TEST(midpoint(UNITS_VECTOR2D_VECTOR(1, 2),
                                      -UNITS_VECTOR2D_VECTOR(1, 2)),
                             UNITS_VECTOR2D_VECTOR(0, 0));


  UNITS_VECTOR2D_VECTOR_TEST(interpolate(UNITS_VECTOR2D_VECTOR(1, 2),
                                         -UNITS_VECTOR2D_VECTOR(1, 2),
                                         ValueType(0.0)),
                             UNITS_VECTOR2D_VECTOR(1, 2));

  UNITS_VECTOR2D_VECTOR_TEST(interpolate(UNITS_VECTOR2D_VECTOR(1, 2),
                                         -UNITS_VECTOR2D_VECTOR(1, 2),
                                         ValueType(0.5)),
                             UNITS_VECTOR2D_VECTOR(0, 0));

  UNITS_VECTOR2D_VECTOR_TEST(interpolate(UNITS_VECTOR2D_VECTOR(1, 2),
                                         -UNITS_VECTOR2D_VECTOR(1, 2),
                                         ValueType(1.0)),
                             -UNITS_VECTOR2D_VECTOR(1, 2));


  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(6, 8).distanceToLine(UNITS_VECTOR2D_VECTOR(0, 0),
                                                                           UNITS_VECTOR2D_VECTOR(3, 4)), 0);

  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(2, 3).distanceToLine(UNITS_VECTOR2D_VECTOR(0, 0),
                                                                           UNITS_VECTOR2D_VECTOR(1, 0)), 3);


  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(6, 8).distanceToSegment(UNITS_VECTOR2D_VECTOR(0, 0),
                                                                              UNITS_VECTOR2D_VECTOR(3, 4)), 5);
  UNITS_VECTOR2D_MAGNITUDE_TEST(UNITS_VECTOR2D_VECTOR(0.5, 3).distanceToSegment(UNITS_VECTOR2D_VECTOR(0, 0),
                                                                                UNITS_VECTOR2D_VECTOR(1, 0)), 3);

  }
  catch (std::exception const & ex)
  {
    std::cerr << "Vector2D::test(): Exception: " << ex.what() << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units


#endif // Units_Vector2D_test_cpp
