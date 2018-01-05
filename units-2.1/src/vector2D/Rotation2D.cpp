//
// $Id: Rotation2D.cpp,v 1.3.4.5 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Rotation2D class.
//

#ifndef Units_Rotation2D_cpp
#define Units_Rotation2D_cpp

#include "Rotation2D.h"


namespace Units
{


template <typename ValueType>
_Rotation2D<ValueType> const
_Rotation2D<ValueType>::_identity(_Direction2D<ValueType>(1, 0));

template <typename ValueType>
_Rotation2D<ValueType> const & _Rotation2D<ValueType>::identity()
{
  return _identity;
}


// Inverse of an orthonormal matrix is its transpose.
template <typename ValueType>
_Rotation2D<ValueType> _Rotation2D<ValueType>::inverse() const
{
  // TODO: Avoid calling the public Direction2D constructor.
  return _Rotation2D<ValueType>(_Direction2D<ValueType>(_xAxis.x(),
                                                        -_xAxis.y()));
}


} // namespace Units


#endif  // Units_Rotation2D_cpp
