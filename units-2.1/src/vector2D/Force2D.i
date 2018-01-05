//
// $Id: Force2D.i,v 1.1.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Force2D class.
//

#ifndef Units_Force2D_i
#define Units_Force2D_i


namespace Units
{


template <typename UnitType>
inline
Force2DFormat<UnitType>::Force2DFormat(Force2D const & force):
  _vector(UnitType(force.x).value(),
	  UnitType(force.y).value())
{
}

template <typename UnitType>
inline
Vector2D<typename UnitType::ValueType> Force2DFormat<UnitType>::vector() const
{
  return _vector;
}

template <typename UnitType>
inline
std::ostream & operator<< (std::ostream                  & stream,
                           Force2DFormat<UnitType> const & format)
{
  return stream << format.vector() << ' ' << UnitType::unitsString();
}


} // namespace Units


#endif  // Units_Force2D_i
