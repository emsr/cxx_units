//
// $Id: Torque3D.h,v 1.5.4.1 2007-09-28 04:54:03 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure of torque in cartesian
// space.
//

#ifndef Units_Torque3D_h
#define Units_Torque3D_h

#include <iostream>
#include "scalar/Torque.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<Torque> Torque3D;


#if 0
//
// Interaction with Length and Force.
//
UNITS_EXPORT
Torque3D operator% (Length3D const & length,
                    Force3D  const & force);

//
// Interaction with Inertia and AngularAcceleration.
//
UNITS_EXPORT
Torque3D operator* (AngularAcceleration3D const & acceleration,
                    Inertia               const & inertia);

//
// operator/(AngularAcceleration3D) isn't provided because it would need to
// require that the directions were colinear.  To get Inertia from a
// Torque3D and AngularAcceleration3D, divide their magnitudes.
//

UNITS_EXPORT
AngularAcceleration3D operator/ (Torque3D const & torque,
                                 Inertia  const & inertia);
#endif


///
/// Template class for converting or formating 3D Torque output.
///
template<typename ForceType,
         typename LengthType>
class Torque3DFormat
{
public:
  typedef typename ForceType::ValueType ValueType;

  Torque3DFormat(Torque3D const & torque);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename ForceType, typename LengthType>
std::ostream &
operator<< (std::ostream                                & stream,
            Torque3DFormat<ForceType, LengthType> const & format);


} // namespace Units


#include "Torque3D.i"

#endif  // Units_Torque3D_h
