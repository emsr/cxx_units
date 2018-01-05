//
// $Id: Direction3D.h,v 1.3.4.3 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional direction (unit vector).
// The magnitude is always 1, or else an exception is thrown.
//

#ifndef Units_Direction3D_h
#define Units_Direction3D_h

#include <iostream>
#include <stdexcept>
#include "system/units_config.h"
#include "scalar/Angle.h"
#include "Vector3D.h"



namespace Units
{


///
/// ValueType is intended to be a unitless type (double or float).
///
template <typename ValueType>
class _Direction3D
{
public:
  //
  // These help making generic functions that use _Direction3D<>.
  //
  typedef typename AngleTraits<ValueType>::BaseUnitType _Angle;
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits<DegreesAngleTraits,
                                          ValueType> > _DegreesAngle;


  // NOTE: No default constructor is provided because we can't allow
  //       an undefined Direction3D to be constructed.

  _Direction3D(_Direction3D const & v);

  // Normalize the given vector.
  explicit
  _Direction3D(Vector3D<ValueType> const & vec)
    throw (std::range_error);

  // Normalize the given vector.
  _Direction3D(ValueType const xx,
               ValueType const yy,
               ValueType const zz)
    throw (std::range_error);


  // Data access

  ValueType const & x() const;
  ValueType const & y() const;
  ValueType const & z() const;

  Vector3D<ValueType> const & vector() const;


  // Comparison functions

  bool          operator== (_Direction3D const & v) const;
  bool          operator!= (_Direction3D const & v) const;


  // Reverse direction
  _Direction3D  operator-  ()                     const;

  // Cross product
  _Direction3D operator% (_Direction3D const & vec) const
    throw (std::range_error);


#if 0
  // Return a vector with a given magnitude and direction.
  template <typename ValueType2>
  Vector3D<ValueType2> operator* (ValueType2 const & magnitude);
#endif

  Vector3D<ValueType> operator* (ValueType const   magnitude)
  {
    return (_vector * magnitude);
  }

  ValueType operator* (_Direction3D const & direction);


  // Compensate for precision drift
  _Direction3D & normalize();


  // Return the angle between this and another vector.
  _Angle         angleTo    (_Direction3D const & v) const;

  _Direction3D   interpolateTo(_Direction3D const & b,
                               ValueType    const   lambda) const
    throw (std::range_error);


  static
  _Angle defaultTolerance();

  ///
  /// Test the proper operation of the public API.  WARNING: This is
  /// for library testing only and not exported.
  ///
  static
  bool test();


private:
  Vector3D<ValueType> _vector;

  _Direction3D();


  void _construct(Vector3D<ValueType> const & vec)
    throw (std::range_error);
};


template <typename ValueType>
bool similar(_Direction3D<ValueType> const & a,
             _Direction3D<ValueType> const & b,
             typename _Direction3D<ValueType>::_Angle const & tol =
             _Direction3D<ValueType>::defaultTolerance());


template <typename ValueType1,
          typename ValueType2>
Vector3D<ValueType2> operator* (_Direction3D<ValueType1> const & direction,
                                ValueType2               const & magnitude);

template <typename ValueType1,
          typename ValueType2>
Vector3D<ValueType2> operator* (ValueType2               const & magnitude,
                                _Direction3D<ValueType1> const & direction);


// Return the angle between two vectors.
template <typename ValueType>
typename _Direction3D<ValueType>::_Angle
angle(_Direction3D<ValueType> const & a,
      _Direction3D<ValueType> const & b);

template <typename ValueType>
_Direction3D<typename UnitlessType<ValueType>::Result>
direction(Vector3D<ValueType> const & vec);

// Return a unit vector half-way between two vectors.
template <typename ValueType>
_Direction3D<ValueType>   midpoint   (_Direction3D<ValueType> const & a,
                                      _Direction3D<ValueType> const & b);

  // Return a direction from a to b as lambda goes from 0 to 1.
template <typename ValueType>
_Direction3D<ValueType>   interpolate(_Direction3D<ValueType> const & a,
                                      _Direction3D<ValueType> const & b,
                                      ValueType               const   lambda)
  throw (std::range_error);


template <typename ValueType>
std::ostream & operator<< (std::ostream                  & stream,
                           _Direction3D<ValueType> const & v);


typedef _Direction3D<double> dDirection3D;
typedef _Direction3D<float> fDirection3D;
typedef _Direction3D<UNITS_DEFAULT_VALUE_TYPE> Direction3D;


} // namespace Units


#include "Direction3D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Direction3D.cpp"
#endif

#endif  // Units_Direction3D_h
