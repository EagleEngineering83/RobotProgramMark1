#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
 #define leftRearDrive_PORT 20
 #define leftFrontDrive_PORT 19
 #define rightRearDrive_PORT 2
 #define rightFrontDrive_PORT 1
 #define intakeLeft_PORT 3
 #define intakeRight_PORT 16
 #define tilt_PORT 11
 #define arm_PORT 17
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Motor leftFrontDrive (leftFrontDrive_PORT);
  pros::Motor leftRearDrive (leftRearDrive_PORT);
	pros::Motor rightFrontDrive (rightFrontDrive_PORT,true);
	pros::Motor rightRearDrive (rightRearDrive_PORT,true);


  void usercontrol(void) {
    // User control code here, inside the loop
    int rightspeed;
    int leftspeed;
    int intake_speed = 75;
    int tilt_speed = 25;
    int arm_speed = 100;
    while (true) {
      if (E_CONTROLLER_MASTER.Axis2.value() < 10 &&
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

      vex::task::sleep(20); // Sleep the task for a short amount of time to
                      // prevent wasted resources.
    }
  }

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}
