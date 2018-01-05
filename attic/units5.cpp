//  ./bin/bin/g++ -std=c++0x -o units5 units5.cpp

#include <iostream>

#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>

using namespace boost::units;
using namespace boost::units::si;

namespace foo
{
quantity<length, long double>
operator"" _m(long double x)
{ return x * meters * 2.0L; }

quantity<si::time, long double>
operator"" _s(long double x)
{ return x * seconds * 0.5L; }
}

quantity<length, long double>
operator"" _m(long double x)
{ return x * meters; }

quantity<si::time, long double>
operator"" _s(long double x)
{ return x * seconds; }

int
main()
{
  //using namespace foo;
  auto l = 66.6_m;
  auto t = 33.3_s;
  auto v = 2.5_m / 6.6_s;
  std::cout << "l = " << l << '\n';
  std::cout << "t = " << t << '\n';
  std::cout << "v = " << v << '\n';
}
