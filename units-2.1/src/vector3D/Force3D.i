//
// $Id: Force3D.i,v 1.1.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Force3D class.
//

#ifndef Units_Force3D_i
#define Units_Force3D_i


namespace Units
{


template<typename UnitType>
inline
Force3DFormat<UnitType>::Force3DFormat(Force3D const & force):
  _vector(UnitType(force.x).value(),
	  UnitType(force.y).value(),
	  UnitType(force.z).value())
{
}

template<typename UnitType>
inline
Vector3D<typename UnitType::ValueType> Force3DFormat<UnitType>::vector() const
{
  return _vector;
}

template<typename UnitType>
inline
std::ostream & operator<< (std::ostream                  & stream,
                           Force3DFormat<UnitType> const & format)
{
  return stream << format.vector() << ' ' << UnitType::unitsString();
}


} // namespace Units


#endif  // Units_Force3D_i
