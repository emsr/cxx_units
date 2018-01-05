//
// $Id: Vector3D.h,v 1.3.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Represent a 3-dimensional unitless vector in cartesian space.
//

#ifndef Units_Vector3D_h
#define Units_Vector3D_h

#include <iostream>
#include "system/units_config.h"
#include "scalar/Angle.h"



namespace Units
{

template <typename ValueType>
class _Direction3D;


template <typename ValueType_>
class Vector3D
{
public:
  typedef ValueType_ ValueType;

  ValueType x;
  ValueType y;
  ValueType z;


  // Constructors

  //
  // Default constructor gives uninitialized value!
  //
  Vector3D();

  template <typename ValueTypeX,
            typename ValueTypeY,
            typename ValueTypeZ>
  Vector3D(ValueTypeX const & x_,
           ValueTypeY const & y_,
           ValueTypeZ const & z_);

  template <typename ValueType2>
  Vector3D(Vector3D<ValueType2> const & vec);


  // Comparison functions

  bool        similarTo  (Vector3D<ValueType> const & b) const
  {
    return (x.similarTo(b.x) &&
            y.similarTo(b.y) &&
            z.similarTo(b.z));
  }

  bool        similarTo  (Vector3D<ValueType> const & b,
			  ValueType           const & tol) const;

  bool        operator== (Vector3D<ValueType> const & vec) const;
  bool        operator!= (Vector3D<ValueType> const & vec) const;


  // Arithmetic operators

  Vector3D  & operator*= (typename UnitlessType<ValueType>::Result const & scale);
  Vector3D  & operator/= (typename UnitlessType<ValueType>::Result const & scale);
 
  Vector3D    operator-  () const;

  Vector3D    operator+  (Vector3D<ValueType> const & vec) const;
  Vector3D    operator-  (Vector3D<ValueType> const & vec) const;

  Vector3D  & operator+= (Vector3D<ValueType> const & vec);
  Vector3D  & operator-= (Vector3D<ValueType> const & vec);


  // Miscellaneous useful functions

  ///
  /// Return the scalar magnitude (2 norm) of this.
  ///
  ValueType      magnitude  () const;

  ///
  /// Return the direction (unit vector) of this.
  ///
  _Direction3D<typename UnitlessType<ValueType>::Result> direction() const
  {
    ValueType mag = magnitude();
    return _Direction3D<typename UnitlessType<ValueType>::Result>(x/mag,
                                                                  y/mag,
                                                                  z/mag);
  }

  //
  // Return the Euclidean distance from this to another vector.
  //
  ValueType      distanceTo (Vector3D<ValueType> const & vec) const;

  //
  // Return the angle between this and another vector.
  //
  inline
  Angle       angleTo    (Vector3D<ValueType> const & vec) const;

  //
  // Distance to an infinite line through p1 and p2.
  //
  ValueType      distanceToLine   (Vector3D<ValueType> const & p1,
                                   Vector3D<ValueType> const & p2) const;

  //
  // Distance to a line segment from p1 and p2.
  //
  ValueType      distanceToSegment(Vector3D<ValueType> const & p1,
                                   Vector3D<ValueType> const & p2) const;


  ///
  /// Test the proper operation of the methods.  WARNING: This is for
  /// library testing only and not exported.
  ///
  static
  bool test();
};


template <typename ValueType>
Vector3D<ValueType>
operator* (Vector3D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale);

template <typename ValueType>
Vector3D<ValueType>
operator* (typename UnitlessType<ValueType>::Result const & scale,
           Vector3D<ValueType>                      const & vec);

template <typename ValueType>
Vector3D<ValueType>
operator/ (Vector3D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale);


///
/// Generic dot product (assumes ValueType*ValueType = ValueType)
///
template <typename ValueType>
ValueType operator* (Vector3D<ValueType> const & lhs,
                     Vector3D<ValueType> const & rhs);

///
/// Generic cross product (assumes ValueType*ValueType = ValueType)
///
template <typename ValueType>
Vector3D<ValueType> operator% (Vector3D<ValueType> const & lhs,
                               Vector3D<ValueType> const & rhs);


template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS1>            const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS2>            const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >(lhs.x*rhs,
                                                              lhs.y*rhs,
                                                              lhs.z*rhs);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_DIV_RESULT> >
operator/ (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS2>            const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_DIV_RESULT> >(lhs.x/rhs,
                                                              lhs.y/rhs,
                                                              lhs.z/rhs);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS> const & lhs,
           Vector3D<ValueType_>           const & rhs);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator* (Vector3D<ValueType_>           const & lhs,
           Unit<UNITS_UNIT_TEMPLATE_ARGS> const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >(lhs.x*rhs,
                                                   lhs.y*rhs,
                                                   lhs.z*rhs);
}


///
/// Specialized dot product for Unit scalar types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT>
operator* (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);

// specialization for dot product returning squared units
template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Unit<UNITS_UNIT_TEMPLATE_ARGS_SQR_RESULT>
operator* (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & rhs)
{
  return (lhs.x * rhs.x +
          lhs.y * rhs.y +
          lhs.z * rhs.z);
}

///
/// Specialized dot product for Unit and unitless types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Unit<UNITS_UNIT_TEMPLATE_ARGS>
operator* (Vector3D<ValueType_>                      const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & rhs)
{
  return (lhs.x * rhs.x +
          lhs.y * rhs.y +
          lhs.z * rhs.z);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Unit<UNITS_UNIT_TEMPLATE_ARGS>
operator* (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & lhs,
           Vector3D<ValueType_>                      const & rhs)
{
  return (lhs.x * rhs.x +
          lhs.y * rhs.y +
          lhs.z * rhs.z);
}

///
/// Specialized cross product for Unit scalar types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator% (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs);

///
/// Specialized cross product for Unit and unitless types.
///
template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator% (Vector3D<ValueType_>                      const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & rhs);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator% (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & lhs,
           Vector3D<ValueType_>                      const & rhs);


template <typename ValueType>
bool similar(Vector3D<ValueType> const & a,
             Vector3D<ValueType> const & b,
             ValueType           const & tol);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
bool similar(Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
             Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b,
             Unit<UNITS_UNIT_TEMPLATE_ARGS>            const & tol)
{
  return (similar(a.x, b.x, tol) &&
          similar(a.y, b.y, tol) &&
          similar(a.z, b.z, tol));
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
bool similar(Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
             Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b)
{
  return (similar(a.x, b.x) &&
          similar(a.y, b.y) &&
          similar(a.z, b.z));
}


//
// Return the length of a given vector.
//
template <typename ValueType>
ValueType      magnitude  (Vector3D<ValueType> const & vec);

//
// Return the Euclidean distance between two vectors.
//
template <typename ValueType>
ValueType      distance   (Vector3D<ValueType> const & a,
                           Vector3D<ValueType> const & b);

//
// Return the angle between two vectors.
//
template <typename T>
Angle       angle      (Vector3D<T> const & a,
                        Vector3D<T> const & b);

// Not intended for public use.
template <typename ValueType,
          typename ValueSqrdType>
Angle _angle(Vector3D<ValueType> const & a,
             Vector3D<ValueType> const & b,
             ValueSqrdType       const & zero);

//
// Return a vector half-way between two vectors.
//
template <typename T>
Vector3D<T> midpoint   (Vector3D<T> const & a,
                        Vector3D<T> const & b);

//
// Return a vector in a line from a to b as lambda goes from 0 to 1.
//
template <typename ValueType>
Vector3D<ValueType> interpolate(Vector3D<ValueType> const & a,
                                Vector3D<ValueType> const & b,
                                ValueType           const   lambda);

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
interpolate(Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & a,
            Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & b,
            ValueType_                                const   lambda)
{
  return (a + lambda*(b - a));
}


//
// Create normal vector to plane formed by p1, p2, and p3.
// NOTE: Value will *not* be normalized (for efficiency).
//
template<typename ValueType>
Vector3D<ValueType>
planeNormal(Vector3D<ValueType> const & p1,
            Vector3D<ValueType> const & p2,
            Vector3D<ValueType> const & p3)
{
  return ((p2 - p1) % (p3 - p1));
}


template <typename ValueType>
std::ostream & operator<< (std::ostream               & stream,
                           Vector3D<ValueType>  const & vec);


} // namespace Units


#include "Vector3D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "Vector3D.cpp"
#endif

#endif  // Units_Vector3D_h
