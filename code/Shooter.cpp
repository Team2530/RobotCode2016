/*
 * Shooter.cpp
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */

#include <Shooter.h>


//instantiates shooter motors, lifer motors, limit switches, and
Shooter::Shooter() {
	//check ports
	leftShooter= new TalonSRX(6);
	rightShooter= new TalonSRX(7);

	leftLifter= new TalonSRX(4);
	rightLifter= new TalonSRX(5);
	shooterEncoder= new Encoder(4,5); //check ports
	shooterEncoder->SetDistancePerPulse(1);// take ticks from 90-0, div 90

	//check ports
	low1= new DigitalInput(8);
	low2= new DigitalInput(9);
	high1= new DigitalInput(6);
	high2= new DigitalInput(7);

}

//shoots boulder at specified speed
void Shooter::shoot(float speed){
	leftShooter->Set(speed);
	rightShooter->Set(-speed);
}

//takes in  ball at 40% speed
void Shooter::takeInBall(){
	leftShooter->Set(-.4f);
	rightShooter->Set(.4f);
}

//stops shooter motors
void Shooter::stopMotors(){
	leftShooter->Set(0);
	rightShooter->Set(0);
}

//if limit switches are pressed, don't lift or lower towards those switches
//otherwise, lift/lower as needed
void Shooter::angleBall(float lifterSpeed){
	if (lowStop(low1->Get(),low2->Get()) && lifterSpeed>0){
		leftLifter->Set(0);
		rightLifter->Set(0);
	}
	else if (highStop(high1->Get(), high2->Get()) && lifterSpeed<0){
		leftLifter->Set(0);
		rightLifter->Set(0);
	}
	else{
	leftLifter->Set(lifterSpeed);
	rightLifter->Set(lifterSpeed);
	SmartDashboard::PutNumber("angle", shooterEncoder->GetDistance());
	}
	SmartDashboard::PutNumber("lifterpower", lifterSpeed);
}


void Shooter::setAngle(float angle){
	if (shooterEncoder->GetDistance()<angle){
		angleBall(.6); //check power
	}
	else{
		angleBall(0);
	}
}
bool Shooter::lowStop(bool l1, bool l2){
	if (l1||l2){
		return false;
	}
	else{
		return true;
	}
}
bool Shooter::highStop(bool h1, bool h2){
	if (h1||h2){
		return false;
	}
	else{
		return true;
	}
}
