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
	leftShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM6);
	rightShooter= new TalonSRX(ControllerConstants::PWMPort::kPWM7);

	leftLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM4);
	rightLifter= new TalonSRX(ControllerConstants::PWMPort::kPWM5);
	shooterEncoder= new Encoder(ControllerConstants::DIOPort::kDIO4, ControllerConstants::DIOPort::kDIO5); //check ports
	shooterEncoder->SetDistancePerPulse(kDefaultEncoderPulseVal);// take ticks from 90-0, div 90
	shooterEncoder->Reset();
	//check ports
	low1= new DigitalInput(ControllerConstants::DIOPort::kDIO8);
	low2= new DigitalInput(ControllerConstants::DIOPort::kDIO9);
	high1= new DigitalInput(ControllerConstants::DIOPort::kDIO6);
	high2= new DigitalInput(ControllerConstants::DIOPort::kDIO7);

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
	if (lowStop(low1->Get(),low2->Get()) && lifterSpeed>kStopMotors){
		leftLifter->Set(0);
		rightLifter->Set(0);
	}
	else if (highStop(high1->Get(), high2->Get()) && lifterSpeed< kStopMotors){
		leftLifter->Set(0);
		rightLifter->Set(0);
		shooterEncoder->Reset();
	}
	else if ((lifterSpeed<kLifterSpeedMin && lifterSpeed>-kLifterSpeedMin)){
		leftLifter->Set(kStopMotors);
		rightLifter->Set(kStopMotors);
	}
	else if((lifterSpeed>kLifterSpeedCap) || (lifterSpeed<-kLifterSpeedCap)){
		leftLifter->Set(kLifterSpeedCap);
		rightLifter->Set(kLifterSpeedCap);
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
	 double angleDiff=angle- shooterEncoder->Get()*kEncoderAngleVal;
	 if (angleDiff<0){
		 angleDiff*=-1;
	 }
	if ((kAngleErrorMargin>= angleDiff)){
		angleBall(kStopMotors);
		return true;
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal>angle){
		angleBall(-kAngleBallSpeed);
	}
	else if (shooterEncoder->Get()*kEncoderAngleVal<angle){
		angleBall(kAngleBallSpeed);
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
