//
// $Id: Direction2D.h,v 1.4.4.6 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional direction (unit vector).
// The magnitude is always 1, or else an exception is thrown.
//

#ifndef Units_Direction2D_h
#define Units_Direction2D_h

#include <iostream>
#include <stdexcept>
#include "system/units_config.h"
#include "scalar/Angle.h"
#include "Vector2D.h"


namespace Units
{


///
/// ValueType is intended to be a unitless type (double or float).
///
template <typename ValueType>
class _Direction2D
{
public:
  //
  // These help making generic functions that use _Direction2D<>.
  //
  typedef typename AngleTraits<ValueType>::BaseUnitType _Angle;
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits<DegreesAngleTraits,
                                          ValueType> > _DegreesAngle;


  // NOTE: No default constructor is provided because we can't allow
  //       an undefined Direction2D to be constructed.

  _Direction2D(_Direction2D const & v);

  // Normalize the given vector.
  explicit
  _Direction2D(Vector2D<ValueType> const & vec)
    throw (std::range_error);

  // Normalize the given vector.
  _Direction2D(ValueType const xx,
               ValueType const yy)
    throw (std::range_error);


  // Data access

  ValueType const & x() const;
  ValueType const & y() const;

  Vector2D<ValueType> const & vector() const;


  // Comparison functions

  bool          operator== (_Direction2D const & v) const;
  bool          operator!= (_Direction2D const & v) const;


  // Reverse direction
  _Direction2D  operator-  ()                     const;

  // Cross product
  ValueType     operator%  (_Direction2D const & v) const;


#if 0
  // Return a vector with a given magnitude and direction.
  template <typename ValueType2>
  Vector2D<ValueType2> operator* (ValueType2 const & magnitude);
#endif

  Vector2D<ValueType> operator* (ValueType const   magnitude)
  {
    return (_vector * magnitude);
  }

  ValueType operator* (_Direction2D const & direction);


  // Compensate for precision drift
  _Direction2D & normalize();


  // Return the angle between this and another vector.
  _Angle         angleTo    (_Direction2D const & v) const;

  _Direction2D   interpolateTo(_Direction2D const & b,
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
  Vector2D<ValueType> _vector;

  _Direction2D();


  void _construct(Vector2D<ValueType> const & vec)
    throw (std::range_error);
};


template <typename ValueType>
bool similar(_Direction2D<ValueType> const & a,
             _Direction2D<ValueType> const & b,
             typename _Direction2D<ValueType>::_Angle const & tol =
             _Direction2D<ValueType>::defaultTolerance());


template <typename ValueType1,
          typename ValueType2>
Vector2D<ValueType2> operator* (_Direction2D<ValueType1> const & direction,
                                ValueType2               const & magnitude);

template <typename ValueType1,
          typename ValueType2>
Vector2D<ValueType2> operator* (ValueType2               const & magnitude,
                                _Direction2D<ValueType1> const & direction);


// Return the angle between two vectors.
template <typename ValueType>
typename _Direction2D<ValueType>::_Angle
angle(_Direction2D<ValueType> const & a,
      _Direction2D<ValueType> const & b);

template <typename ValueType>
_Direction2D<typename UnitlessType<ValueType>::Result>
direction(Vector2D<ValueType> const & vec);

// Return a unit vector half-way between two vectors.
template <typename ValueType>
_Direction2D<ValueType>   midpoint   (_Direction2D<ValueType> const & a,
                                      _Direction2D<ValueType> const & b);

  // Return a direction from a to b as lambda goes from 0 to 1.
template <typename ValueType>
_Direction2D<ValueType>   interpolate(_Direction2D<ValueType> const & a,
                                      _Direction2D<ValueType> const & b,
                                      ValueType               const   lambda)
  throw (std::range_error);


template <typename ValueType>
std::ostream & operator<< (std::ostream                  & stream,
                           _Direction2D<ValueType> const & v);


typedef _Direction2D<double> dDirection2D;
typedef _Direction2D<float> fDirection2D;
typedef _Direction2D<UNITS_DEFAULT_VALUE_TYPE> Direction2D;


} // namespace Units


#include "Direction2D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Direction2D.cpp"
#endif

#endif  // Units_Direction2D_h
