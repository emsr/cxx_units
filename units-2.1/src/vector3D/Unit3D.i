//
// $Id: Unit3D.i,v 1.4.2.2 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Unit3D class.
//

#ifndef Units_Unit3D_i
#define Units_Unit3D_i


namespace Units
{


template<typename UnitType>
inline
Unit3D<UnitType>::Unit3D()
{
}


template<typename UnitType>
template<typename ValueType>
inline
Unit3D<UnitType>::Unit3D(ValueType const & x_,
                         ValueType const & y_,
                         ValueType const & z_):
  BaseVectorType(x_,
                 y_,
                 z_)
{
}

template<typename UnitType>
template<typename ValueType>
inline
Unit3D<UnitType>::Unit3D(Vector3D<ValueType> const & v):
  BaseVectorType(v)
{
}

template<typename UnitType>
inline
Unit3D<UnitType>::Unit3D(Zero const &):
  BaseVectorType(zero(),
                 zero(),
                 zero())
{
}


} // namespace Units


#endif  // Units_Unit3D_i
