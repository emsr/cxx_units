//
// $Id: Vector2D.cpp,v 1.4.4.7 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the Vector2D class.
//

#ifndef Units_Vector2D_cpp
#define Units_Vector2D_cpp

#include <iostream>
#include <math.h>
#include "Vector2D.h"


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
bool Vector2D<ValueType>::operator== (Vector2D<ValueType> const & vec) const
{
  return ((x == vec.x) &&
	  (y == vec.y));
}

template <typename ValueType>
bool Vector2D<ValueType>::operator!= (Vector2D<ValueType> const & vec) const
{
  return ((x != vec.x) ||
	  (y != vec.y));
}

template <typename ValueType>
bool similar(Vector2D<ValueType> const & a,
             Vector2D<ValueType> const & b,
             ValueType           const & tol)
{
  return ((abs(a.x - b.x) < tol) &&
	  (abs(a.y - b.y) < tol));
}

template <>
inline
bool similar(Vector2D<double> const & a,
             Vector2D<double> const & b,
             double           const & tol)
{
  return ((fabs(a.x - b.x) < tol) &&
	  (fabs(a.y - b.y) < tol));
}

template <>
inline
bool similar(Vector2D<float> const & a,
             Vector2D<float> const & b,
             float           const & tol)
{
  return ((fabsf(a.x - b.x) < tol) &&
	  (fabsf(a.y - b.y) < tol));
}


// Arithmetic operators

template <typename ValueType>
ValueType operator* (Vector2D<ValueType> const & lhs,
                     Vector2D<ValueType> const & rhs)
{
  return (lhs.x*rhs.x +
          lhs.y*rhs.y);
}

template <typename ValueType>
ValueType operator% (Vector2D<ValueType> const & lhs,
                     Vector2D<ValueType> const & rhs)
{
  return (lhs.x*rhs.y -
          lhs.y*rhs.x);
}


template <typename ValueType>
Vector2D<ValueType>
operator* (Vector2D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale)
{
  return Vector2D<ValueType>(vec.x * scale,
                             vec.y * scale);
}

template <typename ValueType>
Vector2D<ValueType>
operator/ (Vector2D<ValueType>                      const & vec,
           typename UnitlessType<ValueType>::Result const & scale)
{
  return Vector2D<ValueType>(vec.x / scale,
                             vec.y / scale);
}

template <typename ValueType>
Vector2D<ValueType> &
Vector2D<ValueType>::
operator*= (typename UnitlessType<ValueType>::Result const & scale)
{
  x *= scale;
  y *= scale;
  return *this;
}

template <typename ValueType>
Vector2D<ValueType> &
Vector2D<ValueType>::
operator/= (typename UnitlessType<ValueType>::Result const & scale)
{
  x /= scale;
  y /= scale;
  return *this;
}


template <typename ValueType>
Vector2D<ValueType> Vector2D<ValueType>::operator- () const
{
  return Vector2D(-x,
                  -y);
}

template <typename ValueType>
Vector2D<ValueType> Vector2D<ValueType>::operator+ (Vector2D<ValueType> const & vec) const
{
  return Vector2D(x + vec.x,
		  y + vec.y);
}

template <typename ValueType>
Vector2D<ValueType> Vector2D<ValueType>::operator- (Vector2D<ValueType> const & vec) const
{
  return Vector2D(x - vec.x,
		  y - vec.y);
}


template <typename ValueType>
Vector2D<ValueType> & Vector2D<ValueType>::operator+= (Vector2D<ValueType> const & vec)
{
  x += vec.x;
  y += vec.y;
  return *this;
}

template <typename ValueType>
Vector2D<ValueType> & Vector2D<ValueType>::operator-= (Vector2D<ValueType> const & vec)
{
  x -= vec.x;
  y -= vec.y;
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
Angle Vector2D<ValueType>::angleTo(Vector2D<ValueType> const & vec)  const
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
Vector2D<ValueType> interpolate(Vector2D<ValueType> const & a,
                                Vector2D<ValueType> const & b,
                                ValueType           const   lambda)
{
  return (a + lambda*(b - a));
}


template <typename ValueType_>
ValueType_
Vector2D<ValueType_>::distanceToLine(Vector2D<ValueType_> const & p1,
                                     Vector2D<ValueType_> const & p2) const
{
  Vector2D<ValueType_> v1 = p2    - p1;
  Vector2D<ValueType_> v2 = *this - p1;

  typename UnitlessType<ValueType_>::Result lambda = (v1*v2)/(v1*v1);

  return Units::magnitude(v2 - lambda*v1);
}   

template <typename ValueType_>
ValueType_
Vector2D<ValueType_>::distanceToSegment(Vector2D<ValueType_> const & p1,
                                        Vector2D<ValueType_> const & p2) const
{
  Vector2D<ValueType_> v1 = p2    - p1;
  Vector2D<ValueType_> v2 = *this - p1;

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
                           Vector2D<ValueType> const & vec)
{
  return stream << '('  << vec.x
		<< ", " << vec.y << ')';
}



} // namespace Units


#endif // Units_Vector2D_cpp
