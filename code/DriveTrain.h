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

	VictorSP *vic1;
	VictorSP *vic2;
	VictorSP *vic3;
	VictorSP *vic4;
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
	bool leftTurn=true;

	double kLeftDistancePerPulse= -1*3.14159*8/432;
	double kRightDistancePerPulse= 3.14159*8/630;
	double kThrottleMinimum = .4;
	double kServoRest=130;
	double kServoShoot=0;
	double kshoot100=1;
	double kOppositeAngle =180;
	double kChangeInAngleConstant= 80;
	double kFullCircle= 360;
	double kAngleThetaConstant= 1.2;
	double kTurnSpeedCap=.3;
	double kTurnSpeedMin=.18;
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
	bool turnRight(double);  // input is angle in degrees.
	bool turnLeft(double);
	void setServo(float);
	void driveShoot(double);
	double getTargetD();
	double getTargetA();
	bool setAngle(double);
	void stayAtTheTop();
};

#endif /* SRC_DRIVETRAIN_H_ */
