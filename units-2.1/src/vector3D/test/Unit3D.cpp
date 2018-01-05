//
// $Id: Unit3D.cpp,v 1.7.2.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//

#ifndef Units_Unit3D_cpp
#define Units_Unit3D_cpp

#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Unit3D.h"
#include "Direction3D.h"
#include "QuaternionRotation3D.h"
#include "MatrixRotation3D.h"


namespace Units
{


//
// Test the API to the Unit3D class.
//
template<typename SpecificUnitType>
bool generic3DTest(std::string const & unitName)
{
  typedef typename SpecificUnitType::BaseUnitType UnitType;

  bool status = true;

  Unit3D<UnitType> testVector;

  try
  {

  testVector = zero();
  if ((testVector.x != zero()) ||
      (testVector.y != zero()) ||
      (testVector.z != zero()))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): "
              << "Assign to zero() failed." << std::endl;
    status = false;
  }

#define UNITS_UNIT3D_VECTOR(x, y, z)  Unit3D<UnitType>(SpecificUnitType(x), SpecificUnitType(y), SpecificUnitType(z))


  if (!similar(UNITS_UNIT3D_VECTOR(1, 2, 3),
               UNITS_UNIT3D_VECTOR(1, 2, 3)))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): "
              << "similar() between identical Unit3Ds failed." << std::endl;
    status = false;
  }
  if (!similar(UNITS_UNIT3D_VECTOR(1, 2, 3),
               UNITS_UNIT3D_VECTOR(1.0000005, 2, 3),
               SpecificUnitType(1e-6)))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): "
              << "similar() between similar Unit3Ds failed." << std::endl;
    status = false;
  }
  if (similar(UNITS_UNIT3D_VECTOR(1, 2, 3),
              UNITS_UNIT3D_VECTOR(3, 2, 1)))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): "
              << "similar() between unsimilar Unit3Ds failed." << std::endl;
    status = false;
  }

  if (UNITS_UNIT3D_VECTOR(1, 2, 3) == UNITS_UNIT3D_VECTOR(3, 2, 1))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): operator==() failed."
              << std::endl;
    status = false;
  }
  if (UNITS_UNIT3D_VECTOR(1, 2, 3) != UNITS_UNIT3D_VECTOR(1, 2, 3))
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): operator!=() failed."
              << std::endl;
    status = false;
  }


#define UNITS_UNIT3D_VECTOR_TEST(expr, output) \
  if (!(expr).similarTo(output)) \
  { \
    std::cerr << "Unit3D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                    Expected " \
	      << Unit3D<SpecificUnitType>(output) << ", but got " \
	      << Unit3D<SpecificUnitType>(expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_UNIT3D_MAGNITUDE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Unit3D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                    Expected " \
	      << SpecificUnitType(output) << ", but got " \
	      << SpecificUnitType(expr) << '.' << std::endl; \
    status = false; \
  }

#define UNITS_UNIT3D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Unit3D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                    Expected " \
	      << DegreesAngle(output) << ", but got " \
	      << DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6),
                           2.0 * UNITS_UNIT3D_VECTOR(1, 2, 3));

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 3),
                           UNITS_UNIT3D_VECTOR(2, 4, 6) / 2.0);

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6),
                           UNITS_UNIT3D_VECTOR(1, 2, 3) * 2.0);


  testVector = UNITS_UNIT3D_VECTOR(1, 2, 3);
  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6), testVector *= 2.0);
  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 3), testVector /= 2.0);


  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(-1, -2, -3),
                           -UNITS_UNIT3D_VECTOR(1, 2, 3));

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6),
                           UNITS_UNIT3D_VECTOR(1, 2, 3) +
                           UNITS_UNIT3D_VECTOR(1, 2, 3));

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 3),
                           UNITS_UNIT3D_VECTOR(2, 4, 6) -
                           UNITS_UNIT3D_VECTOR(1, 2, 3));


  testVector = UNITS_UNIT3D_VECTOR(1, 2, 3);
  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6),
                           testVector += UNITS_UNIT3D_VECTOR(1, 2, 3));

  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 3),
                           testVector -= UNITS_UNIT3D_VECTOR(1, 2, 3));


  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 2),
                           operator*(Units::direction(UNITS_UNIT3D_VECTOR(1, 2, 2)),
                                     SpecificUnitType(3)));


  UNITS_UNIT3D_VECTOR_TEST(UNITS_UNIT3D_VECTOR(1, 2, 2),
                           operator*(UNITS_UNIT3D_VECTOR(1, 2, 2).direction(),
                                     SpecificUnitType(3)));


  UNITS_UNIT3D_MAGNITUDE_TEST(magnitude(UNITS_UNIT3D_VECTOR(1, 2, 2)),
                              SpecificUnitType(3));

  UNITS_UNIT3D_MAGNITUDE_TEST(UNITS_UNIT3D_VECTOR(1, 2, 2).magnitude(),
                              SpecificUnitType(3));


  UNITS_UNIT3D_ANGLE_TEST(angle( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                 UNITS_UNIT3D_VECTOR(1, 2, 3)),
                          DegreesAngle(0));

  UNITS_UNIT3D_ANGLE_TEST(angle( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                -UNITS_UNIT3D_VECTOR(1, 2, 3)),
                          DegreesAngle(180));

  UNITS_UNIT3D_ANGLE_TEST(angle( UNITS_UNIT3D_VECTOR(1, 0, 0),
                                 UNITS_UNIT3D_VECTOR(0, 1, 0)),
                          DegreesAngle(90));


  UNITS_UNIT3D_MAGNITUDE_TEST(distance(UNITS_UNIT3D_VECTOR(1, 2, 3),
                                       UNITS_UNIT3D_VECTOR(1, 2, 3)),
                              SpecificUnitType(0));


  UNITS_UNIT3D_VECTOR_TEST(midpoint( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                    -UNITS_UNIT3D_VECTOR(1, 2, 3)),
                           UNITS_UNIT3D_VECTOR(0, 0, 0));


  UNITS_UNIT3D_VECTOR_TEST(interpolate( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                       -UNITS_UNIT3D_VECTOR(1, 2, 3), 0.0),
                           UNITS_UNIT3D_VECTOR(1, 2, 3));

  UNITS_UNIT3D_VECTOR_TEST(interpolate( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                       -UNITS_UNIT3D_VECTOR(1, 2, 3), 0.5),
                           UNITS_UNIT3D_VECTOR(0, 0, 0));

  UNITS_UNIT3D_VECTOR_TEST(interpolate( UNITS_UNIT3D_VECTOR(1, 2, 3),
                                       -UNITS_UNIT3D_VECTOR(1, 2, 3), 1.0),
                           -UNITS_UNIT3D_VECTOR(1, 2, 3));


  UNITS_UNIT3D_MAGNITUDE_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6).distanceToLine(UNITS_UNIT3D_VECTOR(0, 0, 0),
                                                                          UNITS_UNIT3D_VECTOR(1, 2, 3)),
                              SpecificUnitType(0));

  UNITS_UNIT3D_MAGNITUDE_TEST(UNITS_UNIT3D_VECTOR(2, 3, 4).distanceToLine(UNITS_UNIT3D_VECTOR(0, 0, 0),
                                                                          UNITS_UNIT3D_VECTOR(1, 0, 0)),
                              SpecificUnitType(5));


  UNITS_UNIT3D_MAGNITUDE_TEST(UNITS_UNIT3D_VECTOR(2, 4, 6).distanceToSegment(UNITS_UNIT3D_VECTOR(0, 0, 0),
                                                                             UNITS_UNIT3D_VECTOR(1, 2, 3)),
                              magnitude(UNITS_UNIT3D_VECTOR(1, 2, 3)));

  UNITS_UNIT3D_MAGNITUDE_TEST(UNITS_UNIT3D_VECTOR(0.5, 3, 4).distanceToSegment(UNITS_UNIT3D_VECTOR(0, 0, 0),
                                                                               UNITS_UNIT3D_VECTOR(1, 0, 0)),
                              SpecificUnitType(5));


  //
  // Test with QuaternionRotation3D.
  //
  QuaternionRotation3D quat;
  quat = QuaternionRotation3D(Direction3D(0, 0, 1), DegreesAngle( 90));
  UNITS_UNIT3D_VECTOR_TEST(quat*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR(-1, 1, 0));

  quat = QuaternionRotation3D(Direction3D(0, 0, 1), DegreesAngle(180));
  UNITS_UNIT3D_VECTOR_TEST(quat*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR(-1,-1, 0));

  quat = QuaternionRotation3D(Direction3D(0, 0, 1), DegreesAngle(-90));
  UNITS_UNIT3D_VECTOR_TEST(quat*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR( 1,-1, 0));


  //
  // Test with MatrixRotation3D.
  //
  MatrixRotation3D matrix;
  matrix = MatrixRotation3D(Direction3D(0, 0, 1), DegreesAngle( 90));
  UNITS_UNIT3D_VECTOR_TEST(matrix*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR(-1, 1, 0));

  matrix = MatrixRotation3D(Direction3D(0, 0, 1), DegreesAngle(180));
  UNITS_UNIT3D_VECTOR_TEST(matrix*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR(-1,-1, 0));

  matrix = MatrixRotation3D(Direction3D(0, 0, 1), DegreesAngle(-90));
  UNITS_UNIT3D_VECTOR_TEST(matrix*UNITS_UNIT3D_VECTOR( 1, 1, 0),
                           UNITS_UNIT3D_VECTOR( 1,-1, 0));
  }
  catch (std::exception const & ex)
  {
    std::cerr << "Unit3D<" << unitName << ">::test(): "
              << "Exception: " << ex.what() << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units


#endif // Units_Unit3D_cpp
