//
// $Id: Force2D.h,v 1.4.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure of force in cartesian
// space.
//

#ifndef Units_Force2D_h
#define Units_Force2D_h

#include <iostream>
#include "scalar/Force.h"
#include "Unit2D.h"


namespace Units
{


typedef Unit2D<Force> Force2D;


///
/// Template class for converting or formating 2D Force output.
///
template <typename UnitType>
class Force2DFormat
{
public:
  typedef typename UnitType::ValueType ValueType;

  Force2DFormat(Force2D const & force);

  Vector2D<ValueType> vector() const;

private:
  Vector2D<ValueType> _vector;
};



template <typename UnitType>
std::ostream & operator<< (std::ostream                  & stream,
                           Force2DFormat<UnitType> const & format);


} // namespace Units


#include "Force2D.i"

#endif  // Units_Force2D_h
