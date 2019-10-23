using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftFrontDrive;
extern motor LeftRearDrive;
extern motor RightRearDrive;
extern motor RightFrontDrive;
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor Tilt;
extern motor Arm;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
