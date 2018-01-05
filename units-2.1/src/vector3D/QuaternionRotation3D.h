//
// $Id: QuaternionRotation3D.h,v 1.4.4.3 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Unit quaternion representation of a 3D rotation.
//
// Two methods are available: unit quaternion and cosine matrix.
// Both have their strong-points.  Both are non-degenerate at the
// poles; both have pretty much constant accuracy over the range
// of possible rotations.  Unit quaternions are easier to normalize.
// Unit quaternions have fewer computations for combining rotations
// than transforming vectors, but cosine matricies are better for
// applications which transform vectors more often.
//

#ifndef Units_QuaternionRotation3D_h
#define Units_QuaternionRotation3D_h

#include <iostream>
#include <stdexcept>
#include "scalar/Angle.h"
#include "scalar/SignedAngle.h"


namespace Units
{


template<typename ValueType>
class _QuaternionRotation3D
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
  _QuaternionRotation3D();

  _QuaternionRotation3D(_QuaternionRotation3D const & rotation);

  _QuaternionRotation3D(_Direction3D<ValueType> const & axis_,
                        _Angle                  const & angle_);

  //
  // Construct a unit quaternion from raw vector values.
  // The values will automatically be normalized to unit length.
  // [0] is the scalar component; [1], [2], [3] is the vector.
  //
  _QuaternionRotation3D(ValueType const array[4]);
  _QuaternionRotation3D(ValueType const & qs,
                        ValueType const & qvx,
                        ValueType const & qvy,
                        ValueType const & qvz);


  //
  // Get the euclidian length of the quaternion.  (This should always
  // be close to 1.0.)
  //
  ValueType magnitude() const;

  //
  // Make sure quaternion is unit-length.  Useful to compensate for
  // numerical errors.
  //
  void normalize();


  //
  // Be careful with these -- they only check for binary equivalence!
  //
  bool        operator== (_QuaternionRotation3D const & rotation) const;
  bool        operator!= (_QuaternionRotation3D const & rotation) const;


  // Data access

  //
  // NOTE: There are two sets of axis/angles that can represent a rotation:
  //       the angles and axes are opposites of each other.  You might not
  //       get back the identical axis/angle set that you used to construct.
  //

  _Direction3D<ValueType> axis() const;
  _Angle angle() const;

  ValueType           const & qs() const;
  Vector3D<ValueType> const & qv() const;


  // Arithmetic operators

  //
  // Combine this with another rotation.
  //
  _QuaternionRotation3D   operator* (_QuaternionRotation3D const & rot)  const;
  _QuaternionRotation3D & operator*=(_QuaternionRotation3D const & rot);

  _QuaternionRotation3D   inverse() const;
  _QuaternionRotation3D<ValueType> & invert();
  _QuaternionRotation3D<ValueType> & rotate(_Direction3D<ValueType> const & axis,
                                            _Angle                  const & angle);

  static
  _QuaternionRotation3D const & identity();

  static
  _Angle defaultTolerance();


  ///
  /// Test the proper operation of the public API.  WARNING: This is
  /// for library testing only and not exported.
  ///
  static
  bool test();


private:
  ValueType           _qs;
  Vector3D<ValueType> _qv;

  static
  _QuaternionRotation3D const * _identity;

  _QuaternionRotation3D(ValueType           const & qs,
                        Vector3D<ValueType> const & qv);
};


///
/// Transform unitless vector with this rotation.
///
template<typename ValueType,
         typename ValueType2>
Vector3D<ValueType2>
operator* (_QuaternionRotation3D<ValueType> const & rotation,
           Vector3D<ValueType2>             const & vector);

///
/// Transform direction with this rotation.
///
template<typename ValueType>
_Direction3D<ValueType>
operator* (_QuaternionRotation3D<ValueType> const & rotation,
           _Direction3D<ValueType>          const & direction);


///
/// Compute the shortest rotation between two quaternions.
///
template<typename ValueType>
_QuaternionRotation3D<ValueType>
delta(_QuaternionRotation3D<ValueType> const & from,
      _QuaternionRotation3D<ValueType> const & to);

///
/// Compute the angle of the shortest rotation between two quaternions.
///
template<typename ValueType>
typename _QuaternionRotation3D<ValueType>::_Angle
error(_QuaternionRotation3D<ValueType> const & from,
      _QuaternionRotation3D<ValueType> const & to);

///
/// Check if the angle of shortest rotation between the quaternions is
/// within a tolerance.
///
template<typename ValueType>
bool similar(_QuaternionRotation3D<ValueType> const & a,
             _QuaternionRotation3D<ValueType> const & b,
             typename _QuaternionRotation3D<ValueType>::_Angle const & tol =
             _QuaternionRotation3D<ValueType>::defaultTolerance());

template<typename ValueType>
_QuaternionRotation3D<ValueType>
interpolate(_QuaternionRotation3D<ValueType> const & a,
            _QuaternionRotation3D<ValueType> const & b,
            ValueType                        const   lambda)
  throw (std::range_error);


template<typename ValueType>
std::ostream & operator<< (std::ostream                           & stream,
                           _QuaternionRotation3D<ValueType> const & rotation);


typedef _QuaternionRotation3D<double> dQuaternionRotation3D;
typedef _QuaternionRotation3D<float> fQuaternionRotation3D;
typedef _QuaternionRotation3D<UNITS_DEFAULT_VALUE_TYPE> QuaternionRotation3D;


} // namespace Units


#include "QuaternionRotation3D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "QuaternionRotation3D.cpp"
#endif

#endif  // Units_QuaternionRotation3D_h
