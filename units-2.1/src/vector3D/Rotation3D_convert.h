//
// $Id: Rotation3D_convert.h,v 1.1.2.1 2007-09-28 04:54:03 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Convert between rotation representations.
//

#ifndef Units_Rotation3D_convert_h
#define Units_Rotation3D_convert_h

#include "QuaternionRotation3D.h"
#include "MatrixRotation3D.h"


namespace Units
{


///
/// Construct a unit quaterion from a cosine matrix.
///
template<typename ValueType>
_QuaternionRotation3D<ValueType>
convert(_MatrixRotation3D<ValueType> const & rotation);

///
/// Construct a cosine matrix from a unit quaterion.
///
template<typename ValueType>
_MatrixRotation3D<ValueType>
convert(_QuaternionRotation3D<ValueType> const & rotation);


} // namespace Units


#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Rotation3D_convert.cpp"
#endif

#endif  // Units_Rotation3D_convert_h
