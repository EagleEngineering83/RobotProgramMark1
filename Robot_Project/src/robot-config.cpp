#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftFrontDrive = motor(PORT19, ratio18_1, true);
motor LeftRearDrive = motor(PORT20, ratio18_1, false);
motor RightRearDrive = motor(PORT2, ratio18_1, true);
motor RightFrontDrive = motor(PORT1, ratio18_1, false);
motor IntakeLeft = motor(PORT3, ratio18_1, false);
motor IntakeRight = motor(PORT16, ratio18_1, true);
motor Tilt = motor(PORT11, ratio18_1, false);
motor Arm = motor(PORT17, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
