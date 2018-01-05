//
// $Id: Speed3D.i,v 1.1.4.1 2007-09-28 04:54:03 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Speed3D class.
//

#ifndef Units_Speed3D_i
#define Units_Speed3D_i


namespace Units
{


template<typename LengthType,
         typename TimeType>
inline
Speed3DFormat<LengthType, TimeType>::Speed3DFormat(Speed3D const & speed):
  _vector(SpeedFormat<LengthType, TimeType>(speed.x).value(),
	  SpeedFormat<LengthType, TimeType>(speed.y).value(),
	  SpeedFormat<LengthType, TimeType>(speed.z).value())
{
}

template<typename LengthType, typename TimeType>
inline
Vector3D<typename LengthType::ValueType>
Speed3DFormat<LengthType, TimeType>::vector() const
{
  return _vector;
}

template<typename LengthType, typename TimeType>
inline
std::ostream & operator<< (std::ostream                              & stream,
                           Speed3DFormat<LengthType, TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << LengthType::unitsString()
                << '/' << TimeType::unitsString();
}


} // namespace Units


#endif  // Units_Speed3D_i
