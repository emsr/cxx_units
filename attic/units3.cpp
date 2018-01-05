//  ./bin/bin/g++ -std=c++0x -o units3 units3.cpp

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

quantity<energy>
work(const quantity<force> & F, const quantity<length> & dx)
{ return F * dx; }

quantity<length>
foo(double x)
{
  return x * meters;
}

quantity<length, long double>
operator"" _meters(long double x)
{
  return x * meters;
}

int
main()
{
  //auto v = 2.5m / 6.6s;
  quantity<length> L = 2.0 * meters;  //  quantity of length
}
