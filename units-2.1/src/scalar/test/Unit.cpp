//
// $Id: Unit.cpp,v 1.5.4.3 2005-12-22 06:16:41 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Unit class.
//

#ifndef Units_Unit_cpp
#define Units_Unit_cpp

#include <iostream>
#include "SpecificUnit.h"


namespace Units
{


template <typename T>
struct Unit_Tester;

template <typename ValueType,
          typename SpecificUnitTraits>
struct Unit_Tester<SpecificUnit<ValueType,
                                SpecificUnitTraits> >
{
  static
  bool genericTest(char const * name)
{
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits> Unit;

  bool status = true;

  if (sizeof(Unit) != sizeof(ValueType))
  {
    std::cerr << name << "::genericTest(): "
              << "Size does not equal size of a native type." << std::endl;
    status = false;
  }

  if (!Unit(1.0).similarTo(Unit(1.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "similar() between identical units failed." << std::endl;
    status = false;
  }
  if (!Unit(1.0).similarTo(Unit(1.0000005), Unit(1e-6)))
  {
    std::cerr << name << "::genericTest(): "
              << "similar() between similar units (small tol) failed."
              << std::endl;
    status = false;
  }
  if (!Unit(1.0).similarTo(Unit(1.5), Unit(1.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "similar() between similar units (large tol) failed."
              << std::endl;
    status = false;
  }
  if (Unit(1.0).similarTo(Unit(2.0), Unit(1e-6)))
  {
    std::cerr << name << "::genericTest(): "
              << "similar() between unsimilar units failed." << std::endl;
    status = false;
  }

  if (Unit(1.0) == Unit(2.0))
  {
    std::cerr << name
              << "::genericTest(): operator==() failed." << std::endl;
    status = false;
  }
  if (Unit(1.0) != Unit(1.0))
  {
    std::cerr << name
              << "::genericTest(): operator!=() failed." << std::endl;
    status = false;
  }
  if (Unit(2.0) < Unit(1.0))
  {
    std::cerr << name
              << "::genericTest(): operator<() failed." << std::endl;
    status = false;
  }
  if (Unit(1.0) > Unit(2.0))
  {
    std::cerr << name
              << "::genericTest(): operator>() failed." << std::endl;
    status = false;
  }
  if (Unit(2.0) <= Unit(1.0))
  {
    std::cerr << name
              << "::genericTest(): operator<=() failed." << std::endl;
    status = false;
  }
  if (Unit(1.0) >= Unit(2.0))
  {
    std::cerr << name
              << "::genericTest(): operator>=() failed." << std::endl;
    status = false;
  }

  if (!(2.0 * Unit(1.0)).similarTo(Unit(2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator*(double, Unit) failed."
              << std::endl;
    status = false;
  }
  if (!(Unit(1.0) * 2.0).similarTo(Unit(2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator*(double) failed." << std::endl;
    status = false;
  }
  if (!(Unit(2.0) / 2.0).similarTo(Unit(1.0)))
  {
    std::cerr << name
              << "::genericTest(): operator/(double) failed." << std::endl;
    status = false;
  }

  Unit unit;

  unit = Unit(1.0);
  if (!(unit *= 2.0).similarTo(Unit(2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator*=(double) failed." << std::endl;
    status = false;
  }
  if (!(unit /= 2.0).similarTo(Unit(1.0)))
  {
    std::cerr << name
              << "::genericTest(): operator/=(double) failed." << std::endl;
    status = false;
  }

  if (!(-Unit(2.0)).similarTo(Unit(-2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator-() failed." << std::endl;
    status = false;
  }
  if (!(Unit(1.0) + Unit(1.0)).similarTo(Unit(2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator+("
              << name << ") failed." << std::endl;
    status = false;
  }
  if (!(Unit(2.0) - Unit(1.0)).similarTo(Unit(1.0)))
  {
    std::cerr << name
              << "::genericTest(): operator-("
              << name << ") failed." << std::endl;
    status = false;
  }

  unit = Unit(1.0);
  if (!(unit += Unit(1.0)).similarTo(Unit(2.0)))
  {
    std::cerr << name
              << "::genericTest(): operator+=("
              << name << ") failed." << std::endl;
    status = false;
  }
  if (!(unit -= Unit(1.0)).similarTo(Unit(1.0)))
  {
    std::cerr << name
              << "::genericTest(): operator-=("
              << name << ") failed." << std::endl;
    status = false;
  }

  if (fabs(Unit(1.0)/Unit(1.0) - 1.0) > 1e-6)
  {
    std::cerr << name
              << "::genericTest(): operator/("
              << name << ") failed." << std::endl;
    status = false;
  }


  if (!similar(abs(Unit(-1.0)),
               Unit(1.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "abs() failed." << std::endl;
    status = false;
  }

  if (!similar(sqrt(Unit(2.0)*Unit(2.0)),
               Unit(2.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "sqrt() failed." << std::endl;
    status = false;
  }

  if (!similar(min(Unit(-1.0),
                   Unit(2.0)),
               Unit(-1.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "min() failed." << std::endl;
    status = false;
  }

  if (!similar(max(Unit(-1.0),
                   Unit(2.0)),
               Unit(2.0)))
  {
    std::cerr << name << "::genericTest(): "
              << "max() failed." << std::endl;
    status = false;
  }


  typedef typename Unit::BaseUnitType BaseUnitType;
  {
    BaseUnitType x = Units::zero();
    if (x != Unit(0.0))
    {
      std::cerr << name << "::genericTest(): "
                << "zero() failed." << std::endl;
      status = false;
    }
  }
  {
    BaseUnitType x = Units::infinity();
    if (x != Unit(HUGE_VAL))
    {
      std::cerr << name << "::genericTest(): "
                << "infinity() failed." << std::endl;
      status = false;
    }
  }
  {
    BaseUnitType x = -Units::infinity();
    if (x != Unit(-HUGE_VAL))
    {
      std::cerr << name << "::genericTest(): "
                << "-infinity() failed." << std::endl;
      status = false;
    }
  }

  return status;
}
};


} // namespace Units

#endif  // Units_Unit_cpp
