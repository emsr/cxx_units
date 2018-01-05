//
// $Id: Unit3D.h,v 1.14.2.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unit of measure in cartesian space.
//

#ifndef Units_Unit3D_h
#define Units_Unit3D_h

#include <iostream>
#include "system/units_config.h"
#include "scalar/Angle.h"
#include "Vector3D.h"



namespace Units
{


///
/// This is a thin wrapper around Vector3D to provide automatic
/// promotion of specific unit vectors to base unit vectors.
///
template<typename UnitType>
class Unit3D: public Vector3D<typename UnitType::BaseUnitType>
{
public:
  typedef typename UnitType::BaseUnitType BaseUnitType;
  typedef Vector3D<BaseUnitType> BaseVectorType;

  //
  // Default constructor gives uninitialized value!
  //
  Unit3D();

  template<typename ValueType>
  Unit3D(ValueType const & x_,
	 ValueType const & y_,
	 ValueType const & z_);

  template<typename ValueType>
  Unit3D(Vector3D<ValueType> const & vec);

  // set all components to zero
  Unit3D(Zero const &);


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
            Unit3D<SpecificUnit<ValueType,
                                SpecificUnitTraits> > const & vec)
{
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits> SpecificType;
  return stream << '('
                << SpecificType(vec.x).value() << ", "
                << SpecificType(vec.y).value() << ", "
                << SpecificType(vec.z).value() << ')';
}


} // namespace Units


#include "Unit3D.i"

#endif  // Units_Unit3D_h
