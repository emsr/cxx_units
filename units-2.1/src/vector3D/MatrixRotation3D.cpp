//
// $Id: MatrixRotation3D.cpp,v 1.4.4.5 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the MatrixRotation3D class.
//

#ifndef Units_MatrixRotation3D_cpp
#define Units_MatrixRotation3D_cpp

#include <math.h>
#include "MatrixRotation3D.h"


namespace Units
{


template<typename ValueType>
_MatrixRotation3D<ValueType> const *
_MatrixRotation3D<ValueType>::_identity = 0;

template<typename ValueType>
_MatrixRotation3D<ValueType> const & _MatrixRotation3D<ValueType>::identity()
{
  if (!_identity)
  {
    _identity = new _MatrixRotation3D<ValueType>
      (_Direction3D<ValueType>(1, 0, 0),
       _Direction3D<ValueType>(0, 1, 0),
       _Direction3D<ValueType>(0, 0, 1));
  }
  return *_identity;
}


// 2 trigs, 17 mults, 10 adds
template<typename ValueType>
_MatrixRotation3D<ValueType>::
_MatrixRotation3D(_Direction3D<ValueType> const & axis,
                  _Angle                  const & angle):
  _xAxis(1, 0, 0),
  _yAxis(0, 1, 0),
  _zAxis(0, 0, 1)
{
  ValueType S = sin(angle);
  ValueType C = cos(angle);
  ValueType V = 1 - C;        // versine

  //
  // Compute cosine matrix components.
  //
  _xAxis = _Direction3D<ValueType>
    (V*axis.x()*axis.vector() +
     Vector3D<ValueType>( C,           S*axis.z(), -S*axis.y()));

  _yAxis = _Direction3D<ValueType>
    (V*axis.y()*axis.vector() +
     Vector3D<ValueType>(-S*axis.z(),  C,           S*axis.x()));

  _zAxis = _Direction3D<ValueType>
    (V*axis.z()*axis.vector() +
     Vector3D<ValueType>( S*axis.y(), -S*axis.x(),  C));
}


// Data access

//
// Based on matrix-to-quaternion conversion, which handles
// close-to-singular cases nicely.
//
template<typename ValueType>
_Direction3D<ValueType> _MatrixRotation3D<ValueType>::axis() const
{
  ValueType trace = (_xAxis.x() +
                     _yAxis.y() +
                     _zAxis.z());

  ValueType temp2 = (1 - trace)*0.25;  // used to compute vector components

  // Find the magnitudes of the quaternion vector elements (Klummp, eqn 6).

  ValueType           temp;  // squared component value
  Vector3D<ValueType> vmag;

  if ((temp = (_xAxis.x()*0.5 + temp2)) <= 0)
    vmag.x = 0;
  else
    vmag.x = ::sqrt(temp);

  if ((temp = (_yAxis.y()*0.5 + temp2)) <= 0)
    vmag.y = 0;
  else
    vmag.y = ::sqrt(temp);

  if ((temp = (_zAxis.z()*0.5 + temp2)) <= 0)
    vmag.z = 0;
  else
    vmag.z = ::sqrt(temp);

  // Find element with the largest magnitude.
  ValueType maxMag   = vmag.x;
  int       maxIndex = 0;

  if (vmag.y > maxMag)
  {
    maxMag   = vmag.y;
    maxIndex = 1;
  }
  if (vmag.z > maxMag)
  {
    maxMag   = vmag.z;
    maxIndex = 2;
  }

  Vector3D<ValueType> ax;

  // Now find the signs of the q vector elements (Klummp, eqns 4, 6, 12-15).
  switch (maxIndex)
  {
  case 0:                                  // cycle: i = 0, j = 1, k = 2
    ax.x = math_sign(      _yAxis.z() -
                           _zAxis.y()) *vmag.x;

    ax.y = math_sign(ax.x*(_xAxis.y() +
                           _yAxis.x()))*vmag.y;

    ax.z = math_sign(ax.x*(_xAxis.z() +
                           _zAxis.x()))*vmag.z;
    break;

  case 1:                                  // cycle: i = 1, j = 2, k = 0
    ax.y = math_sign(      _zAxis.x() -
                           _xAxis.z()) *vmag.y;

    ax.z = math_sign(ax.y*(_yAxis.z() +
                           _zAxis.y()))*vmag.z;

    ax.x = math_sign(ax.y*(_yAxis.x() +
                           _xAxis.y()))*vmag.x;
    break;

  case 2:                                  // cycle: i = 2, j = 0, k = 1
    ax.z = math_sign(      _xAxis.y() -
                           _yAxis.x()) *vmag.z;

    ax.x = math_sign(ax.z*(_zAxis.x() +
                           _xAxis.z()))*vmag.x;

    ax.y = math_sign(ax.z*(_zAxis.y() +
                           _yAxis.z()))*vmag.y;
    break;
  }

  try
  {
    return _Direction3D<ValueType>(ax);
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

//
// From http://www.pst.stsci.edu/moss/rotations_req.html
//
template<typename ValueType>
typename _MatrixRotation3D<ValueType>::_Angle
_MatrixRotation3D<ValueType>::angle() const
{
  return arccos(ValueType(0.5)*(_xAxis.x() +
                                _yAxis.y() +
                                _zAxis.z() - 1));
}


// 9 mults,  6 adds
template<typename ValueType,
         typename ValueType2>
Vector3D<ValueType2>
operator* (_MatrixRotation3D<ValueType> const & rotation,
           Vector3D<ValueType2>         const & vector)
{
  return (rotation.xAxis().vector()*vector.x +
	  rotation.yAxis().vector()*vector.y +
	  rotation.zAxis().vector()*vector.z);
}

template<typename ValueType>
_Direction3D<ValueType>
operator* (_MatrixRotation3D<ValueType> const & rotation,
           _Direction3D<ValueType>      const & direction)
{
  return _Direction3D<ValueType>(rotation * direction.vector());
}

// 27 mults, 18 adds
template<typename ValueType>
_MatrixRotation3D<ValueType>
_MatrixRotation3D<ValueType>::operator* (_MatrixRotation3D const & r) const
{
  return _MatrixRotation3D(*this * r._xAxis,
                           *this * r._yAxis,
                           *this * r._zAxis);
}


// Inverse of an orthonormal matrix is its transpose.
template<typename ValueType>
_MatrixRotation3D<ValueType> _MatrixRotation3D<ValueType>::inverse () const
{
  // Avoid calling the public Direction2D constructor.
  _Direction3D<ValueType> invX(_xAxis.x(),
                               _yAxis.x(),
                               _zAxis.x());
  _Direction3D<ValueType> invY(_xAxis.y(),
                               _yAxis.y(),
                               _zAxis.y());
  _Direction3D<ValueType> invZ(_xAxis.z(),
                               _yAxis.z(),
                               _zAxis.z());

  return _MatrixRotation3D(invX, invY, invZ);
}


template<typename ValueType>
_MatrixRotation3D<ValueType>
delta(_MatrixRotation3D<ValueType> const & from,
      _MatrixRotation3D<ValueType> const & to)
{
  // TODO: Do we need to handle loop-around case like we do for quaternions?
  _MatrixRotation3D<ValueType> from_to = (from.inverse()*to);
  return from_to;
}


//
// Rotate a to b by a fraction of the angle between them.
//
// 20 mults, 11 adds, 3 divs, 8 trigs
template<typename ValueType>
_MatrixRotation3D<ValueType>
interpolate(_MatrixRotation3D<ValueType> const & a,
            _MatrixRotation3D<ValueType> const & b,
            ValueType                    const   lambda)
  throw (std::range_error)
{
  // Get the shortest rotation from a to b.
  _MatrixRotation3D<ValueType> relative = delta(a, b);

  typename _MatrixRotation3D<ValueType>::_Angle ab = relative.angle();

  if (similar(ab, _MatrixRotation3D<ValueType>::_Angle(zero())))
  {
    throw std::range_error("MatrixRotation3D: "
                           "Attempted to interpolate rotations that are too close together.");
  }

  return (_MatrixRotation3D<ValueType>(relative.axis(), ab*lambda) * a);
}


template<typename ValueType>
std::ostream & operator<< (std::ostream                       & stream,
                           _MatrixRotation3D<ValueType> const & rotation)
{
  stream << std::endl;
  stream <<"   [ "
         << rotation.xAxis().x() << ' '
         << rotation.yAxis().x() << ' '
         << rotation.zAxis().x() << " ]\n";
  stream <<"   [ "
         << rotation.xAxis().y() << ' '
         << rotation.yAxis().y() << ' '
         << rotation.zAxis().y() << " ]\n";
  stream <<"   [ "
         << rotation.xAxis().z() << ' '
         << rotation.yAxis().z() << ' '
         << rotation.zAxis().z() << " ]";
  return stream;
}


} // namespace Units

#endif  // Units_MatrixRotation3D_cpp
