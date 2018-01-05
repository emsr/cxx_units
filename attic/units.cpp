/*
$HOME/bin/bin/g++ -std=c++14 -o units units.cpp
*/

#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/energy.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/electric_potential.hpp>
#include <boost/units/systems/si/current.hpp>
#include <boost/units/systems/si/resistance.hpp>
#include <boost/units/systems/si/io.hpp>

using namespace boost::units;
using namespace boost::units::si;

quantity<length, long double>
operator"" _m(long double x)
{ return x * meters; }

quantity<si::time, long double>
operator"" _s(long double x)
{ return x * seconds; }

quantity<current, long double>
operator"" _A(long double x)
{ return quantity<current, long double>(x * ampere); }

quantity<absorbed_dose, long double>
operator"" _Gy(long double x)
{ return quantity<absorbed_dose, long double>(x * gray); }

quantity<activity, long double>
operator"" _Bq(long double x)
{ return quantity<activity, long double>(x * becquerel); }

quantity<capacitance, long double>
operator"" _F(long double x)
{ return quantity<capacitance, long double>(x * farad); }

quantity<catalytic_activity, long double>
operator"" _kat(long double x)
{ return quantity<catalytic_activity, long double>(x * katal); }

quantity<conductance, long double>
operator"" _S(long double x)
{ return quantity<conductance, long double>(x * siemen); }

quantity<dose_equivalent, long double>
operator"" _Sv(long double x)
{ return quantity<dose_equivalent, long double>(x * sievert); }

quantity<electric_charge, long double>
operator"" _C(long double x)
{ return quantity<electric_charge, long double>(x * coulomb); }

quantity<electric_potential, long double>
operator"" _V(long double x)
{ return quantity<electric_potential, long double>(x * volt); }

quantity<energy, long double>
operator"" _J(long double x)
{ return quantity<energy, long double>(x * joule); }

quantity<force, long double>
operator"" _N(long double x)
{ return quantity<force, long double>(x * newton); }

quantity<frequency, long double>
operator"" _Hz(long double x)
{ return quantity<frequency, long double>(x * hertz); }

quantity<illuminance, long double>
operator"" _lx(long double x)
{ return quantity<illuminance, long double>(x * lux); }

quantity<inductance, long double>
operator"" _H(long double x)
{ return quantity<inductance, long double>(x * henry); }

quantity<luminous_flux, long double>
operator"" _lm(long double x)
{ return quantity<luminous_flux, long double>(x * lumen); }

quantity<magnetic_flux, long double>
operator"" _Wb(long double x)
{ return quantity<magnetic_flux, long double>(x * weber); }

quantity<magnetic_flux_density, long double>
operator"" _T(long double x)
{ return quantity<magnetic_flux_density, long double>(x * tesla); }

quantity<power, long double>
operator"" _W(long double x)
{ return quantity<power, long double>(x * watt); }

quantity<pressure, long double>
operator"" _Pa(long double x)
{ return quantity<pressure, long double>(x * pascal); }

quantity<resistance, long double>
operator"" _Ohm(long double x)
{ return quantity<resistance, long double>(x * ohm); }
/*
quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }

quantity<, long double>
operator"" _(long double x)
{ return quantity<, long double>(x * ); }
*/
//constexpr quantity<length>
//operator"" m(long double x)
//{ return quantity<length>(x * meter); }


int
main()
{
  auto v = 2.5_m / 6.6_s;
  auto wtf = 18.4_J * 0.00003_s;
  auto dV = 3.0_V - 0.002_A * 1000.0_Ohm;
  std::cout << "v = " << v << '\n';
  std::cout << "wtf = " << wtf << '\n';
  std::cout << "dV = " << dV << '\n';
}
