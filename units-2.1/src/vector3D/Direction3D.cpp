//
// $Id: Direction3D.cpp,v 1.4.4.4 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Direction3D class.
//

#ifndef Units_Direction3D_cpp
#define Units_Direction3D_cpp

#include <math.h>
#include <iostream>
#include "Direction3D.h"


namespace Units
{


template <typename ValueType>
void _Direction3D<ValueType>::_construct(Vector3D<ValueType> const & vec)
  throw (std::range_error)
{
  _vector = vec;
  ValueType magSquared = _vector * _vector;
  if (fabs(magSquared) < 1e-6)
  {
    throw std::range_error("Direction3D: "
                           "Attempted to create a zero-magnitude direction.");
  }
  _vector /= ::sqrt(magSquared);
}


//
// Arithmetic operators
//
// NOTE: Operators returning a new Direction3D cannot use the double
//       constructor since internally we don't want to normalize.
//

template <typename ValueType>
_Direction3D<ValueType> _Direction3D<ValueType>::operator- () const
{
  _Direction3D result;
  result._vector = -_vector;
  return result;
}


template <typename ValueType>
_Direction3D<ValueType>
_Direction3D<ValueType>::operator% (_Direction3D const & vec) const
  throw (std::range_error)
{
  _Direction3D result;
  result._vector = _vector % vec._vector;

  ValueType magSquared = result._vector * result._vector;

  if (fabs(magSquared) < 1e-12)
  {
    throw std::range_error("Direction3D: "
                           "Attempted to cross colinear directions.");
  }
  result._vector /= ::sqrt(magSquared);
  return result;
}


template <typename ValueType>
_Direction3D<ValueType> & _Direction3D<ValueType>::normalize()
{
  //
  // Shouldn't need to check for divide by zero since a zero-length
  // Direction3D can't be created.
  //
  _vector /= _vector.magnitude();
  return *this;
}


template <typename ValueType>
typename _Direction3D<ValueType>::_Angle
_Direction3D<ValueType>::angleTo(_Direction3D const & vec)  const
{
  ValueType dot = _vector * vec._vector;

  //
  // Protect against numeric errors.
  //
  if (dot <= -1.0)
  {
    static const _DegreesAngle ang180(180);
    return ang180;
  }
  else if (dot >= 1.0)
  {
    return _Angle(zero());
  }
  return arccos(dot);
}


//
// Perform a Spherical Linear Interpolation (SLERP).
//
template <typename ValueType>
_Direction3D<ValueType>
_Direction3D<ValueType>::interpolateTo(_Direction3D const & b,
                                       ValueType    const   lambda) const
  throw (std::range_error)
{
  _Angle ab = angleTo(b);

  if (fabs(sin(ab)) < 1e-6)
  {
    throw std::range_error("Direction3D: "
                           "Attempted to interpolate colinear directions.");
  }

  // Projection of v on a in the direction of b.
  ValueType va = sin((1 - lambda)*ab)/sin(ab);

  // Projection of v on b in the direction of a.
  ValueType vb = sin(lambda*ab)/sin(ab);

  return _Direction3D(va*_vector + vb*b._vector);
}


} // namespace Units

#endif  // Units_Direction3D_cpp
