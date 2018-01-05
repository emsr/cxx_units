//
// $Id: Vector2D.h,v 1.4.4.8 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 2-dimensional unitless vector in cartesian space.
//

#ifndef Units_Vector2D_h
#define Units_Vector2D_h

#include <iostream>
#include "system/units_config.h"
#include "scalar/Angle.h"



namespace Units
{

template <typename ValueType>
class _Direction2D;


template <typename ValueType_>
class Vector2D
{
public:
  typedef ValueType_ ValueType;

  ValueType x;
  ValueType y;


  // Constructors

  //
  // Default constructor gives uninitialized value!
  //
  Vector2D();

  template <typename ValueTypeX,
            typename ValueTypeY>
  Vector2D(ValueTypeX const & x_,
           ValueTypeY const & y_);

  template <typename ValueType2>
  Vector2D(Vector2D<ValueType2> const & vec);


  // Comparison functions

  bool        similarTo  (Vector2D<ValueType> const & b) const
  {
    return (x.similarTo(b.x) &&
            y.similarTo(b.y));
  }

  bool        similarTo  (Vector2D<ValueType> const & b,
			  ValueType           const & tol) const;

  bool        operator== (Vector2D<ValueType> const & vec) const;
  bool        operator!= (Vector2D<ValueType> const & vec) const;


  // Arithmetic operators

  Vector2D  & operator*= (typename UnitlessType<ValueType>::Result const & scale);
  Vector2D  & operator/= (typename UnitlessType<ValueType>::Result const & scale);
 
  Vector2D    operator-  () const;

  Vector2D    operator+  (Vector2D<ValueType> const & vec) const;
  Vector2D    operator-  (Vector2D<ValueType> const & vec) const;

  Vector2D  & operator+= (Vector2D<ValueType> const & vec);
  Vector2D  & operator-= (Vector2D<ValueType> const & vec);


  // Miscellaneous useful functions

  ///
  /// Return the scalar magnitude (2 norm) of this.
  ///
  ValueType      magnitude  () const;

  ///
  /// Return the direction (unit vector) of this.
  ///
  _Direction2D<typename UnitlessType<ValueType>::Result> direction() const
  {
    ValueType mag = magnitude();
    return _Direction2D<typename UnitlessType<ValueType>::Result>(x/mag,
                                                                  y/mag);
  }

  //
  // Return the Euclidean distance from this to another vector.
  //
  ValueType      distanceTo (Vector2D<ValueType> const & vec) const;

  //
  // Return the angle between this and another vector.
  //
  inline
  Angle       angleTo    (Vector2D<ValueType> const & vec) const;

  //
  // Distance to an infinite line through p1 and p2.
  //
  ValueType      distanceToLine   (Vector2D<ValueType> const & p1,
                                   Vector2D<ValueType> const & p2) const;

  //
  // Distance to a line segment from p1 and p2.
  //
  ValueType      distanceToSegment(Vector2D<ValueType> const & p1,
                                   Vector2D<ValueType> const & p2) const;


  ///
  /// Test the proper operation of the methods.  WARNING: This is for
  /// library testing only and not exported.
  ///
  static
  bool test();
};


template <typename ValueType>
Vector2D<ValueType>
operator* (Vector2D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale);

template <typename ValueType>
Vector2D<ValueType>
operator* (typename UnitlessType<ValueType>::Result const & scale,
           Vector2D<ValueType>                      const & vec);

template <typename ValueType>
Vector2D<ValueType>
operator/ (Vector2D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale);


///
/// Generic dot product (assumes ValueType*ValueType = ValueType)
///
template <typename ValueType>
ValueType operator* (Vector2D<ValueType> const & lhs,
                     Vector2D<ValueType> const & rhs);

///
/// Generic cross product (assumes ValueType*ValueType = ValueType)
///
template <typename ValueType>
ValueType operator% (Vector2D<ValueType> const & lhs,
                     Vector2D<ValueType> const & rhs);


template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS1>            const & lhs,
           Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS2>            const & rhs)
{
  return Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >(lhs.x*rhs,
                                                              lhs.y*rhs);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_DIV_RESULT> >
operator/ (Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS2>            const & rhs)
{
  return Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_DIV_RESULT> >(lhs.x/rhs,
                                                              lhs.y/rhs);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS> const & lhs,
           Vector2D<ValueType_>           const & rhs);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator* (Vector2D<ValueType_>           const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS> const & rhs)
{
  return Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >(lhs.x*rhs,
                                                   lhs.y*rhs);
}


///
/// Specialized dot product for Unit scalar types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT>
operator* (Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);

// specialization for dot product returning squared units
template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Unit<UNITS_UNIT_TEMPLATE_ARGS_SQR_RESULT>
operator* (Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & lhs,
           Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & rhs)
{
  return Unit<UNITS_UNIT_TEMPLATE_ARGS_SQR_RESULT>(lhs.x * rhs.x +
                                                   lhs.y * rhs.y);
}

///
/// Specialized cross product for Unit scalar types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT>
operator% (Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);


template <typename ValueType>
bool similar(Vector2D<ValueType> const & a,
             Vector2D<ValueType> const & b,
             ValueType           const & tol);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
bool similar(Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
             Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b,
             Unit<UNITS_UNIT_TEMPLATE_ARGS>            const & tol)
{
  return (similar(a.x, b.x, tol) &&
          similar(a.y, b.y, tol));
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
bool similar(Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
             Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b)
{
  return (similar(a.x, b.x) &&
          similar(a.y, b.y));
}


//
// Return the length of a given vector.
//
template <typename ValueType>
ValueType      magnitude  (Vector2D<ValueType> const & vec);

//
// Return the Euclidean distance between two vectors.
//
template <typename ValueType>
ValueType      distance   (Vector2D<ValueType> const & a,
                           Vector2D<ValueType> const & b);

//
// Return the angle between two vectors.
//
template <typename T>
Angle       angle      (Vector2D<T> const & a,
                        Vector2D<T> const & b);

// Not intended for public use.
template <typename ValueType,
          typename ValueSqrdType>
Angle _angle(Vector2D<ValueType> const & a,
             Vector2D<ValueType> const & b,
             ValueSqrdType       const & zero);

//
// Return a vector half-way between two vectors.
//
template <typename T>
Vector2D<T> midpoint   (Vector2D<T> const & a,
                        Vector2D<T> const & b);

//
// Return a vector in a line from a to b as lambda goes from 0 to 1.
//
template <typename ValueType>
Vector2D<ValueType> interpolate(Vector2D<ValueType> const & a,
                                Vector2D<ValueType> const & b,
                                ValueType           const   lambda);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
interpolate(Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
            Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b,
            ValueType_                                const   lambda)
{
  return (a + lambda*(b - a));
}


template <typename ValueType>
std::ostream & operator<< (std::ostream               & stream,
                           Vector2D<ValueType>  const & vec);


} // namespace Units


#include "Vector2D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Vector2D.cpp"
#endif

#endif  // Units_Vector2D_h
