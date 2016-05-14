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
	leftShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM7);
	rightShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM6);

	leftLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM4);
	rightLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM5);
	shooterEncoder= new Encoder(ControllerConstants::DIOPort::kDIO4, ControllerConstants::DIOPort::kDIO5); //check ports
	shooterEncoder->SetDistancePerPulse(kDefaultEncoderPulseVal);// take ticks from 90-0, div 90
	shooterEncoder->Reset();
	//check ports
	low1= new DigitalInput(ControllerConstants::DIOPort::kDIO6);
	low2= new DigitalInput(ControllerConstants::DIOPort::kDIO7);
	high1= new DigitalInput(ControllerConstants::DIOPort::kDIO8);
	high2= new DigitalInput(ControllerConstants::DIOPort::kDIO9);
	atTheTop = true;
}

//shoots boulder at specified speed
void Shooter::shoot(float speed){
	leftShooter->Set(-speed);
	rightShooter->Set(speed);
	SmartDashboard::PutNumber("shootspeed",speed);
}

//takes in  ball at 40% speed
void Shooter::takeInBall(){
	leftShooter->Set(kTakeInSpeed);
	rightShooter->Set(-kTakeInSpeed);
}

//stops shooter motors
void Shooter::stopMotors(){
	leftShooter->Set(kStopShooters);
	rightShooter->Set(kStopShooters);
}

//if limit switches are pressed, don't lift or lower towards those switches
//otherwise, lift/lower as needed
void Shooter::angleBall(float lifterSpeed){
	if (shooterEncoder->Get()<100){
		StopMotors=0;
	}
	else if (shooterEncoder->Get()<200){
		StopMotors=-.02;
	}
	else{
		StopMotors=-.06;
	}
	if (lowStop(low1->Get(),low2->Get()) && lifterSpeed>0){
		leftLifter->Set(0);
		rightLifter->Set(0);
	}
	else if (highStop(high1->Get(), high2->Get()) && lifterSpeed< 0){
		leftLifter->Set(0);
		rightLifter->Set(0);
		shooterEncoder->Reset();
		atTheTop = true;
	}
	else if ((lifterSpeed<kLifterSpeedMin && lifterSpeed>-kLifterSpeedMin)){
		leftLifter->Set(StopMotors);
		rightLifter->Set(StopMotors);
	}
	else if((lifterSpeed>kLifterSpeedCap)){
		leftLifter->Set(kLifterSpeedCap);
		rightLifter->Set(kLifterSpeedCap);
	}
	else if (lifterSpeed<-kLifterSpeedCap){
		leftLifter->Set(-kLifterSpeedCap);
		rightLifter->Set(-kLifterSpeedCap);
	}
	else{
		leftLifter->Set(lifterSpeed+StopMotors);
		rightLifter->Set(lifterSpeed+StopMotors);
		SmartDashboard::PutNumber("angle", shooterEncoder->GetDistance());
	}
	if (lifterSpeed > 0){
		atTheTop = false;
	}
		SmartDashboard::PutNumber("lifterpower", lifterSpeed);
	SmartDashboard::PutNumber("encoder angle", shooterEncoder->Get()*kEncoderAngleVal);
}

void Shooter::stayAtTheTop(){

	if (highStop(high1->Get(), high2->Get()) && atTheTop) {
		leftLifter->Set(0);
		rightLifter->Set(0);


	}
	else if (highStop(high1->Get(), high2->Get()) ==false && atTheTop){
		leftLifter->Set(-kLifterSpeedCap);
		rightLifter->Set(-kLifterSpeedCap);
	}
}

bool Shooter::setAngle(double angle){
	double angleDiff=angle- shooterEncoder->Get()*kEncoderAngleVal;
	if (angleDiff<0){
		angleDiff*=-1;
	}
	if ((kAngleErrorMargin>= angleDiff)){
		angleBall(StopMotors);
		return true;
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal>angle){
		angleBall(-kAngleBallSpeed);
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal<angle){
		angleBall(kAngleBallSpeed);
	}
	else{
		angleBall(StopMotors);
		return true;
	}
	return false;
}


//if the low or high motors are pressed, return true so that the lifter doesn't move towards them.
bool Shooter::lowStop(bool l1, bool l2){
	if (l1&&l2){
		return false;
	}
	else{
		return true;
	}
}
bool Shooter::highStop(bool h1, bool h2){
	if (h1&&h2){
		return false;
	}
	else{
		return true;
	}
}

//resets the encoder for reading the lifter angle
void Shooter::resetEncoder(){
	shooterEncoder->Reset();
}
