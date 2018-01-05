//
// $Id: Acceleration3D.i,v 1.1.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Acceleration3D class.
//

#ifndef Units_Acceleration3D_i
#define Units_Acceleration3D_i


namespace Units
{


template<class LengthType, class TimeType>
inline
Acceleration3DFormat<LengthType, TimeType>::
Acceleration3DFormat(Acceleration3D const & value):
  _vector(AccelerationFormat<LengthType, TimeType>(value.x).value(),
	  AccelerationFormat<LengthType, TimeType>(value.y).value(),
	  AccelerationFormat<LengthType, TimeType>(value.z).value())
{
}

template<class LengthType, class TimeType>
inline
Vector3D<typename LengthType::ValueType>
Acceleration3DFormat<LengthType, TimeType>::vector() const
{
  return _vector;
}

template<class LengthType, class TimeType>
inline
std::ostream &
operator<< (std::ostream                                     & stream,
            Acceleration3DFormat<LengthType, TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << LengthType::unitsString()
                << '/' << TimeType::unitsString() << "^2";
}


} // namespace Units


#endif  // Units_Acceleration3D_i
