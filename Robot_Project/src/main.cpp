/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Code V1 for Clash in the Canyon               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftFrontDrive       motor         19              
// LeftRearDrive        motor         20              
// RightRearDrive       motor         2               
// RightFrontDrive      motor         1               
// IntakeLeft           motor         3               
// IntakeRight          motor         16              
// Tilt                 motor         11              
// Arm                  motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "math.h"
#include "vex.h"
#include "robot-config.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
int E_forward = 1;
int E_backward = -1;
int count = 0;

//Turn Left and Right using Time
void turnLeftRight(double time,double velocity,bool direction)
{ //left is true/right is false
    if (direction == true)
    {
        LeftFrontDrive.rotateFor(time,timeUnits::sec,-velocity,velocityUnits::pct);
        LeftRearDrive.rotateFor(time,timeUnits::sec,-velocity,velocityUnits::pct);
        RightFrontDrive.rotateFor(time,timeUnits::sec,velocity,velocityUnits::pct);
        RightRearDrive.rotateFor(time,timeUnits::sec,velocity,velocityUnits::pct);
    }
   else
   {
        LeftFrontDrive.rotateFor(time,timeUnits::sec,velocity,velocityUnits::pct);
        LeftRearDrive.rotateFor(time,timeUnits::sec,velocity,velocityUnits::pct);
        RightFrontDrive.rotateFor(time,timeUnits::sec,-velocity,velocityUnits::pct);
        RightRearDrive.rotateFor(time,timeUnits::sec,velocity,velocityUnits::pct); 
   }
} 

//Stop the Whole Base
void stopBase()
{
    
    RightFrontDrive.stop();
    LeftFrontDrive.stop();
    LeftRearDrive.stop();
    RightRearDrive.stop();  
    
}

//Moving with Encoders of SmartMotors:
void moveWithEncoder(double travelTargetCM, double velocity, int direction)
{
    double circ = 4 * 2.54 * M_PI;
    double dTR = (360 * travelTargetCM) / circ; //All calculations are complete. Start the rest of the program.
   
    //Set the velocity of the left and right motors to whatever power we want. This command will not make the motor spin.
    LeftFrontDrive.setVelocity(velocity * direction, vex::velocityUnits::pct); 
    LeftRearDrive.setVelocity(velocity * direction, vex::velocityUnits::pct);
    RightFrontDrive.setVelocity(velocity * direction, vex::velocityUnits::pct);
    RightRearDrive.setVelocity(velocity * direction, vex::velocityUnits::pct);
    
    
    //Rotate the Left and Right Motor for degreesToRotate. 
   LeftFrontDrive.rotateFor(dTR, vex::rotationUnits::deg, false); //This command must be non blocking.
   LeftRearDrive.rotateFor(dTR, vex::rotationUnits::deg, false); //This command is blocking so the program will wait here until the right motor is done.
   RightFrontDrive.rotateFor(dTR, vex::rotationUnits::deg, false);
   RightRearDrive.rotateFor(dTR, vex::rotationUnits::deg);
    //The motors will brake once they reach their destination.
}

void intake(int speed, int direction, int time)
{
  IntakeRight.rotateFor(time*direction,timeUnits::sec,speed,velocityUnits::pct);
  IntakeLeft.rotateFor(time*direction,timeUnits::sec,speed,velocityUnits::pct); 
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {  //This is the code for auton This is the code for auton This is the code for auton This is the code for auton This is the code for auton This is the code for auton This is the code for auton 
  task::sleep(1000);
  turnLeftRight(1, 75, false);
  turnLeftRight(1, 20, true);
  intake(75, E_forward, 1);
  moveWithEncoder(40, 75, E_forward); 
  turnLeftRight(1, 75, false);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  int rightspeed;
  int leftspeed;
  int intake_speed = 75;
  int tilt_speed = 25;
  int arm_speed = 100;
  while (true) {
    if (Controller1.Axis2.value() < 10 &&
        Controller1.Axis2.value() > -10) // deadzone
    {
      rightspeed = 0;
    } else {
      rightspeed = Controller1.Axis2.value();
    }
    if (Controller1.Axis3.value() < 10 &&
        Controller1.Axis3.value() > -10) // deadzone
    {
      leftspeed = 0;
    } else {
      leftspeed = Controller1.Axis3.value();
    }

    RightFrontDrive.spin(vex::directionType::fwd, rightspeed,
                         vex::velocityUnits::pct);
    RightRearDrive.spin(vex::directionType::fwd, rightspeed,
                        vex::velocityUnits::pct);
    LeftFrontDrive.spin(vex::directionType::fwd, leftspeed,
                        vex::velocityUnits::pct);
    LeftRearDrive.spin(vex::directionType::fwd, leftspeed,
                       vex::velocityUnits::pct);

    if (Controller1.ButtonR1.pressing()) {

      IntakeLeft.spin(vex::directionType::fwd, intake_speed,
                      vex::velocityUnits::pct);
      IntakeRight.spin(vex::directionType::fwd, intake_speed,
                       vex::velocityUnits::pct);

    } else if (Controller1.ButtonR2.pressing()) {

      IntakeLeft.spin(vex::directionType::rev, intake_speed,
                      vex::velocityUnits::pct);
      IntakeRight.spin(vex::directionType::rev, intake_speed,
                       vex::velocityUnits::pct);

    } else {

      IntakeLeft.stop();
      IntakeRight.stop();
    }

    if (Controller1.ButtonL1.pressing()) {

      Tilt.spin(vex::directionType::fwd, tilt_speed, vex::velocityUnits::pct);

    } else if (Controller1.ButtonL2.pressing()) {

      Tilt.spin(vex::directionType::rev, tilt_speed, vex::velocityUnits::pct);
    } else {

      Tilt.stop();
    }

    if (Controller1.ButtonUp.pressing()) {

      Arm.spin(vex::directionType::fwd, arm_speed, vex::velocityUnits::pct);

    } 
    else if (Controller1.ButtonDown.pressing())
    {

      Arm.spin(vex::directionType::rev, arm_speed, vex::velocityUnits::pct);
    } 
    else 
    {

      Arm.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
