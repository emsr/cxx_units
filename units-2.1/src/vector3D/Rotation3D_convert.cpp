//
// $Id: Rotation3D_convert.cpp,v 1.1.2.2 2009-05-14 02:53:56 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Non-inline implementations for the QuaternionRotation3D class.
//

#ifndef Units_Rotation3D_convert_cpp
#define Units_Rotation3D_convert_cpp

#include <math.h>
#include "QuaternionRotation3D.h"
#include "MatrixRotation3D.h"


namespace Units
{


template<typename ValueType>
inline
int math_sign(ValueType const & a)
{
  return ((a < ValueType(0)) ? -1 : 1 );
}

//
// From:       Allan R. Klummp, Journal of Spacecraft, Vol. 13, No. 12, 
//             pp. 754-755, 1976. NOTE: This function assumes a 
//             normalized rotation matrix.
//
// 10 mults, 8 adds, 3 sqrts
template<typename ValueType>
_QuaternionRotation3D<ValueType>
convert(_MatrixRotation3D<ValueType> const & rotation)
{
  ValueType trace = (rotation.xAxis().x() +
                     rotation.yAxis().y() +
                     rotation.zAxis().z());

  ValueType temp1 = (1 + trace)*0.25;  // squared scalar component
  ValueType temp2 = (1 - trace)*0.25;  // used to compute vector components

  // Find scalar element of quaternion (Klummp, eqn 4).
  // Protect against sqrt of negatives.
  ValueType qs = (temp1 <= 0) ? 0 : ::sqrt(temp1);

  // Find the magnitudes of the quaternion vector elements (Klummp, eqn 6).

  ValueType           temp;  // squared component value
  Vector3D<ValueType> vmag;

  if ((temp = (rotation.xAxis().x()*0.5 + temp2)) <= 0)
    vmag.x = 0;
  else
    vmag.x = ::sqrt(temp);

  if ((temp = (rotation.yAxis().y()*0.5 + temp2)) <= 0)
    vmag.y = 0;
  else
    vmag.y = ::sqrt(temp);

  if ((temp = (rotation.zAxis().z()*0.5 + temp2)) <= 0)
    vmag.z = 0;
  else
    vmag.z = ::sqrt(temp);

  // Find element with the largest magnitude.
  ValueType maxMag   = vmag.x;
  int       maxIndex = 0;

  if (vmag.y > maxMag)
  {
    maxMag   = vmag.y;
    maxIndex = 1;
  }
  if (vmag.z > maxMag)
  {
    maxMag   = vmag.z;
    maxIndex = 2;
  }

  Vector3D<ValueType> qv(0, 0, 0);

  // Now find the signs of the q vector elements (Klummp, eqns 4, 6, 12-15).
  switch (maxIndex)
  {
  case 0:                                  // cycle: i = 0, j = 1, k = 2
    qv.x = math_sign(      rotation.yAxis().z() -
                           rotation.zAxis().y()) *vmag.x;

    qv.y = math_sign(qv.x*(rotation.xAxis().y() +
                           rotation.yAxis().x()))*vmag.y;

    qv.z = math_sign(qv.x*(rotation.xAxis().z() +
                           rotation.zAxis().x()))*vmag.z;
    break;

  case 1:                                  // cycle: i = 1, j = 2, k = 0
    qv.y = math_sign(      rotation.zAxis().x() -
                           rotation.xAxis().z()) *vmag.y;

    qv.z = math_sign(qv.y*(rotation.yAxis().z() +
                           rotation.zAxis().y()))*vmag.z;

    qv.x = math_sign(qv.y*(rotation.yAxis().x() +
                           rotation.xAxis().y()))*vmag.x;
    break;

  case 2:                                  // cycle: i = 2, j = 0, k = 1
    qv.z = math_sign(      rotation.xAxis().y() -
                           rotation.yAxis().x()) *vmag.z;

    qv.x = math_sign(qv.z*(rotation.zAxis().x() +
                           rotation.xAxis().z()))*vmag.x;

    qv.y = math_sign(qv.z*(rotation.zAxis().y() +
                           rotation.yAxis().z()))*vmag.y;
    break;
  }

  return _QuaternionRotation3D<ValueType>(qs,
                                          qv.x,
                                          qv.y,
                                          qv.z);
}

//
// From http://www.pst.stsci.edu/moss/rotations_req.html
//
// 27 mults, 12 adds
template<typename ValueType>
_MatrixRotation3D<ValueType>
convert(_QuaternionRotation3D<ValueType> const & quat)
{
  Vector3D<ValueType> xAxis;
  Vector3D<ValueType> yAxis;
  Vector3D<ValueType> zAxis;

  //
  // Don't use member initializers because they will do a normalization.
  // The vectors we generate here are already normalized.
  //
  xAxis.x = 1 - 2*(quat.qv().y*quat.qv().y + quat.qv().z*quat.qv().z);
  xAxis.y =     2*(quat.qv().x*quat.qv().y + quat.qv().z*quat.qs());
  xAxis.z =     2*(quat.qv().x*quat.qv().z - quat.qv().y*quat.qs());

  yAxis.x =     2*(quat.qv().y*quat.qv().x - quat.qv().z*quat.qs());
  yAxis.y = 1 - 2*(quat.qv().z*quat.qv().z + quat.qv().x*quat.qv().x);
  yAxis.z =     2*(quat.qv().y*quat.qv().z + quat.qv().x*quat.qs());

  zAxis.x =     2*(quat.qv().z*quat.qv().x + quat.qv().y*quat.qs());
  zAxis.y =     2*(quat.qv().z*quat.qv().y - quat.qv().x*quat.qs());
  zAxis.z = 1 - 2*(quat.qv().x*quat.qv().x + quat.qv().y*quat.qv().y);

  return _MatrixRotation3D<ValueType>(xAxis.direction(),
                                      yAxis.direction(),
                                      zAxis.direction());
}


} // namespace Units

#endif  // Units_Rotation3D_convert_cpp
