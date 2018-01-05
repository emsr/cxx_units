//
// $Id: Direction2D.i,v 1.3.4.5 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Inline implementations for the Direction2D class.
//

#ifndef Units_Direction2D_i
#define Units_Direction2D_i


namespace Units
{


template <typename ValueType>
inline
_Direction2D<ValueType>::_Direction2D()
{
}

template <typename ValueType>
inline
_Direction2D<ValueType>::_Direction2D(_Direction2D const & vec):
  _vector(vec._vector)
{
}

template <typename ValueType>
inline
_Direction2D<ValueType>::_Direction2D(Vector2D<ValueType> const & vec)
  throw (std::range_error)
{
  _construct(vec);
}

template <typename ValueType>
inline
_Direction2D<ValueType>::_Direction2D(ValueType const xx,
                                      ValueType const yy)
  throw (std::range_error)
{
  _construct(Vector2D<ValueType>(xx,
                                 yy));
}


// Data access

template <typename ValueType>
inline
ValueType const & _Direction2D<ValueType>::x() const
{
  return _vector.x;
}

template <typename ValueType>
inline
ValueType const & _Direction2D<ValueType>::y() const
{
  return _vector.y;
}

template <typename ValueType>
inline
Vector2D<ValueType> const & _Direction2D<ValueType>::vector() const
{
  return _vector;
}


template <typename ValueType>
inline
typename _Direction2D<ValueType>::_Angle
angle(_Direction2D<ValueType> const & a,
      _Direction2D<ValueType> const & b)
{
  return a.angleTo(b);
}


// Comparison functions

template <typename ValueType>
inline
bool _Direction2D<ValueType>::operator== (_Direction2D const & vec) const
{
  return (_vector == vec._vector);
}

template <typename ValueType>
inline
bool _Direction2D<ValueType>::operator!= (_Direction2D const & vec) const
{
  return (_vector != vec._vector);
}

template <typename ValueType>
inline
bool similar(_Direction2D<ValueType> const & a,
	     _Direction2D<ValueType> const & b,
	     typename _Direction2D<ValueType>::_Angle const & tol)
{
  typedef typename _Direction2D<ValueType>::_Angle _Angle;
  return similar(angle(a, b),
                 _Angle(zero()),
                 tol);
}


template <typename ValueType>
inline
ValueType _Direction2D<ValueType>::operator* (_Direction2D const & direction)
{
  return (_vector * direction._vector);
}

template <typename ValueType1,
          typename ValueType2>
inline
Vector2D<ValueType2> operator* (_Direction2D<ValueType1> const & direction,
                                ValueType2               const & magnitude)
{
  return (direction.vector() * magnitude);
}

template <typename ValueType1,
          typename ValueType2>
inline
Vector2D<ValueType2> operator* (ValueType2               const & magnitude,
                                _Direction2D<ValueType1> const & direction)
{
  return (direction * magnitude);
}

template <typename ValueType>
inline
_Direction2D<typename UnitlessType<ValueType>::Result>
direction(Vector2D<ValueType> const & vec)
{
  ValueType mag = vec.magnitude();
  return _Direction2D<typename UnitlessType<ValueType>::Result>(vec.x/mag,
                                                                vec.y/mag);
}


template <typename ValueType>
inline
ValueType _Direction2D<ValueType>::operator% (_Direction2D const & vec) const
{
  return (_vector % vec._vector);
}


template <typename ValueType>
inline
_Direction2D<ValueType> midpoint(_Direction2D<ValueType> const & a,
                                 _Direction2D<ValueType> const & b)
{
  return interpolate(a, b, ValueType(0.5));
}


template <typename ValueType>
inline
_Direction2D<ValueType> interpolate(_Direction2D<ValueType> const & a,
                                    _Direction2D<ValueType> const & b,
                                    ValueType               const   lambda)
  throw (std::range_error)
{
  return a.interpolateTo(b, lambda);
}


template <typename ValueType>
inline
std::ostream & operator<< (std::ostream                  & stream,
                           _Direction2D<ValueType> const & vec)
{
  return stream << vec.vector();
}

template<>
inline
dAngle _Direction2D<double>::defaultTolerance()
{
  return dRadiansAngle(1e-6);
}

template<>
inline
fAngle _Direction2D<float>::defaultTolerance()
{
  return fRadiansAngle(1e-3);
}


} // namespace Units


#endif  // Units_Direction2D_i
