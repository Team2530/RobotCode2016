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
	SendableChooser *chooser;
	const std::string autoNamedN = "Do Nothing";
	const std::string autoNameLeft = "Left Low Goal";
	const std::string autoNameRight = "Right Low Goal";
	const std::string autoNameOver= "Drive Over Defense";
	std::string autoSelected;
	DriveTrain *robotd;
	int step;
	Timer *timer;
	bool isDone;

public:
	Autonomous(DriveTrain*);
	void doNothing();
	void startTimer();
	void driveOverDefense();
	void turnRight(double);
	bool attackTower(std::string);
	double getTime();
};


#endif /* AUTONOMOUS_H_ */
