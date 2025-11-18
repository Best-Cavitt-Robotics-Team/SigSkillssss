using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern motor bottomIntake;
extern motor topIntake;
extern motor leftFront;
extern motor leftMid;
extern motor leftBack;
extern motor rightFront;
extern motor rightMid;
extern motor rightBack;

extern rotation horizontalRotational;
extern rotation verticalRotational;

extern inertial Inertial;

extern pneumatics leftScraper;
extern pneumatics rightScraper;
extern pneumatics descore;
extern pneumatics middleGoal;

void  vexcodeInit( void );