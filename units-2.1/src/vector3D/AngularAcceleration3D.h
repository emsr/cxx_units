//
// $Id: AngularAcceleration3D.h,v 1.3.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure of angular acceleration.
//

#ifndef Units_AngularAcceleration3D_h
#define Units_AngularAcceleration3D_h

#include <iostream>
#include "scalar/AngularAcceleration.h"
#include "Unit3D.h"



namespace Units
{


typedef Unit3D<AngularAcceleration> AngularAcceleration3D;


///
/// Template class for converting or formating 3D AngularAcceleration output.
///
template<typename AngleType,
         typename TimeType>
class AngularAcceleration3DFormat
{
public:
  typedef typename AngleType::ValueType ValueType;

  AngularAcceleration3DFormat(AngularAcceleration3D const & acceleration);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename AngleType,
         typename TimeType>
std::ostream &
operator<< (std::ostream                                           & stream,
            AngularAcceleration3DFormat<AngleType, TimeType> const & format);


} // namespace Units


#include "AngularAcceleration3D.i"

#endif  // Units_AngularAcceleration3D_h
