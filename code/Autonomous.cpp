/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>


//instantiates robot drive, timer, step/bool algorithm, and string from sendable chooser
Autonomous::Autonomous(DriveTrain *dt, std::string str){
	robotd=dt;
	timer= new Timer();
	step=1;
	isDone=false;
	autoMode= str;
}

//autonomous function to do nothing
void Autonomous::doNothing(){
	robotd->DriveSet(0.0,0.0);
}

//checks if string passed into Autonomous class is equal to any of the Auto Modes. If so, it runs that Auto Mode!
void Autonomous::driveOverDefense(){
	SmartDashboard::PutString("Auto Selected", autoMode);
	if (autoMode.compare("Do Nothing")==kModesEqual){
		doNothing();
		SmartDashboard::PutString("DN TEST", "Done");
	}
	else if (autoMode.compare("Drive Over Defense")==kModesEqual){
		if (step==1){
			isDone = robotd->driveDistance(140,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==2){
			doNothing();
		}
	}
	else if (autoMode.compare("Rock Wall or Moat")==0){

		if (step==1){
			// negative speed means go backwards
			isDone = robotd->driveDistance(140,(-kAutoSpeed)-.07);
		}
		else if (step==2){
			doNothing();
		}
	}
	else if (autoMode.compare("Left Low Goal")==kModesEqual){
		/*low goal code:
		 *drives specified distance at specified speed
		 *lowers shooter to specified angle
		 *drives of obstacle at specified speed
		 *turns left or right towards goal
		 *starts motors and flicks boulder with servo
		 */

		if (step==1){
			isDone= true;//robotd->driveDistance(30,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(260); //create lowerShooter&raiseShooter methods in shooter.cpp
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(140,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==4){
			isDone= robotd->turnRight(3);
			nextStep(isDone);
		}
		else if (step==5){
			isDone= robotd->driveDistance(40,kAutoSpeed);
		}
		else if (step==6){
			isDone= robotd->turnRight(kLowGoalAngle-5); //turnLeft if from right side
			nextStep(isDone);
		}
		else if (step==7){
			isDone= robotd->driveDistance(95, kAutoSpeed);
		}
		else if (step==8){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}
	}
	else if (autoMode.compare("Right Low Goal")==kModesEqual){
		/*low goal code:
		 *drives specified distance at specified speed
		 *lowers shooter to specified angle
		 *drives of obstacle at specified speed
		 *turns left or right towards goal
		 *starts motors and flicks boulder with servo
		 */

		if (step==1){
			isDone= true;//robotd->driveDistance(30,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(260); //create lowerShooter&raiseShooter methods in shooter.cpp
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(200,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==4){
			isDone= robotd->turnLeft(kLowGoalAngle); //turnLeft if from right side
			nextStep(isDone);
		}
		else if (step==5){
			isDone= robotd->driveDistance(25, kAutoSpeed);
		}
		else if (step==6){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}
	}
	else if (autoMode.compare("P1 High")==kModesEqual){
		/*high goal code:
		 * drives a little
		 * lowers arm
		 * drives over obstacle
		 * turns towards goal //maybe drive even more before doing this???
		 * drives 5 feet from goal
		 * raises arm to specified angle
		 * shoots boulder
		 */
		xangle= robotd->getTargetA(); //check function and add pointer to variable
		imageDistance= robotd->getTargetD(); //check function and add pointer to variable
		if (step==1){
			isDone= true; //robotd->driveDistance(20,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(260);
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(140,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==4){
			isDone=robotd->turnRight(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==5){
			isDone=robotd->driveDistance((int)(imageDistance-kDistanceAwayFromTarget), kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==6){
			isDone= robotd->setAngle(200); //check angle
			nextStep(isDone);
		}
		else if (step==7){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}

	}

	else if (autoMode.compare("P2 High")==kModesEqual){

		xangle= robotd->getTargetA(); //check function and add pointer to variable
		imageDistance= robotd->getTargetD(); //check function and add pointer to variable
		if (step==1){
			isDone= robotd->driveDistance(20,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(200);
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(100,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==4){
			isDone=robotd->turnRight(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==5){
			isDone=robotd->driveDistance((int)(imageDistance-kDistanceAwayFromTarget), kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==6){
			isDone= robotd->setAngle(45); //check angle
			nextStep(isDone);
		}
		else if (step==7){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}

	}

	else if (autoMode.compare("P3 High")==kModesEqual){

		xangle= robotd->getTargetA(); //check function and add pointer to variable
		imageDistance= robotd->getTargetD(); //check function and add pointer to variable
		if (step==1){
			isDone= robotd->driveDistance(20,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(200);
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(100,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==4){
			isDone=robotd->turnRight(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==5){
			isDone=robotd->driveDistance((int)(imageDistance-kDistanceAwayFromTarget), kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==6){
			//isDone= robotd->raiseShooter(45); //check angle
			nextStep(isDone);
		}
		else if (step==7){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}

	}
	else if (autoMode.compare("P4 High")==kModesEqual){

		xangle= robotd->getTargetA(); //check function and add pointer to variable
		imageDistance= robotd->getTargetD(); //check function and add pointer to variable
		if (step==1){
			isDone= robotd->driveDistance(20, kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(200);
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(100,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==4){
			isDone=robotd->turnLeft(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==5){
			isDone=robotd->driveDistance((int)(imageDistance-kDistanceAwayFromTarget), kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==6){
			isDone= robotd->setAngle(45); //check angle
			nextStep(isDone);
		}
		else if (step==7){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}

	}


	else if (autoMode.compare("P5 High")==kModesEqual){
		xangle= robotd->getTargetA(); //check function and add pointer to variable
		imageDistance= robotd->getTargetD(); //check function and add pointer to variable
		if (step==1){
			isDone= robotd->driveDistance(20,kAutoSpeed); //check distance
			nextStep(isDone);
		}
		else if (step==2){
			isDone= robotd->setAngle(200);
			nextStep(isDone);
		}
		else if (step==3){
			isDone= robotd->driveDistance(100,kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==4){
			isDone=robotd->turnLeft(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==5){
			isDone=robotd->driveDistance((int)(imageDistance-kDistanceAwayFromTarget), kAutoSpeed);
			nextStep(isDone);
		}
		else if (step==6){
			isDone= robotd->setAngle(45); //check angle
			nextStep(isDone);
		}
		else if (step==7){
			robotd->driveShoot(1.0);
			if (timer->Get()>13){
				robotd->setServo(kServoShootAngle);
			}
		}

	}



}

//drives towards tower based on where robot is placed. Currently not used.
bool Autonomous::attackTower(std::string position){
	//Angle/drive based on position
	return false;
}


//start timer function for using time outside of autonomous.cpp
void Autonomous::startTimer(){
	timer->Start();
}

//increases the step and resets the boolean for the step/bool algorithm
bool Autonomous::nextStep(bool done){
	if (done){
		step++;
		done=false;
		isDone=false;
	}
	return done;
}

//resets the step for autonomous.cpp
void Autonomous::reset(){
	step=1;
}

//Only used for testing a certain function from DriveTrain.cpp in Autonomous.cpp
void Autonomous::test(){
	isDone=false;
	if (step==1){
		isDone = robotd->turnRight(90);
		nextStep(isDone);
	}
	if (step==2){
		robotd->DriveSet(0,0);
	}
	/*if (step==1){
			isDone=robotd->turnLeft(xangle); //or turn left based on position
			nextStep(isDone);
		}
		else if (step==2){
			isDone=robotd->setAngle(45);
			nextStep(isDone);
		}
		else if (step==3){
			robotd->driveShoot(kAutoShootSpeed);
			robotd->setServo(kServoShootAngle);
		}*/

}
void Autonomous::setSelected(std::string selected){
	autoMode= selected;
}
