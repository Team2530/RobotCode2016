/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>


//instantiates robot drive, timer, step/bool algorithm, and sendable chooser
Autonomous::Autonomous(DriveTrain *dt, std::string str) {
	robotd=dt;
	timer= new Timer();
	step=1;
	isDone=false;
	autoMode= str;


} //autonomous function to do nothing
	void Autonomous::doNothing(){
		robotd->DriveSet(0.0,0.0);
	} //drives over a defense
	void Autonomous::driveOverDefense(){
		if (autoMode.compare("Do Nothing")==kModesEqual){
			doNothing();
		}
		else if (autoMode.compare("Drive Over Defense")==kModesEqual){
			robotd->driveDistance(130,kAutoSpeed);
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
				isDone= robotd->driveDistance(30,kAutoSpeed); //check distance
				nextStep(isDone);
			}
			else if (step==2){
				isDone= robotd->setAngle(20); //create lowerShooter&raiseShooter methods in shooter.cpp
				nextStep(isDone);
			}
			else if (step==3){
				isDone= robotd->driveDistance(240,kAutoSpeed); //check distance
				nextStep(isDone);
			}
			else if (step==4){
				isDone= robotd->turnRight(kLowGoalAngle); //turnLeft if from right side
				nextStep(isDone);
			}
			else if (step==5){
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
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
				isDone= robotd->driveDistance(30,kAutoSpeed); //check distance
				nextStep(isDone);
			}
			else if (step==2){
			isDone= robotd->setAngle(20); //create lowerShooter&raiseShooter methods in shooter.cpp
				nextStep(isDone);
			}
			else if (step==3){
				isDone= robotd->driveDistance(240,kAutoSpeed); //check distance
				nextStep(isDone);
			}
			else if (step==4){
				isDone= robotd->turnLeft(kLowGoalAngle); //turnLeft if from right side
				nextStep(isDone);
			}
			else if (step==5){
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(1.0);
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
					isDone= robotd->driveDistance(20,kAutoSpeed); //check distance
					nextStep(isDone);
			}
			else if (step==2){
			isDone= robotd->setAngle(20);
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
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
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
			isDone= robotd->setAngle(20);
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
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
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
			//isDone= robotd->lowerShooter(20);
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
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
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
			isDone= robotd->setAngle(20);
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
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
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
			isDone= robotd->setAngle(20);
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
				robotd->setServo(kServoShootAngle);
				robotd->driveShoot(kAutoShootSpeed);
			}

		}



	}//drives towards tower based on where robot is placed
	bool Autonomous::attackTower(std::string position){
		//Angle/drive based on position
		return false;
	}
	//start timer function for using time outside of autonomous.cpp
	void Autonomous::startTimer(){
		timer->Start();
	}
	bool Autonomous::nextStep(bool done){
		if (done){
			step++;
			done=false;
		}
		return done;
	}
	void Autonomous::reset(){
		step=1;
	}
	void Autonomous::test(){
		isDone=false;
		if (step==1){
			isDone = robotd->turnLeft(90);
			nextStep(isDone);
		}
		if (step==2){

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
;
