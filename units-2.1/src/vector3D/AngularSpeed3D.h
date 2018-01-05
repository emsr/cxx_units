//
// $Id: AngularSpeed3D.h,v 1.4.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional measure of AngularSpeed in cartesian space.
//
// This is probably only useful for representing a rotation vector.
// Adding a Rotation class would exceed the scope of this library,
// which is to strictly represent units of measure with no
// interpretation imposed on them.  But this class still needs to be
// provided in addition to an external Rotation class because it needs
// special visibility to compute things like the magnitude.
//
// A 2-dimensional measure of AngularSpeed doesn't make any sense, so
// this is the only vector class with AngularSpeed.
//

#ifndef Units_AngularSpeed3D_h
#define Units_AngularSpeed3D_h

#include <iostream>
#include "scalar/AngularSpeed.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<AngularSpeed> AngularSpeed3D;


///
/// Template class for converting or formating 3D Angle output.
///
template<typename AngleType,
         typename TimeType>
class AngularSpeed3DFormat
{
public:
  typedef typename AngleType::ValueType ValueType;

  AngularSpeed3DFormat(AngularSpeed3D const & angle);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename AngleType,
         typename TimeType>
std::ostream &
operator<< (std::ostream                                    & stream,
            AngularSpeed3DFormat<AngleType, TimeType> const & format);


} // namespace Units


#include "AngularSpeed3D.i"

#endif  // Units_AngularSpeed3D_h
