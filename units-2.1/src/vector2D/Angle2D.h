//
// $Id: Angle2D.h,v 1.3.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// A Unit2D<Angle> represents a 2-dimensional measure of angle in
// *cartesian* space.  This is a cartesian "flat" angle vector, not
// one on a sphere!  There will be no wrapping around poles.
//

#ifndef Units_Angle2D_h
#define Units_Angle2D_h

#include <iostream>
#include "scalar/Angle.h"
#include "Unit2D.h"


namespace Units
{


typedef Unit2D<Angle> Angle2D;


///
/// Template class for converting or formating 2D Angle output.
///
template <typename UnitType>
class Angle2DFormat
{
public:
  typedef typename UnitType::ValueType ValueType;

  Angle2DFormat(Angle2D const & angle);

  Vector2D<ValueType> vector() const;

private:
  Vector2D<ValueType> _vector;
};



template <typename UnitType>
std::ostream & operator<< (std::ostream                  & stream,
                           Angle2DFormat<UnitType> const & format);


} // namespace Units


#include "Angle2D.i"

#endif  // Units_Angle2D_h
