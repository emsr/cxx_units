//  ./bin/bin/g++ -std=c++0x -o units4 units4.cpp

#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>

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
  auto l = 66.6_m;
  auto v = 2.5_m / 6.6_s;
  std::cout << "l = " << l << '\n';
  std::cout << "v = " << v << '\n';
}
