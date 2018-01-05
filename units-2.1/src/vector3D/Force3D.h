//
// $Id: Force3D.h,v 1.4.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure of force in cartesian
// space.
//

#ifndef Units_Force3D_h
#define Units_Force3D_h

#include <iostream>
#include "scalar/Force.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<Force> Force3D;


///
/// Template class for converting or formating 3D Force output.
///
template<typename UnitType>
class Force3DFormat
{
public:
  typedef typename UnitType::ValueType ValueType;

  Force3DFormat(Force3D const & force);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename UnitType>
std::ostream & operator<< (std::ostream                  & stream,
                           Force3DFormat<UnitType> const & format);


} // namespace Units


#include "Force3D.i"

#endif  // Units_Force3D_h
