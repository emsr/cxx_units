//
// $Id: Unit2D.h,v 1.14.2.7 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unit of measure in cartesian space.
//

#ifndef Units_Unit2D_h
#define Units_Unit2D_h

#include <iostream>
#include "system/units_config.h"
#include "scalar/Angle.h"
#include "Vector2D.h"


namespace Units
{


///
/// This is a thin wrapper around Vector2D to provide automatic
/// promotion of specific unit vectors to base unit vectors.
///
template <typename UnitType>
class Unit2D: public Vector2D<typename UnitType::BaseUnitType>
{
public:
  typedef typename UnitType::BaseUnitType BaseUnitType;
  typedef Vector2D<BaseUnitType> BaseVectorType;

  //
  // Default constructor gives uninitialized value!
  //
  Unit2D();

  template <typename ValueType>
  Unit2D(ValueType const & x_,
	 ValueType const & y_);

  template <typename ValueType>
  Unit2D(Vector2D<ValueType> const & vec);

  // set all components to zero
  Unit2D(Zero const &);


  ///
  /// Test the specific unit type.  WARNING: This is for library
  /// testing only and not exported.
  ///
  static
  bool test();
};


template <typename ValueType,
          typename SpecificUnitTraits>
std::ostream &
operator<< (std::ostream                                    & stream,
            Unit2D<SpecificUnit<ValueType,
                                SpecificUnitTraits> > const & vec)
{
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits> SpecificType;
  return stream << '('
                << SpecificType(vec.x).value() << ", "
                << SpecificType(vec.y).value() << ')';
}


} // namespace Units


#include "Unit2D.i"

#endif  // Units_Unit2D_h
