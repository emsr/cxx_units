//
// $Id: Rotation2D.h,v 1.3.4.4 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2D rotation from one coordinate system to another.
//

#ifndef Units_Rotation2D_h
#define Units_Rotation2D_h

#include <iostream>
#include "system/units_config.h"
#include "scalar/Angle.h"
#include "scalar/SignedAngle.h"
#include "Direction2D.h"


namespace Units
{


template<typename ValueType>
class _Rotation2D
{
public:
  //
  // These help making generic functions that use _Direction2D<>.
  //
  typedef typename AngleTraits<ValueType>::BaseUnitType _Angle;
  typedef SignedAngleType<ValueType> _SignedAngle;
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits<DegreesAngleTraits,
                                          ValueType> > _DegreesAngle;

  //
  // Construct the identity rotation.
  //
  _Rotation2D();

  //
  // Copy constructor.
  //
  _Rotation2D(_Rotation2D const & rotation);

  //
  // Create a CCW rotation.
  //
  explicit
  _Rotation2D(_Angle      const & angle);


  // Data access

  _Angle angle () const;

  _Direction2D<ValueType> xAxis() const;
  _Direction2D<ValueType> yAxis() const;


  // Comparison functions

  // Be careful with these -- they only check for binary equivalence.
  bool         operator== (_Rotation2D const & rotation) const;
  bool         operator!= (_Rotation2D const & rotation) const;

  // Arithmetic operators

  //
  // Combine this with another rotation.
  //
  _Rotation2D   operator* (_Rotation2D const & rotation)  const;
  _Rotation2D & operator*=(_Rotation2D const & rotation);

  //
  // Return the inverse of this.
  //
  _Rotation2D   inverse   ()                                  const;

  //
  // Invert this rotation.
  //
  _Rotation2D & invert    ();

  //
  // Rotate this by a given angle.
  //
  _Rotation2D & rotate    (Angle const & angle);


  static
  _Rotation2D const & identity();


  ///
  /// Test the proper operation of the public API.  WARNING: This is
  /// for library testing only and not exported.
  ///
  static
  bool test();


protected:
  // A unit vector in the direction of the rotated X axis.
  _Direction2D<ValueType> _xAxis;

  explicit
  _Rotation2D(_Direction2D<ValueType> const & xAxis);

private:
  static
  _Rotation2D const _identity;
};


template <typename ValueType>
bool similar(_Rotation2D<ValueType> const & a,
             _Rotation2D<ValueType> const & b,
             typename _Rotation2D<ValueType>::_Angle const & tol =
             _Rotation2D<ValueType>::_Angle::defaultTolerance());

///
/// Transform unitless vector with this rotation.
///
template <typename ValueType1,
          typename ValueType2>
// 4 mults,  2 adds
Vector2D<ValueType2> operator* (_Rotation2D<ValueType1> const & rotation,
                                Vector2D<ValueType2>    const & vector)
{
  return (rotation.xAxis()*vector.x +
	  rotation.yAxis()*vector.y);
}

///
/// Transform direction with this rotation.
///
template <typename ValueType>
_Direction2D<ValueType> operator* (_Rotation2D<ValueType>  const & rotation,
                                   _Direction2D<ValueType> const & direction);

template <typename ValueType>
std::ostream & operator<< (std::ostream                 & stream,
                           _Rotation2D<ValueType> const & rotation);


typedef _Rotation2D<double> dRotation2D;
typedef _Rotation2D<float> fRotation2D;
typedef _Rotation2D<UNITS_DEFAULT_VALUE_TYPE> Rotation2D;


} // namespace Units


#include "Rotation2D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Rotation2D.cpp"
#endif

#endif  // Units_Rotation2D_h
