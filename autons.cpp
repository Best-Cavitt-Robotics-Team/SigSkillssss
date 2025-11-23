#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI). //6,3,0,25,0
  chassis.set_drive_constants(6, 1, 1, 12, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0); //6,.4,0,1,0
  chassis.set_turn_constants(12, .4, 0, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 3500);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

void auton1(){
  odom_constants();
  chassis.set_coordinates(0, 0, 90);
  // drive to matchloader, tturn, put scraper down, run intake
  chassis.drive_to_pose(33,0,90);
  wait(1000, msec);
  chassis.turn_to_angle(180);
  leftScraper.set(true);
  rightScraper.set(true);
  wait(1000, msec);
  bottomIntake.spin(reverse, 100, percent);

  //drive into matchloader, wait, drive back, outake to combat jamming
  chassis.drive_to_pose(32,-14,180);
  wait(500, msec);
  chassis.drive_to_pose(31,-8,180);
  wait(200, msec);
  chassis.drive_to_pose(31,-16,180);
  wait(500, msec);
  chassis.drive_to_pose(31,-2,180);
  bottomIntake.spin(forward, 100, percent);
  wait(500, msec);
  bottomIntake.stop();

  //spin intake, drive back to long goal, spin top intake, wait while scoring
  bottomIntake.spin(reverse, 100, percent);
  chassis.drive_to_pose(32,19,180);
  topIntake.spin(reverse, 100, percent);
  wait(2300, msec);

  //stop intakes, put up scraper, move forward, and turn towards other side of field
  bottomIntake.stop();
  topIntake.stop();
  leftScraper.set(false);
  rightScraper.set(false);
  chassis.drive_to_point(33,8);
  wait(1000, msec);
  chassis.turn_to_angle(-90);
  wait(1000, msec);

  //drive to wall 
  // chassis.drive_to_pose(-17,8,-90);
  // wait(1000, msec);
  chassis.drive_to_pose(-82, 8, -90);
  wait(1000, msec);

  // //reset coordinates
  // chassis.set_coordinates(0,0,-90);
  // wait(1000, msec);

  //back up to matchloader, turn to matchloader, set scraper down, spin intake
  chassis.drive_to_pose(-68,8,-90);
  wait(500, msec);
  chassis.turn_to_angle(180);
  leftScraper.set(true);
  rightScraper.set(true);
  bottomIntake.spin(reverse, 100, percent);

  // drive into matchloader
  chassis.drive_to_pose(-68,-14, 180);
  wait(500, msec);
  chassis.drive_to_pose(-68,-10, 180);
  wait(200,msec);
  chassis.drive_to_pose(-68,-16, 180);
  wait(500, msec);

  //drive to long goal, spin top intake, wait to score blocks
  chassis.drive_to_pose(-68,19,180);
  topIntake.spin(reverse, 100, percent);
  wait(2000, msec);

  //stop intakes, drive toward wall, turn, drive towards wall, turn to align with park zone
  topIntake.stop();
  bottomIntake.stop();
  chassis.drive_to_pose(-68,12,180);
  wait(500,msec);
  rightScraper.set(false);
  leftScraper.set(false);
  chassis.turn_to_angle(135);
  wait(500,msec);
  chassis.drive_to_pose(-50,-14,135);
  wait(500,msec);
  chassis.turn_to_angle(90);
  wait(500,msec);
  chassis.drive_to_pose(-40,-15,90);
  wait(500,msec);

  // put scraper down, drive through park zone
  rightScraper.set(true);
  leftScraper.set(true);
  chassis.drive_to_pose(-10,-11,90);
  rightScraper.set(false);
  leftScraper.set(false);


  //To be coded
  // chassis.drive_to_point(-66.5,0);
  // wait(1500, msec);
  // chassis.drive_to_point(-66.5,-3);
  // wait(1500, msec);
  // chassis.drive_to_point(-66.5,16);
  // wait(1500, msec);
  // topIntake.spin(reverse, 100, percent);
  // wait(5000, msec);
  // bottomIntake.spin(reverse, 0, percent);
  // topIntake.spin(reverse, 0, percent);
  // leftScraper.set(false);
  // rightScraper.set(false);
  // chassis.drive_to_pose(-66.5,7,180);
  // chassis.turn_to_angle(135);
  // chassis.drive_to_pose(-48,-11,135);
  // chassis.turn_to_angle(90);
  // chassis.drive_to_pose(0,-11,90);
  

  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    Brain.Screen.printAt(5,120, "Hello");
    task::sleep(20);
  }

  
}

void auton2(){
  chassis.set_coordinates(0, 0, 90);
  chassis.drive_to_pose(24,0,90);
}