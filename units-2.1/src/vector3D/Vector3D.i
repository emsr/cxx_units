//
// $Id3
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Vector3D class.
//

#ifndef Units_Vector3D_i
#define Units_Vector3D_i

#include <math.h>



namespace Units
{


template <typename ValueType>
inline
Vector3D<ValueType>::Vector3D()
{
}


template <typename ValueType>
template <typename ValueTypeX,
          typename ValueTypeY,
          typename ValueTypeZ>
inline
Vector3D<ValueType>::Vector3D(ValueTypeX const & x_,
                              ValueTypeY const & y_,
                              ValueTypeZ const & z_):
  x(x_),
  y(y_),
  z(z_)
{
}

template <typename ValueType>
template <typename ValueType2>
inline
Vector3D<ValueType>::Vector3D(Vector3D<ValueType2> const & vec):
  x(vec.x),
  y(vec.y),
  z(vec.z)
{
}


template <typename ValueType>
inline
bool Vector3D<ValueType>::similarTo(Vector3D<ValueType> const & b,
                                    ValueType           const & tol) const
{
  return similar(*this,
                 b,
                 tol);
}


template <typename ValueType>
inline
Vector3D<ValueType>
operator* (typename UnitlessType<ValueType>::Result const & scale,
           Vector3D<ValueType>                      const & vec)
{
  return (vec * scale);
}

template <UNITS_UNIT_TEMPLATE_DECL_ARGS2>
inline
Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS_MUL_RESULT> >
operator* (Unit<UNITS_UNIT_TEMPLATE_ARGS1>            const & lhs,
           Vector3D<Unit<UNITS_UNIT_TEMPLATE_ARGS2> > const & rhs)
{
  return (rhs * lhs);
}


template <typename ValueType>
inline
ValueType Vector3D<ValueType>::magnitude() const
{
  return sqrt(*this * *this);
}

template <>
inline
double Vector3D<double>::magnitude() const
{
  return ::sqrt(*this * *this);
}

template <>
inline
float Vector3D<float>::magnitude() const
{
  return ::sqrtf(*this * *this);
}

template <typename ValueType>
inline
ValueType magnitude(Vector3D<ValueType> const & vec)
{
   return vec.magnitude();
}


template <typename ValueType>
inline
ValueType
Vector3D<ValueType>::distanceTo(Vector3D<ValueType> const & vec)  const
{
   return Units::magnitude(vec - *this);
}

template <typename ValueType>
inline
ValueType distance(Vector3D<ValueType> const & a,
                   Vector3D<ValueType> const & b)
{
   return a.distanceTo(b);
}

template <typename ValueType>
inline
Angle angle(Vector3D<ValueType> const & a,
	    Vector3D<ValueType> const & b)
{
  return a.angleTo(b);
}

template <typename ValueType>
inline
Vector3D<ValueType> midpoint(Vector3D<ValueType> const & a,
                             Vector3D<ValueType> const & b)
{
   return (0.5*(a + b));
}


} // namespace Units


#endif  // Units_Vector3D_i
