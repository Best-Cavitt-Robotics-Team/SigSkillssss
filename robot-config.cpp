#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen.
brain  Brain;

//The motor constructor takes motors as (port, ratio, reversed), so for example
//motor LeftFront = motor(PORT1, ratio6_1, false);

//Add your devices below, and don't forget to do the same in robot-config.h:

motor bottomIntake = motor(PORT1, ratio6_1, false);
motor topIntake = motor(PORT2, ratio6_1, false);

motor leftFront = motor(PORT5, ratio6_1, true);
motor leftMid = motor(PORT6, ratio6_1, false);
motor leftBack = motor(PORT7, ratio6_1, true);
motor rightFront = motor(PORT8, ratio6_1, false);
motor rightMid = motor(PORT9, ratio6_1, true);
motor rightBack = motor(PORT10, ratio6_1, false);

rotation horizontalRotational = rotation(PORT3, false);
rotation verticalRotational = rotation(PORT4, false);

inertial Intertial = inertial(PORT19);

pneumatics leftScraper = pneumatics(Brain.ThreeWirePort.H);
pneumatics rightScraper = pneumatics(Brain.ThreeWirePort.G);
pneumatics descore = pneumatics(Brain.ThreeWirePort.F);
pneumatics middleGoal = pneumatics(Brain.ThreeWirePort.E);

void vexcodeInit( void ) {
  // nothing to initialize
}