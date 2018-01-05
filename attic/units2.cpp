/*
$HOME/bin/bin/g++ -std=c++14 -o units2 units2.cpp
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

int
main()
{
  auto v = 2.5m;
}
