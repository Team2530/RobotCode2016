/*
 * Autonomous.h
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#include "ControllerConstants.h"
#include "DriveTrain.h"
#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

class Autonomous {

	DriveTrain *robotd;
	int step;
	Timer *timer;
	bool isDone;
	std::string autoMode;
	double xangle;
	double imageDistance;
	double kAutoSpeed=.85;
	double kLowGoalAngle= 60;
	double kServoShootAngle=130;
	double kAutoShootSpeed=.8;
	double kModesEqual=0;
	int kDistanceAwayFromTarget=60;

public:
	Autonomous(DriveTrain*, std::string);
	void doNothing();
	void startTimer();
	void driveOverDefense();
	void turnRight(double);
	bool attackTower(std::string);
	double getTime();
	bool nextStep(bool);
	void test();
	void reset();
	void setSelected(std::string);
};


#endif /* AUTONOMOUS_H_ */
