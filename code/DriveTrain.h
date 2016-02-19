/*
 * DriveTrain.h
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#include "AHRS.h"
#include "Shooter.h"
#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

class DriveTrain {

	VictorSP *vic1;
	VictorSP *vic2;
	VictorSP *vic3;
	VictorSP *vic4;

	PIDController *turnController;
	Joystick *leftStick;
	Joystick *rightStick;
	Joystick *xBox;

	RobotDrive *myRobot;

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Shooter *shooter;

	AHRS *ahrs;
	int step;
	double angleStart;
	double currentAngle;
	double startAngle;
	double stopAngle;
	double speed;
	double angleTheta;

public:
	DriveTrain();

	double getThrottle(double);
	void DriveSet(float, float);

	void AutonomousInit();
	void TeleopInit();
	void Drive();
	void driveDistance(int,float);

	double getChangeTheta();
	void turnRight(double);
	PIDController* getController(PIDOutput*);
};

#endif /* SRC_DRIVETRAIN_H_ */
