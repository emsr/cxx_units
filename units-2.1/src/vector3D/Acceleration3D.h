//
// $Id: Acceleration3D.h,v 1.3.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure of acceleration in cartesian
// space.
//

#ifndef Units_Acceleration3D_h
#define Units_Acceleration3D_h

#include <iostream>
#include "scalar/Acceleration.h"
#include "Unit3D.h"


namespace Units
{


typedef Unit3D<Acceleration> Acceleration3D;


///
/// Template class for converting or formating 3D Acceleration output.
///
template<typename LengthType,
         typename TimeType>
class Acceleration3DFormat
{
public:
  typedef typename LengthType::ValueType ValueType;

  Acceleration3DFormat(Acceleration3D const & acceleration);

  Vector3D<ValueType> vector() const;

private:
  Vector3D<ValueType> _vector;
};



template<typename LengthType,
         typename TimeType>
std::ostream &
operator<< (std::ostream                         & stream,
            Acceleration3DFormat<LengthType,
                                 TimeType> const & format);


} // namespace Units


#include "Acceleration3D.i"

#endif  // Units_Acceleration3D_h
