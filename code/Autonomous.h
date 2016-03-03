/*
 * Autonomous.h
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"

#include "DriveTrain.h"
#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

class Autonomous {

	DriveTrain *robotd;
	int step;
	Timer *timer;
	bool isDone;
	std::string autoMode;

public:
	Autonomous(DriveTrain*, std::string);
	void doNothing();
	void startTimer();
	void driveOverDefense();
	void turnRight(double);
	bool attackTower(std::string);
	double getTime();
	bool nextStep(bool);
};


#endif /* AUTONOMOUS_H_ */
