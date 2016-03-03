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
		if (autoMode.compare("Do Nothing")==0){
			doNothing();
		}
		else if (autoMode.compare("Drive Over Defense")==0){
			robotd->driveDistance(130,.5);
		}
		else if (autoMode.compare("Left Low Goal")==0){
			/*low goal code:
			*drives specified distance at specified speed
			*lowers shooter to specified angle
			*drives of obstacle at specified speed
			*turns left or right towards goal
			*starts motors and flicks boulder with servo
			*/

			if (step==1){
				isDone= robotd->driveDistance(30,.6); //check distance
				nextStep(isDone);
			}
			else if (step==2){
			//	isDone= robotd->lowerShooter(20); //create lowerShooter&raiseShooter methods in shooter.cpp
				nextStep(isDone);
			}
			else if (step==3){
				isDone= robotd->driveDistance(240,.6); //check distance
				nextStep(isDone);
			}
			else if (step==4){
				isDone= robotd->turnRight(60); //turnLeft if from right side
				nextStep(isDone);
			}
			else if (step==5){
				robotd->setServo(130);
				robotd->driveShoot(1.0);
			}
		}
		else if (autoMode.compare("Right Low Goal")==0){
			/*low goal code:
			*drives specified distance at specified speed
			*lowers shooter to specified angle
			*drives of obstacle at specified speed
			*turns left or right towards goal
			*starts motors and flicks boulder with servo
			*/

			if (step==1){
				isDone= robotd->driveDistance(30,.6); //check distance
				nextStep(isDone);
			}
			else if (step==2){
			//	isDone= robotd->lowerShooter(20); //create lowerShooter&raiseShooter methods in shooter.cpp
				nextStep(isDone);
			}
			else if (step==3){
				isDone= robotd->driveDistance(240,.6); //check distance
				nextStep(isDone);
			}
			else if (step==4){
				isDone= robotd->turnLeft(60); //turnLeft if from right side
				nextStep(isDone);
			}
			else if (step==5){
				robotd->setServo(130);
				robotd->driveShoot(1.0);
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
