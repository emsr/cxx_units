//
// $Id: Length2D.i,v 1.1.4.3 2006-02-03 04:42:34 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Length2D class.
//

#ifndef Units_Length2D_i
#define Units_Length2D_i


namespace Units
{


template <typename UnitType>
inline
Length2DFormat<UnitType>::Length2DFormat(Length2D const & length):
  _vector(UnitType(length.x).value(),
	  UnitType(length.y).value())
{
}

template <typename UnitType>
inline
Vector2D<typename UnitType::ValueType> Length2DFormat<UnitType>::vector() const
{
  return _vector;
}

template <typename UnitType>
inline
std::ostream & operator<< (std::ostream                   & stream,
                           Length2DFormat<UnitType> const & format)
{
  return stream << format.vector() << ' ' << UnitType::unitsString();
}


} // namespace Units


#endif  // Units_Length2D_i
