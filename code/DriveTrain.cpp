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
		vic1 = new VictorSP(3);
		vic2= new VictorSP(2);


		vic3= new VictorSP(1);
		vic4= new VictorSP(0);
		myRobot= new RobotDrive(vic1,vic2,vic3,vic4);

		leftEncoder = new Encoder (2,3, true, CounterBase:: k4X); //check ports
		rightEncoder = new Encoder (0,1, true, CounterBase:: k4X);
		leftEncoder->SetDistancePerPulse((-1*3.14159*8)/432); //check circumference/(pulses per revolution)
		rightEncoder->SetDistancePerPulse((3.14159*8)/630);

		leftStick = new Joystick(0);
		rightStick= new Joystick(1);
		xBox= new Joystick(2);
		servo= new Servo(8);
		ahrs= new AHRS(SerialPort::kMXP);
		step=1;
		spike= new Relay(0,Relay::Direction::kForwardOnly);
		shooter= new Shooter();
		done=false;



}

//used for autonomousinit in robot.cpp
	void DriveTrain::AutonomousInit(){
		leftEncoder->Reset();
		rightEncoder->Reset();
		ahrs->Reset();
		step=1;

	}
	//used for teleopinit in robot.cpp
	void DriveTrain::TeleopInit(){
		leftEncoder->Reset();
		rightEncoder->Reset();
		ahrs->Reset();
		step=1;
		spike->Set(Relay::Value::kOn);




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


		float throttle = getThrottle(.4); //minimum value for throttle in (min, 1)
		//if x is pressed let operator pivot
		if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kXbutton)){
			myRobot->Drive(xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kLSXAxis),1);
		}//otherwise drive with each stick controlling the robot
		else{
			myRobot->TankDrive(rightStick->GetY()*throttle, leftStick->GetY()*throttle, true);
		}

			//button RT controls power of shooter
		if (xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kRTAxis)>.1){
			shooter->shoot(xBox->GetRawAxis(ControllerConstants::xBoxAxisMap::kRTAxis));
		}
		//if right bumper is pressed, shoot boulder at 100% power
		else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kRBbutton)){
			shooter->shoot(1);
		}
		//button LB takes in the ball and resets Servo
		else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kLBbutton)){
			shooter->takeInBall();
			servo->Set(0);
		}

		//button Y stops motors and resets Servo
		else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kYbutton)){
			shooter->stopMotors();
			servo->Set(0);
		}

		//button RB flicks servo to send ball through motors
		else if (xBox->GetRawButton(ControllerConstants::xBoxButtonMap::kAbutton)){
			servo->Set(130);
		}

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
		if (step==1){
			angleStart= ahrs->GetAngle()-180;
			myRobot->Drive(0.0,0.0);
			step++;
		}
		//find difference in this angle from angle last loop and drive opposite of that; keep driving until distance is reached
		if (step==2){
			double changeInAngle= ((ahrs->GetAngle()-180)-angleStart);
			if (leftEncoder->GetDistance()< distanceInches && leftEncoder->GetDistance()> -distanceInches && rightEncoder->GetDistance()< distanceInches && rightEncoder->GetDistance()>-distanceInches){
				myRobot->Drive(-speed, changeInAngle/80);
			}
			else{
				myRobot->ArcadeDrive(0.0,0.0,true);
				done =true;

			}
			SmartDashboard::PutNumber("left distance Auto", leftEncoder->GetDistance());
			SmartDashboard::PutNumber("right distance Auto", rightEncoder->GetDistance());
			SmartDashboard::PutNumber("changeInAngle", changeInAngle/80);
		}
		return done;

	}

	//flip servo so boulder goes through shooter
	void DriveTrain::setServo(float angle){
		servo->Set(angle);

	}

	//turn right until angle is reached; slow down as angle approaches
	bool DriveTrain::turnRight(double angle){

		if (step==1){
			startAngle= ahrs->GetAngle();
			stopAngle= startAngle+angle;
			if (stopAngle>360){
				stopAngle-=360;
			}
			step++;
		}
		if (step==2){
			angleTheta= stopAngle-ahrs->GetAngle();
			if (angleTheta<=0){
				angleTheta= (stopAngle+360);
			}
			speed =angleTheta/(1.2*angle);
			if (speed>.3){
				speed=.3;
			}
			if (speed<.1){
				speed=.1;
			}
			if (startAngle<stopAngle){
				if (ahrs->GetAngle()<stopAngle){
					myRobot->Drive(speed,1);
				}
				else{
					myRobot->ArcadeDrive(0.0,0,true);
					done= true;

				}
			}
			else{
				if (ahrs->GetAngle()>startAngle||ahrs->GetAngle()<stopAngle){
					myRobot->Drive(speed,1);
				}
				else{
					myRobot->ArcadeDrive(0,0,true);
					done=true;

				}
			}


		}
		SmartDashboard::PutNumber("Current Angle", ahrs->GetAngle());
		SmartDashboard::PutNumber("StartAngle", startAngle);
		SmartDashboard::PutNumber("Stop Angle", stopAngle);
		return done;

	}

	//turn left until stop angle is reached; slow down as angle approaches
	bool DriveTrain::turnLeft(double angle){
		if (step==1){
					startAngle= ahrs->GetAngle();
					stopAngle= startAngle-angle;
					if (stopAngle<0){
						stopAngle+=360;
					}
					step++;
				}
		if(step==2){
		angleTheta= ahrs->GetAngle()-stopAngle;
				if (angleTheta<=0){
					angleTheta= (stopAngle+360);
				}
				speed= angleTheta/(1.2*angle);
				if (speed>.3){
					speed=.3;
				}
				if (speed<.1){
					speed=.1;
				}
				if (stopAngle<startAngle){
					if (stopAngle<ahrs->GetAngle()){
						myRobot->Drive(speed,-1);
					}
					else{
						myRobot->ArcadeDrive(0,0,true);
						done = true;
					}
				}
				else{
					if (ahrs->GetAngle()<startAngle||ahrs->GetAngle()>stopAngle){
						myRobot->Drive(speed,-1);
					}
					else{
						myRobot->ArcadeDrive(0,0,true);
						done=true;
					}
				}
		}
		SmartDashboard::PutNumber("Current Angle2", ahrs->GetAngle());
		SmartDashboard::PutNumber("StartAngle2", startAngle);
		SmartDashboard::PutNumber("Stop Angle2", stopAngle);
		return done;

	}
	//shoot ball at specified speed; used for other functions in DriveTrain.cpp
	void DriveTrain::driveShoot(double speed){
		shooter->shoot(speed);
	}
