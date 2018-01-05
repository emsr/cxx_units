//
// $Id: Speed2D.i,v 1.1.4.2 2006-02-03 04:42:34 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Speed2D class.
//

#ifndef Units_Speed2D_i
#define Units_Speed2D_i


namespace Units
{


template <typename LengthType,
          typename TimeType>
inline
Speed2DFormat<LengthType, TimeType>::Speed2DFormat(Speed2D const & speed):
  _vector(SpeedFormat<LengthType, TimeType>(speed.x).value(),
	  SpeedFormat<LengthType, TimeType>(speed.y).value())
{
}

template <typename LengthType,
          typename TimeType>
inline
Vector2D<typename LengthType::ValueType>
Speed2DFormat<LengthType, TimeType>::vector() const
{
  return _vector;
}

template <typename LengthType,
          typename TimeType>
inline
std::ostream & operator<< (std::ostream                              & stream,
                           Speed2DFormat<LengthType, TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << LengthType::unitsString()
                << '/' << TimeType::unitsString();
}


} // namespace Units


#endif  // Units_Speed2D_i
