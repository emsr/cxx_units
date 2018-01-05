//
// $Id: AngularAcceleration3D.i,v 1.2.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the AngularAcceleration3D class.
//

#ifndef Units_AngularAcceleration3D_i
#define Units_AngularAcceleration3D_i


namespace Units
{


template<class LengthType, class TimeType>
inline
AngularAcceleration3DFormat<LengthType, TimeType>::
AngularAcceleration3DFormat(AngularAcceleration3D const & value):
  _vector(AngularAccelerationFormat<LengthType, TimeType>(value.x).value(),
	  AngularAccelerationFormat<LengthType, TimeType>(value.y).value(),
	  AngularAccelerationFormat<LengthType, TimeType>(value.z).value())
{
}

template<class LengthType, class TimeType>
inline
Vector3D<typename LengthType::ValueType>
AngularAcceleration3DFormat<LengthType, TimeType>::vector() const
{
  return _vector;
}

template<class LengthType, class TimeType>
inline
std::ostream &
operator<< (std::ostream                                            & stream,
            AngularAcceleration3DFormat<LengthType, TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << LengthType::unitsString()
                << '/' << TimeType::unitsString() << "^2";
}


} // namespace Units


#endif  // Units_AngularAcceleration3D_i
