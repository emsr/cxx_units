//
// $Id: Length3D.i,v 1.1.4.1 2007-09-28 04:54:02 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Length3D class.
//

#ifndef Units_Length3D_i
#define Units_Length3D_i


namespace Units
{


template <typename UnitType>
inline
Length3DFormat<UnitType>::Length3DFormat(Length3D const & length):
  _vector(UnitType(length.x).value(),
	  UnitType(length.y).value(),
	  UnitType(length.z).value())
{
}

template <typename UnitType>
inline
Vector3D<typename UnitType::ValueType> Length3DFormat<UnitType>::vector() const
{
  return _vector;
}

template <typename UnitType>
inline
std::ostream & operator<< (std::ostream                   & stream,
                           Length3DFormat<UnitType> const & format)
{
  return stream << format.vector() << ' ' << UnitType::unitsString();
}


} // namespace Units


#endif  // Units_Length3D_i
