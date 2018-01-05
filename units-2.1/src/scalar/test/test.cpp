//
// $Id: test.cpp,v 1.7.2.4 2009-05-14 02:53:55 knicewar Exp $
//
// Copyright Keith Nicewarner.  All rights reserved.
//
// Test all the scalar library components.
//

#include <iostream>
#include <string>

#include "Unit.h"
#include "Time.h"
#include "Frequency.h"
#include "Mass.h"
#include "MassFlowRate.h"
#include "Length.h"
#include "Area.h"
#include "Volume.h"
#include "Speed.h"
#include "Acceleration.h"
#include "Force.h"
#include "Inertia.h"
#include "Angle.h"
#include "SignedAngle.h"
#include "UnsignedAngle.h"
#include "AngularSpeed.h"
#include "AngularAcceleration.h"
#include "Torque.h"
#include "Voltage.h"
#include "Current.h"
#include "Power.h"
#include "MagneticField.h"
#include "MagneticFluxDensity.h"
#include "MagneticFlux.h"
#include "Pressure.h"
#include "Density.h"
#include "Temperature.h"


using namespace Units;
using namespace std;


struct ClassTest
{
  string   className;
  bool   (*testFunc)();

  ClassTest(string   className_,
            bool   (*testFunc_)()):
    className(className_),
    testFunc(testFunc_)
  {}
};

bool Time_test();
bool Frequency_test();
bool Mass_test();
bool MassFlowRate_test();
bool Length_test();
bool Area_test();
bool Volume_test();
bool Speed_test();
bool Acceleration_test();
bool Force_test();
bool Inertia_test();
bool Angle_test();
bool SignedAngle_test();
bool UnsignedAngle_test();
bool AngularSpeed_test();
bool AngularAcceleration_test();
bool Torque_test();
bool Voltage_test();
bool Current_test();
bool Power_test();
bool MagneticField_test();
bool MagneticFluxDensity_test();
bool MagneticFlux_test();
bool Pressure_test();
bool Density_test();
bool Temperature_test();

ClassTest classTestList[] =
{
  ClassTest("Time",                &Time_test),
  ClassTest("Frequency",           &Frequency_test),
  ClassTest("Mass",                &Mass_test),
  ClassTest("MassFlowRate",        &MassFlowRate_test),
  ClassTest("Length",              &Length_test),
  ClassTest("Area",                &Area_test),
  ClassTest("Volume",              &Volume_test),
  ClassTest("Speed",               &Speed_test),
  ClassTest("Acceleration",        &Acceleration_test),
  ClassTest("Force",               &Force_test),
  ClassTest("Inertia",             &Inertia_test),
  ClassTest("Angle",               &Angle_test),
  ClassTest("SignedAngle",         &SignedAngle_test),
  ClassTest("UnsignedAngle",       &UnsignedAngle_test),
  ClassTest("AngularSpeed",        &AngularSpeed_test),
  ClassTest("AngularAcceleration", &AngularAcceleration_test),
  ClassTest("Torque",              &Torque_test),
  ClassTest("Voltage",             &Voltage_test),
  ClassTest("Current",             &Current_test),
  ClassTest("Power",               &Power_test),
  ClassTest("MagneticField",       &MagneticField_test),
  ClassTest("MagneticFluxDensity", &MagneticFluxDensity_test),
  ClassTest("MagneticFlux",        &MagneticFlux_test),
  ClassTest("Pressure",            &Pressure_test),
  ClassTest("Density",             &Density_test),
  ClassTest("Temperature",         &Temperature_test)
};



int main(int    argc,
         char * argv[])
{
  cout << endl;

  //
  // If no arguments were given, default to testing all classes.
  //
  if (argc == 1)
  {
    unsigned numFailed = 0;
    for (unsigned i = 0; i < sizeof(classTestList)/sizeof(ClassTest); i++)
    {
      bool status = (*classTestList[i].testFunc)();
      cout << classTestList[i].className << "::test() "
	   << (status ? "passed" : "failed") << '.' << endl;
      if (!status)
      {
	numFailed++;
      }
    }

    cout << "\n************************************\n" << endl;
    cout << "   " << numFailed << " classes failed.\n" << endl;

    return 0;
  }

  //
  // Loop through each argument and run its test from the class table.
  //
  for (int argument = 1; argument < argc; argument++)
  {
    for (unsigned i = 0; i < sizeof(classTestList)/sizeof(ClassTest); i++)
    {
      if (classTestList[i].className == argv[argument])
      {
	bool status = (*classTestList[i].testFunc)();
	cout << classTestList[i].className << "::test() "
	     << (status ? "passed" : "failed") << '.' << endl;
      }
    }
  }

  // Spot-check float types.
  fTime x = fSecondsTime(10);
  fTime y = x*2;

  return 0;
}
