//
// $Id: Vector2D.i,v 1.2.4.4 2006-02-03 05:49:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Vector2D class.
//

#ifndef Units_Vector2D_i
#define Units_Vector2D_i

#include <math.h>



namespace Units
{


template <typename ValueType>
inline
Vector2D<ValueType>::Vector2D()
{
}


template <typename ValueType>
template <typename ValueTypeX,
          typename ValueTypeY>
inline
Vector2D<ValueType>::Vector2D(ValueTypeX const & x_,
                              ValueTypeY const & y_):
  x(x_),
  y(y_)
{
}

template <typename ValueType>
template <typename ValueType2>
inline
Vector2D<ValueType>::Vector2D(Vector2D<ValueType2> const & vec):
  x(vec.x),
  y(vec.y)
{
}


template <typename ValueType>
inline
bool Vector2D<ValueType>::similarTo(Vector2D<ValueType> const & b,
                                    ValueType           const & tol) const
{
  return similar(*this,
                 b,
                 tol);
}


template <typename ValueType>
inline
Vector2D<ValueType>
operator* (typename UnitlessType<ValueType>::Result const & scale,
           Vector2D<ValueType>                      const & vec)
{
  return (vec * scale);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
inline
Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS1>            const & lhs,
           Vector2D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs)
{
  return (rhs * lhs);
}


template <typename ValueType>
inline
ValueType Vector2D<ValueType>::magnitude() const
{
  return sqrt(*this * *this);
}

template <>
inline
double Vector2D<double>::magnitude() const
{
  return ::sqrt(*this * *this);
}

template <>
inline
float Vector2D<float>::magnitude() const
{
  return ::sqrtf(*this * *this);
}

template <typename ValueType>
inline
ValueType magnitude(Vector2D<ValueType> const & vec)
{
   return vec.magnitude();
}


template <typename ValueType>
inline
ValueType
Vector2D<ValueType>::distanceTo(Vector2D<ValueType> const & vec)  const
{
   return Units::magnitude(vec - *this);
}

template <typename ValueType>
inline
ValueType distance(Vector2D<ValueType> const & a,
                   Vector2D<ValueType> const & b)
{
   return a.distanceTo(b);
}

template <typename ValueType>
inline
Angle angle(Vector2D<ValueType> const & a,
	    Vector2D<ValueType> const & b)
{
  return a.angleTo(b);
}

template <typename ValueType>
inline
Vector2D<ValueType> midpoint(Vector2D<ValueType> const & a,
                             Vector2D<ValueType> const & b)
{
   return (0.5*(a + b));
}


} // namespace Units


#endif  // Units_Vector2D_i
