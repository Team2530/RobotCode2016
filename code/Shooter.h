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

public:
	Shooter();
	void shoot();
	void takeInBall();
	void stopMotors();
	void angleBall(float);
	float getAngle();
	void setAngle(float);

};



#endif /* SRC_SHOOTER_H_ */
