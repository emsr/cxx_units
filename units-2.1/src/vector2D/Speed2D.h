//
// $Id: Speed2D.h,v 1.3.4.3 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure of speed in cartesian
// space.
//

#ifndef Units_Speed2D_h
#define Units_Speed2D_h

#include <iostream>
#include "scalar/Speed.h"
#include "Unit2D.h"


namespace Units
{


typedef Unit2D<Speed> Speed2D;


///
/// Template class for converting or formating 2D Speed output.
///
template <typename LengthType,
          typename TimeType>
class Speed2DFormat
{
public:
  typedef typename LengthType::ValueType ValueType;

  Speed2DFormat(Speed2D const & speed);

  Vector2D<ValueType> vector() const;

private:
  Vector2D<ValueType> _vector;
};



template <typename LengthType,
          typename TimeType>
std::ostream & operator<< (std::ostream                  & stream,
                           Speed2DFormat<LengthType,
                                         TimeType> const & format);


} // namespace Units


#include "Speed2D.i"

#endif  // Units_Speed2D_h
