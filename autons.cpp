#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.set_heading_constants(4, .4, 0, 1, 0);
  chassis.set_turn_constants(6, .4, .03, 3, 15);
  chassis.set_swing_constants(6, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 2000);
  chassis.set_turn_exit_conditions(1, 300, 1000);
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


/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */



/**
 * Should swing in a fun S shape.
 */



/**
 * A little of this, a little of that; it should end roughly where it started.
 */



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
 * prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void display_screen(){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    Brain.Screen.printAt(5,120, "Avg Distance: %f", (chassis.get_left_position_in()+chassis.get_right_position_in())/2.0);
    Brain.Screen.printAt(5,140, "Left Deg: %f  :: Right Deg: %f", chassis.DriveL.position(deg),chassis.DriveR.position(deg));

    //Brain.Screen.printAt(5,140, "Y: %f", chassis.get_Y_position());
   
    task::sleep(500);
  
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */



/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */




void skills(){
  
  display_screen();
  IntakeBottom.setVelocity(100, percent);  
  IntakeTop.setVelocity(100, percent);

  chassis.drive_distance(33);
  wait(100, msec);
  chassis.turn_to_angle(90);
  Scraper1.set(true);
  Scraper2.set(true);
  chassis.drive_max_voltage = 4;
  IntakeBottom.spin(reverse);
  wait(100, msec);
  chassis.drive_distance(12);
  wait(2, sec);
//get blocks from the first loader

  chassis.drive_max_voltage = 10;
  chassis.drive_distance(-5);
  Scraper1.set(false);
  Scraper2.set(false);
  chassis.drive_distance(2);
  chassis.drive_distance(-2);
  IntakeBottom.stop();
  chassis.turn_to_angle(-45);
  chassis.drive_distance(24);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(68);
  //go through the first ally

  chassis.right_swing_to_angle(-45);
  chassis.drive_distance(-13);
  chassis.turn_to_angle(-90);
  IntakeBottom.spin(reverse);
  IntakeTop.spin(reverse);
  chassis.drive_distance(-5);
  //align with the goal


  wait(2.5, sec);
  //score blocks

  IntakeTop.stop(); 
  Scraper1.set(true);
  Scraper2.set(true);
  chassis.drive_max_voltage = 4;
  chassis.drive_distance(28.5);
  wait(3,sec);
  //collect blocks from the second loader

  chassis.drive_distance(-29.25);
  IntakeTop.spin(reverse);
  wait(4, sec);
  //score blocks from second loader

  Scraper1.set(false);
  Scraper2.set(false);
  chassis.drive_max_voltage = 8;
  IntakeBottom.stop();
  IntakeTop.stop();
  chassis.drive_distance(15);
  chassis.turn_to_angle(180);
  chassis.drive_distance(96);
  chassis.turn_to_angle(-87);
  //go across the field and line up with the third loader

  Scraper1.set(true);
  Scraper2.set(true);
  chassis.drive_max_voltage = 4;
  IntakeBottom.spin(reverse);
  chassis.drive_distance(18.5);
  wait(3, sec);
  //colect blocks from the third loader

  chassis.drive_max_voltage = 10;
  chassis.drive_distance(-5);
  Scraper1.set(false);
  Scraper2.set(false);
  chassis.drive_distance(1);
  chassis.drive_distance(-1);
  IntakeBottom.stop();
  chassis.turn_to_angle(-225);
  chassis.drive_distance(24);
  chassis.right_swing_to_angle(94);
  
  chassis.drive_distance(68);
  
  //go in the second ally

  chassis.right_swing_to_angle(-225);
  chassis.drive_distance(-14);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-5);
  //align with the goal

  IntakeBottom.spin(reverse);
  IntakeTop.spin(reverse);
  wait(3, sec);
  IntakeTop.stop();
  //score in the goal

  chassis.drive_max_voltage = 4;
  Scraper1.set(true);
  Scraper2.set(true);
  chassis.drive_distance(29.25);
  wait(3,sec);
  //get blocks from the fourth loader

  chassis.drive_distance(-29.25);
  chassis.drive_distance(5);
  wait(500, msec);
  chassis.drive_distance(-5);
  IntakeTop.spin(reverse);
  wait(3, sec);
  //score blocks from the fourth loader
  
  chassis.drive_distance(20 );
  chassis.turn_to_angle(45);
  chassis.drive_distance(30);
  chassis.right_swing_to_angle(0);
  chassis.drive_distance(30);
  Scraper1.set(false);
  Scraper2.set(false);



  //LeftBack.setVelocity(200, rpm);



  // wait(1000,msec);
  // IntakeTop.setVelocity(100, percent);
  // IntakeBottom.setVelocity(100, percent);
  // Scraper1.set(false);
  // Scraper2.set(false);
  // chassis.drive_distance(32);
  
  // chassis.turn_to_angle(90);
  // Scraper1.set(true);
  // Scraper2.set(true);
  // IntakeBottom.spin(reverse);

  // chassis.drive_distance(12.5);
  // wait(1750,msec);
  // IntakeBottom.spin(forward);
  // wait(200, msec);
  // IntakeBottom.spin(reverse);
  // chassis.drive_distance(-14);
  // chassis.drive_distance(4);
  // chassis.drive_distance(-20);
  // IntakeTop.spin(reverse);
  // wait(250,msec);
  // IntakeBottom.spin(forward);
  // IntakeBottom.spin(forward);
  // wait(250,msec);
  // IntakeBottom.spin(reverse);
  // IntakeTop.spin(reverse);
  // wait(5000,msec);
  // IntakeBottom.stop();
  // IntakeTop.stop();
  // chassis.drive_distance(10);
  // chassis.turn_to_angle(0);
  // chassis.drive_distance(-48);
  
  // chassis.drive_distance(-48);
  
  // chassis.drive_distance(-24);
  
  // chassis.drive_distance(15);
  // Scraper1.set(false);
  // Scraper2.set(false);
  // chassis.turn_to_angle(90);
  // Scraper1.set(true);
  // Scraper2.set(true);
  // IntakeBottom.spin(reverse);
  // wait(150,msec);
  // chassis.drive_distance(19);
  // wait(2500, msec);
  // IntakeBottom.spin(forward);
  // wait(500, msec);
  // IntakeBottom.spin(reverse);
  // wait(2500, msec);
  // chassis.drive_distance(-14);
  // chassis.drive_distance(4);
  // chassis.turn_to_angle(89);
  // chassis.drive_distance(-20);
  // IntakeTop.spin(reverse);
  // wait(250,msec);
  // IntakeBottom.spin(forward);
  // IntakeTop.spin(forward);
  // wait(250,msec);
  // IntakeBottom.spin(reverse);
  // IntakeTop.spin(reverse);
  // wait(5000,msec);
  // Scraper1.set(false);
  // Scraper2.set(false);
  // chassis.drive_distance(10);
  // chassis.turn_to_angle(45);
  // chassis.drive_distance(27);
  // chassis.drive_distance(-0.5);
  // chassis.right_swing_to_angle(5);
  // chassis.drive_max_voltage = 12;
  // Scraper1.set(true);
  // Scraper2.set(true);
  // chassis.drive_distance(45);



  
  // IntakeBottom.spin(reverse);
  // IntakeTop.spin(reverse);
  // wait(2500,msec);.spin(reverse)
  // IntakeBottom.stop();
  // IntakeTop.stop();
  // chassis.drive_to_pose(120,30,90);
  // chassis.turn_to_angle(180);
  // chassis.drive_to_pose(24,30,180);
  // chassis.turn_to_angle(90);
  // Scraper1.set(true);
  // Scraper2.set(true);
  // chassis.drive_to_pose(24,9,90);
  // IntakeBottom.spin(reverse);
  // wait(2500,msec);
  // IntakeBottom.stop();
  // chassis.drive_to_pose(24,24,90);
  // Scraper1.set(false);
  // Scraper2.set(false);
  // chassis.drive_to_pose(24,40,90);
  // IntakeBottom.spin(reverse);
  // IntakeTop.spin(reverse);
  // wait(2500,msec);
  // IntakeBottom.stop();
  // IntakeTop.stop();
  // chassis.drive_to_pose(24,24,90);
  // chassis.turn_to_angle(45);
  // chassis.drive_to_pose(46,2,45);
  // chassis.right_swing_to_angle(0);
  // Scraper1.set(true);
  // Scraper2.set(true);
  // chassis.drive_to_pose(70,2,0);
  // Scraper1.set(false);
  // Scraper2.set(false);

  

  //chassis.drive_to_pose(120,24,0);
  //display_screen();
  //wait(200000,msec);
  //chassis.turn_to_angle(90);
  //Scraper1.set(true);
  //Scraper2.set(true);
  //chassis.drive_to_pose(120,9,90);
  //IntakeBottom.spin(reverse);
  //wait(2500,msec);
  //IntakeBottom.stop();
  //chassis.drive_to_pose(120,24,90);
}