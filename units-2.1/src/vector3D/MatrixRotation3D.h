//
// $Id: MatrixRotation3D.h,v 1.2.4.3 2007-10-01 05:44:30 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Cosine matrix representation of a 3D rotation.
//
// Two methods are available: unit quaternion and cosine matrix.
// Both have their strong-points.  Both are non-degenerate at the
// poles; both have pretty much constant accuracy over the range
// of possible rotations.  Unit quaternions are easier to normalize.
// Unit quaternions have fewer computations for combining rotations
// than transforming vectors, but cosine matricies are better for
// applications which transform vectors more often.
//

#ifndef Units_MatrixRotation3D_h
#define Units_MatrixRotation3D_h

#include <iostream>
#include <stdexcept>


namespace Units
{


template<typename ValueType>
class _MatrixRotation3D
{
public:
  //
  // These help making generic functions that use _Direction2D<>.
  //
  typedef typename AngleTraits<ValueType>::BaseUnitType _Angle;
  typedef SignedAngleType<ValueType> _SignedAngle;
  typedef SpecificUnit<ValueType,
                       SpecificUnitTraits<DegreesAngleTraits,
                                          ValueType> > _DegreesAngle;

  //
  // Construct the identity rotation.
  //
  _MatrixRotation3D();

  _MatrixRotation3D(_MatrixRotation3D     const & rotation);

  _MatrixRotation3D(_Direction3D<ValueType>          const & axis_,
                    _Angle                           const & angle_);

  _MatrixRotation3D(_Direction3D<ValueType>          const & xAxis,
                    _Direction3D<ValueType>          const & yAxis,
                    _Direction3D<ValueType>          const & zAxis)
    throw (std::range_error);


  //
  // Be careful with these -- they only check for binary equivalence!
  //
  bool        operator== (_MatrixRotation3D const & rotation) const;
  bool        operator!= (_MatrixRotation3D const & rotation) const;


  // Data access

  //
  // NOTE: There are two sets of axis/angles that can represent a rotation:
  //       the angles and axes are opposites of each other.  You might not
  //       get back the identical axis/angle set that you used to construct.
  //

  _Direction3D<ValueType> axis() const;
  _Angle angle() const;

  _Direction3D<ValueType> xAxis () const;
  _Direction3D<ValueType> yAxis () const;
  _Direction3D<ValueType> zAxis () const;


  // Arithmetic operators

  //
  // Combine this with another rotation.
  //
  _MatrixRotation3D   operator* (_MatrixRotation3D const & rotation)  const;
  _MatrixRotation3D & operator*=(_MatrixRotation3D const & rotation);

  _MatrixRotation3D   inverse() const;
  _MatrixRotation3D<ValueType> & invert();
  _MatrixRotation3D<ValueType> & rotate(_Direction3D<ValueType> const & axis,
                                        _Angle                  const & angle);

  static
  _MatrixRotation3D const & identity();

  static
  _Angle defaultTolerance();


  ///
  /// Test the proper operation of the public API.  WARNING: This is
  /// for library testing only and not exported.
  ///
  static
  bool test();


private:
  //
  // The columns of the cosine matrix are three unit-length vectors
  // which point along the axes.
  //
  _Direction3D<ValueType> _xAxis;
  _Direction3D<ValueType> _yAxis;
  _Direction3D<ValueType> _zAxis;

  static
  _MatrixRotation3D const * _identity;
};


///
/// Transform unitless vector with this rotation.
///
template<typename ValueType,
         typename ValueType2>
Vector3D<ValueType2>
operator* (_MatrixRotation3D<ValueType> const & rotation,
           Vector3D<ValueType2>         const & vector);

///
/// Transform direction with this rotation.
///
template<typename ValueType>
_Direction3D<ValueType>
operator* (_MatrixRotation3D<ValueType> const & rotation,
           _Direction3D<ValueType>      const & direction);


///
/// Compute the shortest rotation between two quaternions.
///
template<typename ValueType>
_MatrixRotation3D<ValueType>
delta(_MatrixRotation3D<ValueType> const & from,
      _MatrixRotation3D<ValueType> const & to);

///
/// Compute the angle of the shortest rotation between two matrices.
///
template<typename ValueType>
typename _MatrixRotation3D<ValueType>::_Angle
error(_MatrixRotation3D<ValueType> const & from,
      _MatrixRotation3D<ValueType> const & to);

///
/// Check if the angle of shortest rotation between the matrices is
/// within a tolerance.
///
template<typename ValueType>
bool similar(_MatrixRotation3D<ValueType> const & a,
             _MatrixRotation3D<ValueType> const & b,
             typename _MatrixRotation3D<ValueType>::_Angle const & tol =
             _MatrixRotation3D<ValueType>::defaultTolerance());

template<typename ValueType>
_MatrixRotation3D<ValueType>
interpolate(_MatrixRotation3D<ValueType> const & a,
            _MatrixRotation3D<ValueType> const & b,
            ValueType                    const   lambda)
  throw (std::range_error);


typedef _MatrixRotation3D<double> dMatrixRotation3D;
typedef _MatrixRotation3D<float> fMatrixRotation3D;
typedef _MatrixRotation3D<UNITS_DEFAULT_VALUE_TYPE> MatrixRotation3D;


} // namespace Units


#include "MatrixRotation3D.i"

#ifdef UNITS_TEMPLATES_REQUIRE_SOURCE
#include "MatrixRotation3D.cpp"
#endif

#endif  // Units_MatrixRotation3D_h
