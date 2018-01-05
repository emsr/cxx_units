//
// $Id: Rotation2D.i,v 1.1.4.4 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Rotation2D class.
//

#ifndef Units_Rotation2D_i
#define Units_Rotation2D_i

#include <math.h>
#include "scalar/SignedAngle.h"



namespace Units
{


template <typename ValueType>
inline
_Rotation2D<ValueType>::_Rotation2D():
  _xAxis(1, 0)
{
}

template <typename ValueType>
inline
_Rotation2D<ValueType>::_Rotation2D(_Rotation2D const & rotation):
  _xAxis(rotation._xAxis)
{
}

template <typename ValueType>
inline
_Rotation2D<ValueType>::_Rotation2D(_Direction2D<ValueType> const & xAxis):
  _xAxis(xAxis)
{
}

template <typename ValueType>
inline
_Rotation2D<ValueType>::_Rotation2D(_Angle const & angle):
  _xAxis(cos(angle),
         sin(angle))
{
}


// Data access

template <typename ValueType>
inline
typename _Rotation2D<ValueType>::_Angle _Rotation2D<ValueType>::angle() const
{
  return arctan2(_xAxis.y(),
                 _xAxis.x());
}

template <typename ValueType>
inline
_Direction2D<ValueType> _Rotation2D<ValueType>::xAxis () const
{
  return _xAxis;
}

template <typename ValueType>
inline
_Direction2D<ValueType> _Rotation2D<ValueType>::yAxis () const
{
  return _Direction2D<ValueType>(-_xAxis.y(),
                                 _xAxis.x());
}


// Comparison functions

template <typename ValueType>
inline
bool similar(_Rotation2D<ValueType> const & a,
             _Rotation2D<ValueType> const & b,
             typename _Rotation2D<ValueType>::_Angle const & tol)
{
  return similar(typename _Rotation2D<ValueType>::_SignedAngle(a.angle()),
		 typename _Rotation2D<ValueType>::_SignedAngle(b.angle()),
                 tol);
}

template <typename ValueType>
inline
bool         _Rotation2D<ValueType>::operator== (_Rotation2D const & rotation) const
{
  return (_xAxis == rotation._xAxis);
}

template <typename ValueType>
inline
bool         _Rotation2D<ValueType>::operator!= (_Rotation2D const & rotation) const
{
  return (_xAxis != rotation._xAxis);
}


// Arithmetic operators

template <typename ValueType>
inline
_Direction2D<ValueType> operator* (_Rotation2D<ValueType>  const & rotation,
                                   _Direction2D<ValueType> const & direction)
{
  return _Direction2D<ValueType>(rotation*direction.vector());
}

template <typename ValueType>
inline
_Rotation2D<ValueType> _Rotation2D<ValueType>::operator* (_Rotation2D const & r) const
{
  return _Rotation2D(*this * r._xAxis);
}


template <typename ValueType>
inline
_Rotation2D<ValueType> & _Rotation2D<ValueType>::operator*=(_Rotation2D const & rotation)
{
  *this = *this * rotation;
  return *this;
}

template <typename ValueType>
inline
_Rotation2D<ValueType> & _Rotation2D<ValueType>::invert ()
{
  *this = inverse();
  return *this;
}

template <typename ValueType>
inline
_Rotation2D<ValueType> & _Rotation2D<ValueType>::rotate (Angle const & angle)
{
  *this *= _Rotation2D(angle);
  return *this;
}


template <typename ValueType>
inline
std::ostream & operator<< (std::ostream                 & stream,
                           _Rotation2D<ValueType> const & rotation)
{
  return stream << typename _Rotation2D<ValueType>::_DegreesAngle(rotation.angle());
}


} // namespace Units


#endif  // Units_Rotation2D_i
