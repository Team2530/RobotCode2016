/*
 * DriveTrain.h
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#include "AHRS.h"
#include "Shooter.h"
#include "Camera.h"
#ifndef SRC_DRIVETRAIN_H_
#define SRC_DRIVETRAIN_H_

class DriveTrain {

	Victor *vic1;
	Victor *vic2;
	Victor *vic3;
	Victor *vic4;
	Relay *spike;
	Servo *servo;

	PIDController *turnController;
	Joystick *leftStick;
	Joystick *rightStick;
	Joystick *xBox;

	RobotDrive *myRobot;

	Encoder *leftEncoder;
	Encoder *rightEncoder;
	Shooter *shooter;
	Camera *camera;

	AHRS *ahrs;
	int step=1;

	double angleStart;
	double currentAngle;
	double startAngle;
	double stopAngle;
	double speed;
	double angleTheta;
	double constant;
	bool done;

	double kLeftDistancePerPulse= 1;// -1*3.14159*8/432;
	double kRightDistancePerPulse= 1;//3.14159*8/630;
	double kThrottleMinimum = .4;
	double kServoRest=130;
	double kServoShoot=0;
	double kshoot100=1;
	double kOppositeAngle =180;
	double kChangeInAngleConstant= 80;
	double kFullCircle= 360;
	double kAngleThetaConstant= 1.2;
	double kTurnSpeedCap=.4;
	double kTurnSpeedMin=.2;
	double kTriggerThreshold=.1;
	double kTurnRightFullDegrees= 1.0;
	double kNoAngle=0.0;
	double kNoPower=0.0;
	int kNoDistance=0;

public:
	DriveTrain();

	double getThrottle(double);
	void DriveSet(float, float);

	void AutonomousInit();
	void TeleopInit();
	void Drive();
	bool driveDistance(int,float);

	double getChangeTheta();
	bool turnRight(double);
	bool turnLeft(double);
	void setServo(float);
	void driveShoot(double);
	double getTargetD();
	double getTargetA();
	bool setAngle(double);
};

#endif /* SRC_DRIVETRAIN_H_ */
