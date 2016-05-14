/*
 * DriveTrain.cpp *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <DriveTrain.h>
#include "ControllerConstants.h"



//instantiates drive train, encoders, joysticks, shooter/manipulator objects, step/done algorithm, and camera objects
DriveTrain::DriveTrain() {

	//=new Victor(port) for kitbot, SP for actual bot
	vic1 = new VictorSP(ControllerConstants::PWMPort::kPWM0);
	vic2= new VictorSP(ControllerConstants::PWMPort::kPWM1);
	camera = new Camera();

	vic3= new VictorSP(ControllerConstants::PWMPort::kPWM2);
	vic4= new VictorSP(ControllerConstants::PWMPort::kPWM3);
	myRobot= new RobotDrive(vic1,vic2,vic3,vic4);

	rightEncoder = new Encoder (ControllerConstants::DIOPort::kDIO2, ControllerConstants::DIOPort::kDIO3, true, CounterBase:: k4X); //check ports
	leftEncoder = new Encoder (ControllerConstants::DIOPort::kDIO0, ControllerConstants::DIOPort::kDIO1, true, CounterBase:: k4X);
	leftEncoder->SetDistancePerPulse(kLeftDistancePerPulse); //check circumference/(pulses per revolution)
	rightEncoder->SetDistancePerPulse(kRightDistancePerPulse);

	leftStick = new Joystick(ControllerConstants::USBJoystickPort::kUSB0);
	rightStick= new Joystick(ControllerConstants::USBJoystickPort::kUSB1);
	xBox= new Joystick(ControllerConstants::USBJoystickPort::kUSB2);
	servo= new Servo(ControllerConstants::PWMPort::kPWM8);
	servo->SetAngle(kServoRest);

	ahrs= new AHRS(SerialPort::kMXP);
	step=1;
	spike= new Relay(ControllerConstants::RelayPort::kRP0,Relay::Direction::kForwardOnly);
	//spike->Set(Relay::Value::kOn);
	shooter= new Shooter();
	done=false;



}

//used for autonomousinit in robot.cpp
void DriveTrain::AutonomousInit(){
	leftEncoder->Reset();
	rightEncoder->Reset();
	ahrs->Reset();
	step=1;
	shooter->resetEncoder();
	//spike->Set(Relay::Value::kOn);

}
//used for teleopinit in robot.cpp
void DriveTrain::TeleopInit(){
	leftEncoder->Reset();
	rightEncoder->Reset();
	ahrs->Reset();
	//spike->Set(Relay::Value::kOff);
	//shooter->resetEncoder();




}

//makes sensitivity from val to 1 on joystick slider
double DriveTrain::getThrottle(double val){
	float throttle = leftStick->GetThrottle();
	throttle++;
	throttle = throttle *((1-val)/2);


	throttle+= val;
	return throttle;}

//all functions necessary for teleopperiodic
void DriveTrain::Drive(){


	float throttle = getThrottle(kThrottleMinimum); //minimum value for throttle in (min, 1)
	//if x is pressed let operator pivot
	if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kBbutton)){
		throttle=.5;
	}
	if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kXbutton)){
		myRobot->Drive(0.5 * xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kLSXAxis),kTurnRightFullDegrees);
	}//otherwise drive with each stick controlling the robot
	else if (leftStick->GetRawButton(2)){
		driveDistance(50, -.75); //
		leftEncoder->Reset();
		rightEncoder->Reset();
	}
	else if (rightStick->GetRawButton(2)){
		driveDistance(50, .75);
		leftEncoder->Reset();
		rightEncoder->Reset();
	}
	//else if (leftStick->GetRawButton(2)){
		//	driveDistance(50,.75);
		//}
	//interesting. why is the left commented out but not the right?
	else{
		myRobot->TankDrive(leftStick->GetY()*throttle*-1, rightStick->GetY()*throttle*-1, true);
		step=1;
	}

	//button RT controls power of shooter
	if (xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kRTAxis)>kTriggerThreshold){
		shooter->shoot(xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kRTAxis));
	}
	//if right bumper is pressed, shoot boulder at 100% power
	else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kRBbutton)){
		shooter->shoot(kshoot100);
	}
	//button LB takes in the ball and resets Servo
	else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kLBbutton)){
		shooter->takeInBall();
		servo->SetAngle(kServoRest);
	}

	//button Y stops motors and resets Servo
	else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kYbutton)){
		shooter->stopMotors();
		servo->SetAngle(kServoRest);
	}

	//button RB flicks servo to send ball through motors
	else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kAbutton)){
		servo->SetAngle(kServoShoot);
	}



	//camera->cameraTeleop();
	//lift boulder at left analog stick speed
	shooter->angleBall(xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kLSYAxis));
	SmartDashboard::PutNumber("LD", leftEncoder->GetDistance()); //-432
	SmartDashboard::PutNumber("RD", rightEncoder->GetDistance()); //630
	SmartDashboard::PutNumber("angleTele", ahrs->GetAngle());
	//OneStick: myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist(),true);
}


//drive function useful for auto, avoids ArcadeDrive
void DriveTrain::DriveSet(float speed, float angle){
	myRobot->ArcadeDrive(speed,angle,true);
}

//drives until certain distance is reached

bool DriveTrain::driveDistance(int distanceInches, float speed){
	//get start angle
	done = false;
	if (step==1){
		angleStart= ahrs->GetAngle()-kOppositeAngle;
		leftEncoder->Reset();
		rightEncoder->Reset();
		myRobot->Drive(kNoPower,kNoAngle);
		step++;
	}
	//find difference in this angle from angle last loop and drive opposite of that; keep driving until distance is reached
	if (step==2){
		double changeInAngle= ((ahrs->GetAngle()-kOppositeAngle)-angleStart);
		float backwardsDirection = 1.0;
		if (speed < 0.0){
			backwardsDirection = -1.0;
		}
		if (leftEncoder->GetDistance()< distanceInches
				&& leftEncoder->GetDistance() > -distanceInches
				&& rightEncoder->GetDistance() < distanceInches
				&& rightEncoder->GetDistance() > -distanceInches){
			myRobot->Drive(speed, -backwardsDirection*changeInAngle/kChangeInAngleConstant);
		}
		else{
			myRobot->Drive(kNoPower,kNoAngle);
			step = 1;
			done = true;
		}

		SmartDashboard::PutNumber("left distance Auto", leftEncoder->GetDistance());
		SmartDashboard::PutNumber("right distance Auto", rightEncoder->GetDistance());
		SmartDashboard::PutNumber("changeInAngle", changeInAngle/kChangeInAngleConstant);
	}

	return done;
}

//flip servo so boulder goes through shooter
void DriveTrain::setServo(float angle){
	servo->SetAngle(angle);

}

//turn right until angle is reached; slow down as angle approaches
bool DriveTrain::turnRight(double angle){
	done = false;
	if (step==1){
		ahrs->Reset();
		startAngle= ahrs->GetAngle(); // returns z-yaw angle in degrees
		stopAngle= startAngle+angle;
		if (stopAngle>kFullCircle){
			stopAngle-=kFullCircle;
		}
		step++;
	}
	if (step==2){
		angleTheta= stopAngle-ahrs->GetAngle();
		if (angleTheta<=0){ //-180
			angleTheta= (angleTheta+kFullCircle);
			std::printf("angle set to stop+Full circle\n");
		}
		speed =angleTheta/(kAngleThetaConstant*angle);
		if (speed>kTurnSpeedCap){
			speed=kTurnSpeedCap;
			std::printf("speed set to Turn speed cap\n");
		}
		if (speed<kTurnSpeedMin){
			speed=kTurnSpeedMin;
			std::printf("speed set to speed min\n");
		}
		if (startAngle<stopAngle){
			if (ahrs->GetAngle()<stopAngle){
				myRobot->Drive(speed,1.0);
				//std::printf("DRIVE A VECTOR\n");
				SmartDashboard::PutNumber("CodeLocation", 1);
			}
			else{
				myRobot->Drive(kNoPower,kNoAngle);
				//std::printf("DRIVE IN ARCADE! LIKE CAVE JOHNSON/n");
				SmartDashboard::PutNumber("CodeLocation", 2);
				done= true;
				//std::printf("done");
			}
		}
		else{
			if (ahrs->GetAngle()>(startAngle-10)||ahrs->GetAngle()<stopAngle){
				myRobot->Drive(speed,1.0);
				SmartDashboard::PutNumber("CodeLocation", 3);
				//std::printf("consider the other case\n");
			}
			else{
				myRobot->Drive(kNoPower,kNoAngle);
				done=true;
				SmartDashboard::PutNumber("CodeLocation", 4);
				//std::printf("done with other case\n");
			}
		}


	}
	SmartDashboard::PutNumber("Current Angle", ahrs->GetAngle());
	SmartDashboard::PutNumber("StartAngle", startAngle);
	SmartDashboard::PutNumber("Stop Angle", stopAngle);
	if (done){ step = 1;}
	return done;

}

//turn left until stop angle is reached; slow down as angle approaches
bool DriveTrain::turnLeft(double angle){
	done = false;
	if (step==1){
		ahrs->Reset();
		startAngle= ahrs->GetAngle();
		stopAngle= startAngle-angle;
		if (stopAngle<kNoAngle){
			stopAngle+=kFullCircle;
		}
		step++;
	}
	if(step==2){
		angleTheta= ahrs->GetAngle()-stopAngle;
		if (angleTheta<=0){
			angleTheta= (angleTheta+kFullCircle);
		}
		speed= angleTheta/(kAngleThetaConstant*angle);
		if (speed>kTurnSpeedCap){
			speed=.23;
		}
		if (speed<kTurnSpeedMin){
			speed=.125;
		}
		if (stopAngle<startAngle){
			if (stopAngle<ahrs->GetAngle()){
				myRobot->Drive(speed,-kTurnRightFullDegrees); //TankDrive(-,+)
			}
			else{
				myRobot->Drive(kNoPower,kNoAngle);
				done = true;
			}
		}
		else{
			if (ahrs->GetAngle()<=startAngle||ahrs->GetAngle()>stopAngle){
				myRobot->Drive(speed,-kTurnRightFullDegrees);
			}
			else{
				myRobot->Drive(kNoPower,kNoAngle);
				done=true;
			}
		}
	}
	SmartDashboard::PutNumber("Current Angle2", ahrs->GetAngle());
	SmartDashboard::PutNumber("StartAngle2", startAngle);
	SmartDashboard::PutNumber("Stop Angle2", stopAngle);
	if (done) step = 1;
	return done;

}
//shoot ball at specified speed; used for other functions in DriveTrain.cpp
void DriveTrain::driveShoot(double speed){
	shooter->shoot(speed);
}

double DriveTrain::getTargetD(){
	return camera->getDis();
}

double DriveTrain::getTargetA(){
	return camera->getAng();
}

bool DriveTrain::setAngle(double theta){
	bool isDoneNow=false;
	isDoneNow= shooter->setAngle(theta);
	return isDoneNow;
}

void DriveTrain::stayAtTheTop(){
	shooter->stayAtTheTop();
}
