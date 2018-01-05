//
// $Id: Length2D.h,v 1.3.4.3 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure of length in cartesian
// space.
//

#ifndef Units_Length2D_h
#define Units_Length2D_h

#include <iostream>
#include "scalar/Length.h"
#include "Unit2D.h"


namespace Units
{


typedef Unit2D<Length> Length2D;


///
/// Template class for converting or formating 2D Length output.
///
template <typename UnitType>
class Length2DFormat
{
public:
  typedef typename UnitType::ValueType ValueType;

  Length2DFormat(Length2D const & length);

  Vector2D<ValueType> vector() const;

private:
  Vector2D<ValueType> _vector;
};



template <typename UnitType>
std::ostream & operator<< (std::ostream                   & stream,
                           Length2DFormat<UnitType> const & format);


} // namespace Units


#include "Length2D.i"

#endif  // Units_Length2D_h
