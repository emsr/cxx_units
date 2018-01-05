//
// $Id: Acceleration2D.h,v 1.3.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure of acceleration in cartesian
// space.
//

#ifndef Units_Acceleration2D_h
#define Units_Acceleration2D_h

#include <iostream>
#include "scalar/Acceleration.h"
#include "Unit2D.h"


namespace Units
{


typedef Unit2D<Acceleration> Acceleration2D;


///
/// Template class for converting or formating 2D Acceleration output.
///
template <typename SpeedType,
          typename TimeType>
class Acceleration2DFormat
{
public:
  typedef typename SpeedType::ValueType ValueType;

  Acceleration2DFormat(Acceleration2D const & acceleration);

  Vector2D<ValueType> vector() const;

private:
  Vector2D<ValueType> _vector;
};



template <typename SpeedType,
          typename TimeType>
std::ostream & operator<< (std::ostream                         & stream,
                           Acceleration2DFormat<SpeedType,
                                                TimeType> const & format);


} // namespace Units


#include "Acceleration2D.i"

#endif  // Units_Acceleration2D_h
