//
// $Id: Unit2D.cpp,v 1.8.2.5 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Unit2D class.
//

#ifndef Units_Unit2D_cpp
#define Units_Unit2D_cpp

#include <iostream>
#include <stdexcept>
#include <math.h>
#include "Unit2D.h"
#include "Rotation2D.h"



namespace Units
{


///
/// Test the proper operation of the generic methods.  These are the
/// same for any specific unit type.
///
template<typename SpecificUnitType>
bool generic2DTest(std::string const & unitName)
{
  typedef typename SpecificUnitType::BaseUnitType UnitType;

  bool status = true;

  Unit2D<UnitType> testVector;

  try
  {

  testVector = zero();
  if ((testVector.x != zero()) ||
      (testVector.y != zero()))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): "
              << "Assign to zero() failed." << std::endl;
    status = false;
  }

#define UNITS_UNIT2D_VECTOR(x, y) \
  Unit2D<UnitType>(SpecificUnitType(x), SpecificUnitType(y))


  if (!similar(UNITS_UNIT2D_VECTOR(1, 2),
               UNITS_UNIT2D_VECTOR(1, 2)))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): "
              << "similar() between identical Unit2Ds failed." << std::endl;
    status = false;
  }
  if (!similar(UNITS_UNIT2D_VECTOR(1, 2),
               UNITS_UNIT2D_VECTOR(1.0000005,
                                   2),
               SpecificUnitType(1e-6)))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): "
              << "similar() between similar Unit2Ds failed." << std::endl;
    status = false;
  }
  if (similar(UNITS_UNIT2D_VECTOR(1, 2),
              UNITS_UNIT2D_VECTOR(3, 2)))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): "
              << "similar() between unsimilar Unit2Ds failed." << std::endl;
    status = false;
  }

  if (UNITS_UNIT2D_VECTOR(1, 2) == UNITS_UNIT2D_VECTOR(3, 2))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): operator==() failed."
              << std::endl;
    status = false;
  }
  if (UNITS_UNIT2D_VECTOR(1, 2) != UNITS_UNIT2D_VECTOR(1, 2))
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): operator!=() failed."
              << std::endl;
    status = false;
  }


#define UNITS_UNIT2D_VECTOR_TEST(expr, output) \
  if (!(expr).similarTo(output)) \
  { \
    std::cerr << "Unit2D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                Expected " \
	      << Unit2D<SpecificUnitType>(output) << ", but got " \
	      << Unit2D<SpecificUnitType>(expr) << "." << std::endl; \
    status = false; \
  }

#define UNITS_UNIT2D_MAGNITUDE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Unit2D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                Expected " \
	      << SpecificUnitType(output) << ", but got " \
	      << SpecificUnitType(expr) << '.' << std::endl; \
    status = false; \
  }

#define UNITS_UNIT2D_ANGLE_TEST(expr, output) \
  if (!similar(expr, output)) \
  { \
    std::cerr << "Unit2D<" << unitName << ">::test(): " \
              << #expr " failed." << std::endl; \
    std::cerr << "                Expected " \
	      << DegreesAngle(output) << ", but got " \
	      << DegreesAngle(expr) << '.' << std::endl; \
    status = false; \
  }

  UNITS_UNIT2D_VECTOR_TEST(2.0 * UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(2, 4));

  UNITS_UNIT2D_VECTOR_TEST(UNITS_UNIT2D_VECTOR(1, 2) * 2.0,
                           UNITS_UNIT2D_VECTOR(2, 4));

  UNITS_UNIT2D_VECTOR_TEST(UNITS_UNIT2D_VECTOR(2, 4) / 2.0,
                           UNITS_UNIT2D_VECTOR(1, 2));


  testVector = UNITS_UNIT2D_VECTOR(1, 2);
  UNITS_UNIT2D_VECTOR_TEST(testVector *= 2.0, UNITS_UNIT2D_VECTOR(2, 4));
  UNITS_UNIT2D_VECTOR_TEST(testVector /= 2.0, UNITS_UNIT2D_VECTOR(1, 2));

  UNITS_UNIT2D_VECTOR_TEST(-UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(-1, -2));

  UNITS_UNIT2D_VECTOR_TEST(UNITS_UNIT2D_VECTOR(1, 2) +
                           UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(2, 4));

  UNITS_UNIT2D_VECTOR_TEST(UNITS_UNIT2D_VECTOR(2, 4) -
                           UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(1, 2));

  testVector = UNITS_UNIT2D_VECTOR(1, 2);
  UNITS_UNIT2D_VECTOR_TEST(testVector += UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(2, 4));

  UNITS_UNIT2D_VECTOR_TEST(testVector -= UNITS_UNIT2D_VECTOR(1, 2),
                           UNITS_UNIT2D_VECTOR(1, 2));


  UNITS_UNIT2D_VECTOR_TEST(Units::operator*(Units::direction(UNITS_UNIT2D_VECTOR(3, 4)),
                                            SpecificUnitType(5)),
                           UNITS_UNIT2D_VECTOR(3, 4));

  UNITS_UNIT2D_VECTOR_TEST(Units::operator*(UNITS_UNIT2D_VECTOR(3, 4).direction(),
                                            SpecificUnitType(5)),
                           UNITS_UNIT2D_VECTOR(3, 4));

  UNITS_UNIT2D_MAGNITUDE_TEST(Units::magnitude(UNITS_UNIT2D_VECTOR(3, 4)),
                              SpecificUnitType(5));

  UNITS_UNIT2D_MAGNITUDE_TEST(UNITS_UNIT2D_VECTOR(3, 4).magnitude(),
                              SpecificUnitType(5));


  UNITS_UNIT2D_ANGLE_TEST(angle(UNITS_UNIT2D_VECTOR(1, 2),
                                UNITS_UNIT2D_VECTOR(1, 2)), DegreesAngle(0));

  UNITS_UNIT2D_ANGLE_TEST(angle(UNITS_UNIT2D_VECTOR(1, 2),
                                -UNITS_UNIT2D_VECTOR(1, 2)), DegreesAngle(180));

  UNITS_UNIT2D_ANGLE_TEST(angle(UNITS_UNIT2D_VECTOR(1, 0),
                                UNITS_UNIT2D_VECTOR(0, 1)), DegreesAngle(90));


  UNITS_UNIT2D_MAGNITUDE_TEST(distance(UNITS_UNIT2D_VECTOR(1, 2),
                                       UNITS_UNIT2D_VECTOR(1, 2)),
                              SpecificUnitType(0));

  UNITS_UNIT2D_VECTOR_TEST(midpoint(UNITS_UNIT2D_VECTOR(1, 2),
                                    -UNITS_UNIT2D_VECTOR(1, 2)),
                           UNITS_UNIT2D_VECTOR(0, 0));


  UNITS_UNIT2D_VECTOR_TEST(interpolate(UNITS_UNIT2D_VECTOR(1, 2),
                                       -UNITS_UNIT2D_VECTOR(1, 2), 0.0),
                           UNITS_UNIT2D_VECTOR(1, 2));

  UNITS_UNIT2D_VECTOR_TEST(interpolate(UNITS_UNIT2D_VECTOR(1, 2),
                                       -UNITS_UNIT2D_VECTOR(1, 2), 0.5),
                           UNITS_UNIT2D_VECTOR(0, 0));

  UNITS_UNIT2D_VECTOR_TEST(interpolate(UNITS_UNIT2D_VECTOR(1, 2),
                                       -UNITS_UNIT2D_VECTOR(1, 2), 1.0),
                           -UNITS_UNIT2D_VECTOR(1, 2));


  UNITS_UNIT2D_MAGNITUDE_TEST(UNITS_UNIT2D_VECTOR(6, 8).distanceToLine(UNITS_UNIT2D_VECTOR(0, 0),
                                                                       UNITS_UNIT2D_VECTOR(3, 4)),
                              SpecificUnitType(0));

  UNITS_UNIT2D_MAGNITUDE_TEST(UNITS_UNIT2D_VECTOR(2, 3).distanceToLine(UNITS_UNIT2D_VECTOR(0, 0),
                                                                       UNITS_UNIT2D_VECTOR(1, 0)),
                              SpecificUnitType(3));

  UNITS_UNIT2D_MAGNITUDE_TEST(UNITS_UNIT2D_VECTOR(6, 8).distanceToSegment(UNITS_UNIT2D_VECTOR(0, 0),
                                                                          UNITS_UNIT2D_VECTOR(3, 4)),
                              SpecificUnitType(5));

  UNITS_UNIT2D_MAGNITUDE_TEST(UNITS_UNIT2D_VECTOR(0.5, 3).distanceToSegment(UNITS_UNIT2D_VECTOR(0, 0),
                                                                            UNITS_UNIT2D_VECTOR(1, 0)),
                              SpecificUnitType(3));

  //
  // Test rotation.
  //
  UNITS_UNIT2D_VECTOR_TEST(Rotation2D(DegreesAngle(90))*UNITS_UNIT2D_VECTOR(1, 1),
                           UNITS_UNIT2D_VECTOR(-1, 1));
  UNITS_UNIT2D_VECTOR_TEST(Rotation2D(DegreesAngle(-90))*UNITS_UNIT2D_VECTOR(1, 1),
                           UNITS_UNIT2D_VECTOR(1, -1));

  }
  catch (std::exception const & ex)
  {
    std::cerr << "Unit2D<" << unitName << ">::test(): "
              << "Exception: " << ex.what() << std::endl;
    status = false;
  }

  return status;
}


} // namespace Units


#endif // Units_Unit2D_cpp
