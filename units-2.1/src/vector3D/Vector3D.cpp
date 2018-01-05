//
// $Id: Vector3D.cpp,v 1.3.4.4 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Vector3D class.
//

#ifndef Units_Vector3D_cpp
#define Units_Vector3D_cpp

#include <iostream>
#include <math.h>
#include "scalar/Format.h"
#include "Vector3D.h"


namespace Units
{


//
// The following operators are not inlined because they involve
// more than a few operations each -- the time spent *doing* the
// function is far greater than the time spent *calling* it.
// Inlining these would only make really big executables with
// a doubtful increase in speed.
//
// (See Section 7.1.2 of The Annotated C++ Reference Manual by Stroustrup.)
//

// Comparison functions

template <typename ValueType>
bool Vector3D<ValueType>::operator== (Vector3D<ValueType> const & vec) const
{
  return ((x == vec.x) &&
	  (y == vec.y) &&
	  (z == vec.z));
}

template <typename ValueType>
bool Vector3D<ValueType>::operator!= (Vector3D<ValueType> const & vec) const
{
  return ((x != vec.x) ||
	  (y != vec.y) ||
	  (z != vec.z));
}

template <typename ValueType>
bool similar(Vector3D<ValueType> const & a,
             Vector3D<ValueType> const & b,
             ValueType           const & tol)
{
  return ((abs(a.x - b.x) < tol) &&
	  (abs(a.y - b.y) < tol) &&
	  (abs(a.z - b.z) < tol));
}

template <>
inline
bool similar(Vector3D<double> const & a,
             Vector3D<double> const & b,
             double           const & tol)
{
  return ((fabs(a.x - b.x) < tol) &&
	  (fabs(a.y - b.y) < tol) &&
	  (fabs(a.z - b.z) < tol));
}

template <>
inline
bool similar(Vector3D<float> const & a,
             Vector3D<float> const & b,
             float           const & tol)
{
  return ((fabsf(a.x - b.x) < tol) &&
	  (fabsf(a.y - b.y) < tol) &&
	  (fabsf(a.z - b.z) < tol));
}


// Arithmetic operators

template <typename ValueType>
ValueType operator* (Vector3D<ValueType> const & lhs,
                     Vector3D<ValueType> const & rhs)
{
  return (lhs.x*rhs.x +
          lhs.y*rhs.y +
          lhs.z*rhs.z);
}

template <typename ValueType>
Vector3D<ValueType> operator% (Vector3D<ValueType> const & lhs,
                               Vector3D<ValueType> const & rhs)
{
  return Vector3D<ValueType>(lhs.y*rhs.z - lhs.z*rhs.y,
                             lhs.z*rhs.x - lhs.x*rhs.z,
                             lhs.x*rhs.y - lhs.y*rhs.x);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator% (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS1> > const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
    (lhs.y*rhs.z - lhs.z*rhs.y,
     lhs.z*rhs.x - lhs.x*rhs.z,
     lhs.x*rhs.y - lhs.y*rhs.x);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator% (Vector3D<ValueType_>                      const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >(lhs.y*rhs.z - lhs.z*rhs.y,
                                                   lhs.z*rhs.x - lhs.x*rhs.z,
                                                   lhs.x*rhs.y - lhs.y*rhs.x);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
operator% (Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> > const & lhs,
           Vector3D<ValueType_>                      const & rhs)
{
  return Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS> >(lhs.y*rhs.z - lhs.z*rhs.y,
                                                   lhs.z*rhs.x - lhs.x*rhs.z,
                                                   lhs.x*rhs.y - lhs.y*rhs.x);
}


template <typename ValueType>
Vector3D<ValueType>
operator* (Vector3D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale)
{
  return Vector3D<ValueType>(vec.x * scale,
                             vec.y * scale,
                             vec.z * scale);
}

template <typename ValueType>
Vector3D<ValueType>
operator/ (Vector3D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale)
{
  return Vector3D<ValueType>(vec.x / scale,
                             vec.y / scale,
                             vec.z / scale);
}

template <typename ValueType>
Vector3D<ValueType> &
Vector3D<ValueType>::
operator*= (typename UnitlessType<ValueType>::Result const & scale)
{
  x *= scale;
  y *= scale;
  z *= scale;
  return *this;
}

template <typename ValueType>
Vector3D<ValueType> &
Vector3D<ValueType>::
operator/= (typename UnitlessType<ValueType>::Result const & scale)
{
  x /= scale;
  y /= scale;
  z /= scale;
  return *this;
}


template <typename ValueType>
Vector3D<ValueType> Vector3D<ValueType>::operator- () const
{
  return Vector3D(-x,
                  -y,
                  -z);
}

template <typename ValueType>
Vector3D<ValueType> Vector3D<ValueType>::operator+ (Vector3D<ValueType> const & vec) const
{
  return Vector3D(x + vec.x,
		  y + vec.y,
		  z + vec.z);
}

template <typename ValueType>
Vector3D<ValueType> Vector3D<ValueType>::operator- (Vector3D<ValueType> const & vec) const
{
  return Vector3D(x - vec.x,
		  y - vec.y,
		  z - vec.z);
}


template <typename ValueType>
Vector3D<ValueType> & Vector3D<ValueType>::operator+= (Vector3D<ValueType> const & vec)
{
  x += vec.x;
  y += vec.y;
  z += vec.z;
  return *this;
}

template <typename ValueType>
Vector3D<ValueType> & Vector3D<ValueType>::operator-= (Vector3D<ValueType> const & vec)
{
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  return *this;
}


template <typename ValueType>
struct ValueSquared
{
  typedef ValueType Result;
  static Result zeroSquared()
  {
    return 0;
  }
};

template <UNITS_UNIT_TEMPLATE_DECL_ARGS>
struct ValueSquared<Unit<UNITS_UNIT_TEMPLATE_ARGS> >
{
  typedef Unit<UNITS_UNIT_TEMPLATE_ARGS_SQR_RESULT> Result;
  static Result zeroSquared()
  {
    return Result(zero());
  }
};


template <typename ValueType>
Angle Vector3D<ValueType>::angleTo(Vector3D<ValueType> const & vec)  const
{
  ValueType aMag  = magnitude();
  ValueType bMag  = vec.magnitude();
  typename ValueSquared<ValueType>::Result abMag = aMag * bMag;

  if (abMag == ValueSquared<ValueType>::zeroSquared())
  {
    return Angle(zero());
  }
  double ratio = ((*this * vec) / abMag);
  //
  // Protect against numeric errors.
  //
  if (ratio <= -1.0)
  {
    static DegreesAngle const ang180(180);
    return ang180;
  }
  else if (ratio >= 1.0)
  {
    return Angle(zero());
  }
  return arccos(ratio);
}


template <typename ValueType>
Vector3D<ValueType> interpolate(Vector3D<ValueType> const & a,
                                Vector3D<ValueType> const & b,
                                ValueType           const   lambda)
{
  return (a + lambda*(b - a));
}


template <typename ValueType_>
ValueType_
Vector3D<ValueType_>::distanceToLine(Vector3D<ValueType_> const & p1,
                                     Vector3D<ValueType_> const & p2) const
{
  Vector3D<ValueType_> v1 = p2    - p1;
  Vector3D<ValueType_> v2 = *this - p1;

  typename UnitlessType<ValueType_>::Result lambda = (v1*v2)/(v1*v1);

  return Units::magnitude(v2 - lambda*v1);
}   

template <typename ValueType_>
ValueType_
Vector3D<ValueType_>::distanceToSegment(Vector3D<ValueType_> const & p1,
                                        Vector3D<ValueType_> const & p2) const
{
  Vector3D<ValueType_> v1 = p2    - p1;
  Vector3D<ValueType_> v2 = *this - p1;

  typename UnitlessType<ValueType_>::Result lambda = (v1*v2)/(v1*v1);

  if (lambda < 0)
    return distance(*this, p1);
  else if (lambda > 1)
    return distance(*this, p2);
  else
    return Units::magnitude(v2 - lambda*v1);
}


template <typename ValueType>
std::ostream & operator<< (std::ostream              & stream,
                           Vector3D<ValueType> const & vec)
{
  return stream << '('  << vec.x
		<< ", " << vec.y
		<< ", " << vec.z << ')';
}


} // namespace Units


#endif // Units_Vector3D_cpp
