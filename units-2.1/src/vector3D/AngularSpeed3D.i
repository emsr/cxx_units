//
// $Id: AngularSpeed3D.i,v 1.2.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Angle3D class.
//

#ifndef Units_Angle3D_i
#define Units_Angle3D_i


namespace Units
{


template<typename LengthType, typename TimeType>
inline
AngularSpeed3DFormat<LengthType, TimeType>::
AngularSpeed3DFormat(AngularSpeed3D const & value):
  _vector(AngularSpeedFormat<LengthType, TimeType>(value.x).value(),
	  AngularSpeedFormat<LengthType, TimeType>(value.y).value(),
	  AngularSpeedFormat<LengthType, TimeType>(value.z).value())
{
}

template<typename LengthType, typename TimeType>
inline
Vector3D<typename LengthType::ValueType>
AngularSpeed3DFormat<LengthType, TimeType>::vector() const
{
  return _vector;
}

template<typename LengthType, typename TimeType>
inline
std::ostream &
operator<< (std::ostream                                     & stream,
            AngularSpeed3DFormat<LengthType, TimeType> const & format)
{
  return stream << format.vector()
		<< ' ' << LengthType::unitsString()
                << '/' << TimeType::unitsString();
}


} // namespace Units


#endif  // Units_Angle3D_i
