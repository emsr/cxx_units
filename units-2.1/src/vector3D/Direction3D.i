//
// $Id: Direction3D.i,v 1.3.4.3 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Direction3D class.
//

#ifndef Units_Direction3D_i
#define Units_Direction3D_i


namespace Units
{


template <typename ValueType>
inline
_Direction3D<ValueType>::_Direction3D()
{
}

template <typename ValueType>
inline
_Direction3D<ValueType>::_Direction3D(_Direction3D const & vec):
  _vector(vec._vector)
{
}

template <typename ValueType>
inline
_Direction3D<ValueType>::_Direction3D(Vector3D<ValueType> const & vec)
  throw (std::range_error)
{
  _construct(vec);
}

template <typename ValueType>
inline
_Direction3D<ValueType>::_Direction3D(ValueType const xx,
                                      ValueType const yy,
                                      ValueType const zz)
  throw (std::range_error)
{
  _construct(Vector3D<ValueType>(xx,
                                 yy,
                                 zz));
}


// Data access

template <typename ValueType>
inline
ValueType const & _Direction3D<ValueType>::x() const
{
  return _vector.x;
}

template <typename ValueType>
inline
ValueType const & _Direction3D<ValueType>::y() const
{
  return _vector.y;
}

template <typename ValueType>
inline
ValueType const & _Direction3D<ValueType>::z() const
{
  return _vector.z;
}

template <typename ValueType>
inline
Vector3D<ValueType> const & _Direction3D<ValueType>::vector() const
{
  return _vector;
}


template <typename ValueType>
inline
typename _Direction3D<ValueType>::_Angle
angle(_Direction3D<ValueType> const & a,
      _Direction3D<ValueType> const & b)
{
  return a.angleTo(b);
}


// Comparison functions

template <typename ValueType>
inline
bool _Direction3D<ValueType>::operator== (_Direction3D const & vec) const
{
  return (_vector == vec._vector);
}

template <typename ValueType>
inline
bool _Direction3D<ValueType>::operator!= (_Direction3D const & vec) const
{
  return (_vector != vec._vector);
}

template <typename ValueType>
inline
bool similar(_Direction3D<ValueType> const & a,
	     _Direction3D<ValueType> const & b,
	     typename _Direction3D<ValueType>::_Angle const & tol)
{
  typedef typename _Direction3D<ValueType>::_Angle _Angle;
  return similar(angle(a, b),
                 _Angle(zero()),
                 tol);
}


template <typename ValueType>
inline
ValueType _Direction3D<ValueType>::operator* (_Direction3D const & direction)
{
  return (_vector * direction._vector);
}

template <typename ValueType1,
          typename ValueType2>
inline
Vector3D<ValueType2> operator* (_Direction3D<ValueType1> const & direction,
                                ValueType2               const & magnitude)
{
  return (direction.vector() * magnitude);
}

template <typename ValueType1,
          typename ValueType2>
inline
Vector3D<ValueType2> operator* (ValueType2               const & magnitude,
                                _Direction3D<ValueType1> const & direction)
{
  return (direction * magnitude);
}

template <typename ValueType>
inline
_Direction3D<typename UnitlessType<ValueType>::Result>
direction(Vector3D<ValueType> const & vec)
{
  ValueType mag = vec.magnitude();
  return _Direction3D<typename UnitlessType<ValueType>::Result>(vec.x/mag,
                                                                vec.y/mag,
                                                                vec.z/mag);
}


template <typename ValueType>
inline
_Direction3D<ValueType> midpoint(_Direction3D<ValueType> const & a,
                                 _Direction3D<ValueType> const & b)
{
  return interpolate(a, b, ValueType(0.5));
}


template <typename ValueType>
inline
_Direction3D<ValueType> interpolate(_Direction3D<ValueType> const & a,
                                    _Direction3D<ValueType> const & b,
                                    ValueType               const   lambda)
  throw (std::range_error)
{
  return a.interpolateTo(b, lambda);
}


template <typename ValueType>
inline
std::ostream & operator<< (std::ostream                  & stream,
                           _Direction3D<ValueType> const & vec)
{
  return stream << vec.vector();
}

template<>
inline
dAngle _Direction3D<double>::defaultTolerance()
{
  return dRadiansAngle(1e-6);
}

template<>
inline
fAngle _Direction3D<float>::defaultTolerance()
{
  return fRadiansAngle(1e-3);
}


} // namespace Units


#endif  // Units_Direction3D_i
