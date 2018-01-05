//
// $Id: Acceleration2D.i,v 1.1.4.1 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Acceleration2D class.
//

#ifndef Units_Acceleration2D_i
#define Units_Acceleration2D_i


namespace Units
{


template <typename SpeedType,
          typename TimeType>
inline
Acceleration2DFormat<SpeedType, TimeType>::
Acceleration2DFormat(Acceleration2D const & acceleration):
  _vector(AccelerationFormat<SpeedType, TimeType>(acceleration.x).value(),
	  AccelerationFormat<SpeedType, TimeType>(acceleration.y).value())
{
}

template <typename SpeedType,
          typename TimeType>
inline
Vector2D<typename SpeedType::ValueType>
Acceleration2DFormat<SpeedType, TimeType>::vector() const
{
  return _vector;
}

template <typename SpeedType,
          typename TimeType>
inline
std::ostream & operator<< (std::ostream                         & stream,
                           Acceleration2DFormat<SpeedType,
                                                TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << SpeedType::unitsString()
                << '/' << TimeType::unitsString() << "^2";
}


} // namespace Units


#endif  // Units_Acceleration2D_i
