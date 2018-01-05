//
// $Id: Length3D.h,v 1.3.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure of length in cartesian
// space.
//

#ifndef Units_Length3D_h
#define Units_Length3D_h

#include <iostream>
#include "scalar/Length.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<Length> Length3D;


///
/// Template class for converting or formating 3D Length output.
///
template<typename UnitType>
class Length3DFormat
{
public:
  typedef typename UnitType::ValueType ValueType;

  Length3DFormat(Length3D const & length);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename UnitType>
std::ostream & operator<< (std::ostream                   & stream,
                           Length3DFormat<UnitType> const & format);


} // namespace Units


#include "Length3D.i"

#endif  // Units_Length3D_h
