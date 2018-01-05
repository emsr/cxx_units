//
// $Id: MatrixRotation3D.i,v 1.2.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the MatrixRotation3D class.
//

#ifndef Units_MatrixRotation3D_i
#define Units_MatrixRotation3D_i

#include <math.h>



namespace Units
{


template<typename ValueType>
inline
_MatrixRotation3D<ValueType>::_MatrixRotation3D():
  _xAxis(1, 0, 0),
  _yAxis(0, 1, 0),
  _zAxis(0, 0, 1)
{
}

template<typename ValueType>
inline
_MatrixRotation3D<ValueType>::
_MatrixRotation3D(_MatrixRotation3D const & rotation):
  _xAxis(rotation._xAxis),
  _yAxis(rotation._yAxis),
  _zAxis(rotation._zAxis)
{
}

template<typename ValueType>
inline
_MatrixRotation3D<ValueType>::
_MatrixRotation3D(_Direction3D<ValueType> const & xAxis,
                  _Direction3D<ValueType> const & yAxis,
                  _Direction3D<ValueType> const & zAxis)
  throw (std::range_error):
  _xAxis(xAxis),
  _yAxis(yAxis),
  _zAxis(zAxis)
{
  if (fabs(_xAxis.operator*(_yAxis)) > 1e-5)
  {
    throw std::range_error("MatrixRotation3D: "
                           "X and Y axes must be perpendicular.");
  }
  if (fabs(_yAxis.operator*(_zAxis)) > 1e-5)
  {
    throw std::range_error("MatrixRotation3D: "
                           "Y and Z axes must be perpendicular.");
  }
}


// Comparison functions

template<typename ValueType>
inline
bool _MatrixRotation3D<ValueType>::
operator== (_MatrixRotation3D const & rotation) const
{
  return ((_xAxis == rotation._xAxis) &&
	  (_yAxis == rotation._yAxis) &&
	  (_zAxis == rotation._zAxis));
}

template<typename ValueType>
inline
bool _MatrixRotation3D<ValueType>::
operator!= (_MatrixRotation3D const & rotation) const
{
  return ((_xAxis != rotation._xAxis) &&
	  (_yAxis != rotation._yAxis) &&
	  (_zAxis != rotation._zAxis));
}


// Data access

template<typename ValueType>
inline
_Direction3D<ValueType> _MatrixRotation3D<ValueType>::xAxis () const
{
  return _Direction3D<ValueType>(_xAxis);
}

template<typename ValueType>
inline
_Direction3D<ValueType> _MatrixRotation3D<ValueType>::yAxis () const
{
  return _Direction3D<ValueType>(_yAxis);
}

template<typename ValueType>
inline
_Direction3D<ValueType> _MatrixRotation3D<ValueType>::zAxis () const
{
  return _Direction3D<ValueType>(_zAxis);
}


// Arithmetic operators

template<typename ValueType>
inline
_MatrixRotation3D<ValueType> &
_MatrixRotation3D<ValueType>::operator*=(_MatrixRotation3D const & rotation)
{
  *this = *this * rotation;
  return *this;
}

template<typename ValueType>
inline
_MatrixRotation3D<ValueType> & _MatrixRotation3D<ValueType>::invert ()
{
  *this = inverse();
  return *this;
}

template<typename ValueType>
inline
_MatrixRotation3D<ValueType> & _MatrixRotation3D<ValueType>::
rotate    (_Direction3D<ValueType> const & axis,
           _Angle                  const & angle)
{
  *this *= _MatrixRotation3D(axis, angle);
  return *this;
}

template<typename ValueType>
inline
typename _MatrixRotation3D<ValueType>::_Angle
error(_MatrixRotation3D<ValueType> const & from,
      _MatrixRotation3D<ValueType> const & to)
{
  _MatrixRotation3D<ValueType> delta_quat = delta(from, to);
  return delta_quat.angle();
}

template<typename ValueType>
inline
bool similar(_MatrixRotation3D<ValueType> const & a,
             _MatrixRotation3D<ValueType> const & b,
             typename _MatrixRotation3D<ValueType>::_Angle const & tol)
{
  typedef typename _MatrixRotation3D<ValueType>::_Angle _Angle;
  return similar(error(a, b),
                 _Angle(zero()),
                 tol);
}

template<>
inline
dAngle _MatrixRotation3D<double>::defaultTolerance()
{
  return dRadiansAngle(1e-6);
}

template<>
inline
fAngle _MatrixRotation3D<float>::defaultTolerance()
{
  return fRadiansAngle(1e-3);
}


} // namespace Units


#endif  // Units__MatrixRotation3D_i
