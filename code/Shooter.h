/*
 * Shooter.h
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
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

public:
	Shooter();
	void shoot(float);
	void takeInBall();
	void stopMotors();
	void angleBall(float);
	float getAngle();
	void setAngle(float);
	bool lowStop(bool, bool);
	bool highStop(bool, bool);

};



#endif /* SRC_SHOOTER_H_ */
