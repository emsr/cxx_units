//
// $Id: Unit2D.i,v 1.5.2.4 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Unit2D class.
//

#ifndef Units_Unit2D_i
#define Units_Unit2D_i


namespace Units
{


template<typename UnitType>
inline
Unit2D<UnitType>::Unit2D()
{
}


template<typename UnitType>
template<typename ValueType>
inline
Unit2D<UnitType>::Unit2D(ValueType const & x_,
                         ValueType const & y_):
  BaseVectorType(x_,
                 y_)
{
}

template<typename UnitType>
template<typename ValueType>
inline
Unit2D<UnitType>::Unit2D(Vector2D<ValueType> const & v):
  BaseVectorType(v)
{
}

template<typename UnitType>
inline
Unit2D<UnitType>::Unit2D(Zero const &):
  BaseVectorType(zero(),
                 zero())
{
}


} // namespace Units


#endif  // Units_Unit2D_i
