//
// $Id: QuaternionRotation3D.i,v 1.5.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the QuaternionRotation3D class.
//

#ifndef Units_QuaternionRotation3D_i
#define Units_QuaternionRotation3D_i

#include <math.h>



namespace Units
{


template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::_QuaternionRotation3D():
  _qs(1),
  _qv(0, 0, 0)
{
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::
_QuaternionRotation3D(_QuaternionRotation3D const & rot):
  _qs(rot._qs),
  _qv(rot._qv)
{
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::
_QuaternionRotation3D(ValueType           const & qs,
                      Vector3D<ValueType> const & qv):
  _qs(qs),
  _qv(qv)
{
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::
_QuaternionRotation3D(_Direction3D<ValueType> const & axis_,
                      _Angle                  const & angle_):
  _qs(cos(ValueType(0.5)*angle_)),
  _qv(sin(ValueType(0.5)*angle_)*axis_.vector())
{
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::
_QuaternionRotation3D(ValueType const array[4]):
  _qs(array[0]),
  _qv(array[1],
      array[2],
      array[3])
{
  normalize();
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>::_QuaternionRotation3D(ValueType const & qs,
                                                        ValueType const & qvx,
                                                        ValueType const & qvy,
                                                        ValueType const & qvz):
  _qs(qs),
  _qv(qvx,
      qvy,
      qvz)
{
  normalize();
}


// Comparison functions

template<typename ValueType>
inline
bool _QuaternionRotation3D<ValueType>::
operator== (_QuaternionRotation3D const & rot) const
{
  return ((_qs == rot._qs) &&
	  (_qv == rot._qv));
}

template<typename ValueType>
inline
bool _QuaternionRotation3D<ValueType>::
operator!= (_QuaternionRotation3D const & rot) const
{
  return ((_qs != rot._qs) &&
	  (_qv != rot._qv));
}


// Data access

template<typename ValueType>
inline
_Direction3D<ValueType> _QuaternionRotation3D<ValueType>::axis() const
{
  try
  {
    return _Direction3D<ValueType>(_qv);
  }
  catch (std::range_error const &)
  {
    //
    // Rotation is identity -- it doesn't matter which way the axis
    // points because the rotation angle is zero.
    //
    return _Direction3D<ValueType>(0, 0, 1);
  }
}

template<typename ValueType>
inline
typename _QuaternionRotation3D<ValueType>::_Angle
_QuaternionRotation3D<ValueType>::angle() const
{
  if (_qs >= 1.0)
  {
    return _Angle(zero());
  }
  else if (_qs <= -1.0)
  {
    return _DegreesAngle(180.0);
  }
  else
  {
    return arccos(_qs)*2;
  }
}


template<typename ValueType>
inline
ValueType           const & _QuaternionRotation3D<ValueType>::qs() const
{
  return _qs;
}
template<typename ValueType>
inline
Vector3D<ValueType> const & _QuaternionRotation3D<ValueType>::qv() const
{
  return _qv;
}


// Arithmetic operators

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType> &
_QuaternionRotation3D<ValueType>::
operator*=(_QuaternionRotation3D const & rotation)
{
  *this = *this * rotation;
  return *this;
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType>
_QuaternionRotation3D<ValueType>::inverse () const
{
  return _QuaternionRotation3D(_qs, -_qv);
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType> & _QuaternionRotation3D<ValueType>::invert ()
{
  *this = this->inverse();
  return *this;
}

template<typename ValueType>
inline
_QuaternionRotation3D<ValueType> & _QuaternionRotation3D<ValueType>::
rotate    (_Direction3D<ValueType> const & axis,
           _Angle                  const & angle)
{
  *this *= _QuaternionRotation3D(axis, angle);
  return *this;
}

template<typename ValueType>
inline
typename _QuaternionRotation3D<ValueType>::_Angle
error(_QuaternionRotation3D<ValueType> const & from,
      _QuaternionRotation3D<ValueType> const & to)
{
  _QuaternionRotation3D<ValueType> delta_quat = delta(from, to);
  return delta_quat.angle();
}

template<typename ValueType>
inline
bool similar(_QuaternionRotation3D<ValueType> const & a,
             _QuaternionRotation3D<ValueType> const & b,
             typename _QuaternionRotation3D<ValueType>::_Angle const & tol)
{
  typedef typename _QuaternionRotation3D<ValueType>::_Angle _Angle;
  return similar(error(a, b),
                 _Angle(zero()),
                 tol);
}


template<typename ValueType>
inline
std::ostream & operator<< (std::ostream                           & stream,
                           _QuaternionRotation3D<ValueType> const & rotation)
{
  return stream << '(' << rotation.qs() << ", " << rotation.qv() << ')';
}

template<>
inline
dAngle _QuaternionRotation3D<double>::defaultTolerance()
{
  return dRadiansAngle(1e-6);
}

template<>
inline
fAngle _QuaternionRotation3D<float>::defaultTolerance()
{
  return fRadiansAngle(1e-3);
}


} // namespace Units


#endif  // Units_QuaternionRotation3D_i
