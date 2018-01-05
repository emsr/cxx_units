//
// $Id: QuaternionRotation3D.cpp,v 1.5.4.4 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the QuaternionRotation3D class.
//

#ifndef Units_QuaternionRotation3D_cpp
#define Units_QuaternionRotation3D_cpp

#include <math.h>
#include "QuaternionRotation3D.h"


namespace Units
{


template<typename ValueType>
_QuaternionRotation3D<ValueType> const *
_QuaternionRotation3D<ValueType>::_identity = 0;

template<typename ValueType>
_QuaternionRotation3D<ValueType> const &
_QuaternionRotation3D<ValueType>::identity()
{
  if (!_identity)
  {
    _identity = new _QuaternionRotation3D(1, Vector3D<ValueType>(0, 0, 0));
  }
  return *_identity;
}


template<typename ValueType>
ValueType _QuaternionRotation3D<ValueType>::magnitude() const
{
  return ::sqrt(_qs*_qs + _qv*_qv);
}

template<typename ValueType>
void _QuaternionRotation3D<ValueType>::normalize()
{
  ValueType mag = magnitude();
  _qs /= mag;
  _qv /= mag;
}


// 21 mults, 8 adds
template<typename ValueType,
         typename ValueType2>
Vector3D<ValueType2>
operator* (_QuaternionRotation3D<ValueType> const & rotation,
           Vector3D<ValueType2>             const & vector)
{
  Vector3D<ValueType2> v1 (vector*(2*rotation.qs()*rotation.qs() - 1));
  Vector3D<ValueType2> v2 (rotation.qv()*(rotation.qv()*vector));
  Vector3D<ValueType2> v3 ((rotation.qv() % vector)*rotation.qs());

  Vector3D<ValueType2> s  = v1 + (v2 + v3)*2.0;
  return s;
}

template<typename ValueType>
_Direction3D<ValueType>
operator* (_QuaternionRotation3D<ValueType> const & rotation,
           _Direction3D<ValueType>          const & direction)
{
  return _Direction3D<ValueType>(rotation * direction.vector());
}

//
// From http://www.pst.stsci.edu/moss/rotations_req.html
//
// 16 mults, 8 adds
template<typename ValueType>
_QuaternionRotation3D<ValueType>
_QuaternionRotation3D<ValueType>::
operator* (_QuaternionRotation3D const & r) const
{
  return _QuaternionRotation3D(_qs*r._qs - _qv*r._qv,
                               _qv*r._qs + _qs*r._qv + _qv%r._qv);
}


template<typename ValueType>
_QuaternionRotation3D<ValueType>
delta(_QuaternionRotation3D<ValueType> const & from,
      _QuaternionRotation3D<ValueType> const & to)
{
  _QuaternionRotation3D<ValueType> from_to = (from.inverse()*to);
  if (from_to.qs() < 0.0)
  {
    from_to = _QuaternionRotation3D<ValueType>(-from_to.qs(),
                                               -from_to.qv().x,
                                               -from_to.qv().y,
                                               -from_to.qv().z);
  }

  // Compensate for numerical errors
  from_to.normalize();
  return from_to;
}


//
// Perform a Spherical Linear Interpolation (SLERP) on the unit hypersphere.
// This gives us evenly-spaced unit quaternions along the shortest path
// between the two given rotations.
//
// 20 mults, 11 adds, 3 divs, 8 trigs
template<typename ValueType>
_QuaternionRotation3D<ValueType>
interpolate(_QuaternionRotation3D<ValueType> const & a,
            _QuaternionRotation3D<ValueType> const & b,
            ValueType                        const   lambda)
  throw (std::range_error)
{
  // Get the angle between the quaternion vectors, not just their vector parts.
  ValueType aMag  = a.magnitude();
  ValueType bMag  = b.magnitude();
  ValueType aDotb = sqrt(a._qs*b._qs + a._qv*b._qv);
  ValueType abMag = aMag * bMag;
  typename _QuaternionRotation3D<ValueType>::_Angle ab =
    ((abMag == 0.0) ? 0.0 :
     arccos(aDotb / abMag));

  if (similar(ab, _QuaternionRotation3D<ValueType>::_Angle(zero())))
  {
    throw std::range_error("QuaternionRotation3D: "
                           "Attempted to interpolate rotations that are too close together.");
  }

  // Projection of v on a in the direction of b.
  ValueType va = sin((1 - lambda)*ab)/sin(ab);

  // Projection of v on b in the direction of a.
  ValueType vb = sin(lambda*ab)/sin(ab);

  return _QuaternionRotation3D<ValueType>(va*a._qs + vb*b._qs,
                                          va*a._qv + vb*b._qv);
}


} // namespace Units

#endif  // Units_QuaternionRotation3D_cpp
