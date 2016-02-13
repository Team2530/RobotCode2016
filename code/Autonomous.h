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
	const std::string dN = "DN";
	const std::string position1 = "P1";
	const std::string position2 = "P2";
	const std::string position3 = "P3";
	const std::string position4 = "P4";
	const std::string position5 = "P5";
	DriveTrain *robotd;
	std::string autoSelected;
	Timer *timer;

public:
	Autonomous(DriveTrain*);
	void doNothing();
	void startTimer();
	void driveOverDefense();
	bool attackTower(std::string);
};


#endif /* AUTONOMOUS_H_ */
