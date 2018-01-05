//
// $Id: Speed3D.h,v 1.3.4.1 2007-09-28 04:54:03 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure of speed in cartesian
// space.
//

#ifndef Units_Speed3D_h
#define Units_Speed3D_h

#include <iostream>
#include "scalar/Speed.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<Speed> Speed3D;


///
/// Template class for converting or formating 3D Speed output.
///
template<typename LengthType,
         typename TimeType>
class Speed3DFormat
{
public:
  typedef typename LengthType::ValueType ValueType;

  Speed3DFormat(Speed3D const & speed);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename LengthType,
         typename TimeType>
std::ostream & operator<< (std::ostream                  & stream,
                           Speed3DFormat<LengthType,
                                         TimeType> const & format);


} // namespace Units


#include "Speed3D.i"

#endif  // Units_Speed3D_h
