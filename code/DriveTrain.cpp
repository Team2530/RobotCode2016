/*
 * DriveTrain.cpp *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <DriveTrain.h>



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

}
	void DriveTrain::AutonomousInit(){
		leftEncoder->Reset();
		rightEncoder->Reset();
		ahrs->Reset();
		step=1;

	}
	void DriveTrain::TeleopInit(){
		leftEncoder->Reset();
		rightEncoder->Reset();
		ahrs->Reset();
		step=1;
		spike->Set(Relay::Value::kOn);




	}
	double DriveTrain::getThrottle(double val){
		 float throttle = leftStick->GetThrottle();
		 throttle++;
		 throttle = throttle *((1-val)/2);


		 throttle+= val;
		 return throttle;}

	void DriveTrain::Drive(){


		float throttle = getThrottle(.4);
			myRobot->TankDrive(leftStick->GetY()*throttle, rightStick->GetY()*throttle, true);

		if (xBox->GetRawButton(2)){
			shooter->shoot();
		}
		else if (xBox->GetRawButton(3)){
			shooter->takeInBall();
		}
		else if (xBox->GetRawButton(1)){
			shooter->stopMotors();
		}
		if (leftStick->GetRawButton(2)){
			servo->Set(0);
		}
		else if (rightStick->GetRawButton(2)){
			servo->Set(130);
		}

		shooter->angleBall(xBox->GetRawAxis(5));
		SmartDashboard::PutNumber("LD", leftEncoder->GetDistance()); //-432
		SmartDashboard::PutNumber("RD", rightEncoder->GetDistance()); //630
		SmartDashboard::PutNumber("angleTele", ahrs->GetAngle());
		//OneStick: myRobot->ArcadeDrive(stick->GetY()*throttle, stick->GetTwist(),true);
	}



	void DriveTrain::DriveSet(float speed, float angle){
		myRobot->ArcadeDrive(speed,angle,true);
	}

	void DriveTrain::driveDistance(int distanceInches, float speed){
		if (step==1){
			angleStart= ahrs->GetAngle()-180;
			myRobot->Drive(0.0,0.0);
			step++;
		}

		if (step==2){
			double changeInAngle= ((ahrs->GetAngle()-180)-angleStart);
			if (leftEncoder->GetDistance()< distanceInches && leftEncoder->GetDistance()> -distanceInches && rightEncoder->GetDistance()< distanceInches && rightEncoder->GetDistance()>-distanceInches){
				myRobot->Drive(-speed, changeInAngle/80);
			}
			else{
				myRobot->ArcadeDrive(0.0,0.0,true);

			}
			SmartDashboard::PutNumber("left distance Auto", leftEncoder->GetDistance());
			SmartDashboard::PutNumber("right distance Auto", rightEncoder->GetDistance());
			SmartDashboard::PutNumber("changeInAngle", changeInAngle/80);
		}

	}

	void DriveTrain::turnRight(double angle){

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

				}
			}
			else{
				if (ahrs->GetAngle()>startAngle||ahrs->GetAngle()<stopAngle){
					myRobot->Drive(speed,1);
				}
				else{
					myRobot->ArcadeDrive(0,0,true);

				}
			}

		}
		SmartDashboard::PutNumber("Current Angle", ahrs->GetAngle());
		SmartDashboard::PutNumber("StartAngle", startAngle);
		SmartDashboard::PutNumber("Stop Angle", stopAngle);


	}

	void DriveTrain::turnLeft(double angle){
		if (step==1){
					startAngle= ahrs->GetAngle();
					stopAngle= startAngle-angle;
					if (stopAngle<0){
						stopAngle+=360;
					}
					step++;
				}
		if(step==2){
		angleTheta= stopAngle-ahrs->GetAngle();
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

					}
				}
				else{
					if (ahrs->GetAngle()<startAngle||ahrs->GetAngle()>stopAngle){
						myRobot->Drive(speed,-1);
					}
					else{
						myRobot->ArcadeDrive(0,0,true);

					}
				}
		}
		SmartDashboard::PutNumber("Current Angle2", ahrs->GetAngle());
		SmartDashboard::PutNumber("StartAngle2", startAngle);
		SmartDashboard::PutNumber("Stop Angle2", stopAngle);

	}
