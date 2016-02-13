/*
 * Shooter.cpp
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */

#include <Shooter.h>



Shooter::Shooter() {
	leftShooter= new TalonSRX(4);
	rightShooter= new TalonSRX(5);

	leftLifter= new TalonSRX(6);
	rightLifter= new TalonSRX(7);

}

void Shooter::shoot(){
	leftShooter->Set(1.0f);
	rightShooter->Set(1.0f);
}

void Shooter::takeInBall(){
	leftShooter->Set(-.7f);
	rightShooter->Set(-.7f);
}

void Shooter::stopMotors(){
	leftShooter->Set(0);
	rightShooter->Set(0);
}
void Shooter::angleBall(float lifterSpeed){
	leftLifter->Set(lifterSpeed);
	rightLifter->Set(lifterSpeed);
}
