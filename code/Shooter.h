/*
 * Shooter.h
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#include "ControllerConstants.h"
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

class Shooter {
	//motor controllers
	TalonSRX *leftShooter;
	TalonSRX *rightShooter;
	TalonSRX *leftLifter;
	TalonSRX *rightLifter;
	Encoder *shooterEncoder;
	DigitalInput *low1;
	DigitalInput *low2;
	DigitalInput *high1;
	DigitalInput *high2;

	double kDefaultEncoderPulseVal=1;
	double kTakeInSpeed=.4f;
	double kStopMotors= 0;
	double kLifterSpeedCap = .2;
	double kLifterSpeedMin =.075;
	double kAngleErrorMargin= 2.0;
	double kEncoderAngleVal= .3515625;
	double kAngleBallSpeed= .1;

public:
	Shooter();
	void shoot(float);
	void takeInBall();
	void stopMotors();
	void angleBall(float);
	float getAngle();
	bool setAngle(double);
	bool lowStop(bool, bool);
	bool highStop(bool, bool);

};



#endif /* SRC_SHOOTER_H_ */
