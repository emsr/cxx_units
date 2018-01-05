//
// $Id: Torque3D.i,v 1.2.4.1 2007-09-28 04:54:03 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Torque3D class.
//

#ifndef Units_Torque3D_i
#define Units_Torque3D_i


namespace Units
{


template<class ForceType, class LengthType>
inline
Torque3DFormat<ForceType, LengthType>::Torque3DFormat(Torque3D const & value):
  _vector(TorqueFormat<ForceType, LengthType>(value.x).value(),
	  TorqueFormat<ForceType, LengthType>(value.y).value(),
	  TorqueFormat<ForceType, LengthType>(value.z).value())
{
}

template<class ForceType, class LengthType>
inline
Vector3D<typename ForceType::ValueType>
Torque3DFormat<ForceType, LengthType>::vector() const
{
  return _vector;
}

template<class ForceType, class LengthType>
inline
std::ostream &
operator<< (std::ostream                                & stream,
            Torque3DFormat<ForceType, LengthType> const & format)
{
  return stream << format.vector() << ' '
		<< ForceType::unitsString() << '-'
                << LengthType::unitsString();
}


} // namespace Units


#endif  // Units_Torque3D_i
