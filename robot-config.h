using namespace vex;

extern brain Brain;
extern controller Controller;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern motor IntakeBottom;
extern motor IntakeTop;
extern motor LeftFront;
extern motor LeftMiddle;
extern motor LeftBack;
extern motor RightFront;
extern motor RightMiddle;
extern motor RightBack;

extern rotation horizontalRotational;
extern rotation verticalRotational;

extern inertial Inertial;

extern pneumatics Scraper1;
extern pneumatics Scraper2;
extern pneumatics descore;
extern pneumatics middleGoal;

void  vexcodeInit( void );