//
// $Id: Angle2D.i,v 1.1.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Angle2D class.
//

#ifndef Units_Angle2D_i
#define Units_Angle2D_i


namespace Units
{


template <typename UnitType>
inline
Angle2DFormat<UnitType>::Angle2DFormat(Angle2D const & angle):
  _vector(UnitType(angle.x).value(),
	  UnitType(angle.y).value())
{
}

template <typename UnitType>
inline
Vector2D<typename UnitType::ValueType> Angle2DFormat<UnitType>::vector() const
{
  return _vector;
}

template <typename UnitType>
inline
std::ostream & operator<< (std::ostream                  & stream,
                           Angle2DFormat<UnitType> const & format)
{
  return stream << format.vector() << ' ' << UnitType::unitsString();
}


} // namespace Units


#endif  // Units_Angle2D_i
