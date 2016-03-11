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
	leftShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM4);
	rightShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM5);

	leftLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM6);
	rightLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM7);
	shooterEncoder= new Encoder(ControllerConstants::DIOPort::kDIO3, ControllerConstants::DIOPort::kDIO4); //check ports
	shooterEncoder->SetDistancePerPulse(kDefaultEncoderPulseVal);// take ticks from 90-0, div 90

	//check ports
	low1= new DigitalInput(ControllerConstants::PWMPort::kPWM8);
	low2= new DigitalInput(ControllerConstants::PWMPort::kPWM9);
	high1= new DigitalInput(ControllerConstants::PWMPort::kPWM6);
	high2= new DigitalInput(ControllerConstants::PWMPort::kPWM7);

}

//shoots boulder at specified speed
void Shooter::shoot(float speed){
	leftShooter->Set(speed);
	rightShooter->Set(-speed);
	SmartDashboard::PutNumber("shootspeed",speed);
}

//takes in  ball at 40% speed
void Shooter::takeInBall(){
	leftShooter->Set(-kTakeInSpeed);
	rightShooter->Set(kTakeInSpeed);
}

//stops shooter motors
void Shooter::stopMotors(){
	leftShooter->Set(kStopMotors);
	rightShooter->Set(kStopMotors);
}

//if limit switches are pressed, don't lift or lower towards those switches
//otherwise, lift/lower as needed
void Shooter::angleBall(float lifterSpeed){
	if (lowStop(low1->Get(),low2->Get()) && lifterSpeed>kStopMotors){
		leftLifter->Set(kStopMotors);
		rightLifter->Set(kStopMotors);
	}
	else if (highStop(high1->Get(), high2->Get()) && lifterSpeed< kStopMotors){
		leftLifter->Set(kStopMotors);
		rightLifter->Set(kStopMotors);
	}
	else if ((lifterSpeed<kLifterSpeedMin && lifterSpeed>-kLifterSpeedMin) || (lifterSpeed>kLifterSpeedCap) || (lifterSpeed<-kLifterSpeedCap)){
		leftLifter->Set(kStopMotors);
		rightLifter->Set(kStopMotors);
	}
	else{
	leftLifter->Set(lifterSpeed);
	rightLifter->Set(lifterSpeed);
	SmartDashboard::PutNumber("angle", shooterEncoder->GetDistance());
	}
	SmartDashboard::PutNumber("lifterpower", lifterSpeed);
	SmartDashboard::PutNumber("encoder angle", shooterEncoder->Get()*kEncoderAngleVal);
}


bool Shooter::setAngle(double angle){
	if ((kAngleErrorMargin<= angle- shooterEncoder->Get()*kEncoderAngleVal) && (kAngleErrorMargin>= angle- shooterEncoder->Get()*kEncoderAngleVal)){
		angleBall(kStopMotors);
		return true;
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal<angle){
		angleBall(kAngleBallSpeed);
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal>angle){
		angleBall(-kAngleBallSpeed);
	}
	else{
		angleBall(kStopMotors);
		return true;
	}
	return false;
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
