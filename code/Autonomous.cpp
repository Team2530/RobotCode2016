/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>


//instantiates robot drive, timer, step/bool algorithm, and sendable chooser
Autonomous::Autonomous(DriveTrain *dt) {
	robotd=dt;
	timer= new Timer();
	step=1;
	isDone=false;


} //autonomous function to do nothing
	void Autonomous::doNothing(){
		robotd->DriveSet(0.0,0.0);
	} //drives over a defense
	void Autonomous::driveOverDefense(){
		robotd->driveDistance(130,.5);
		/*if (step==1){
			isDone= robotd->driveDistance(96,.5);
			if (isDone){
				step++;
				isDone=false;
			}
		}
		else if (step==2){
			isDone= robotd->turnRight(60);
			if (isDone){
				step++;
				isDone=false;
			}
		}
		//make sure arm is lowered first

		else if (step==3){
			robotd->setServo(130);
			robotd->driveShoot(1.0);
		}*/


		//robotd->turnRight(90);
		//robotd->turnLeft(90); //needs work
		/*if (autoSelected==autoNameLeft){
			if (step==1){
				isDone=robotd->driveDistance(60,.5);
				if (isDone){
					isDone=false;
					step++;
				}
			}
			else if (step==2){
				isDone=robotd->turnRight(45);
				if (isDone){
					isDone=false;
					step++;
				}
			}
			//drive more or shoot

		}
		else if (autoSelected==autoNameRight){
			if (step==1){
				isDone=robotd->driveDistance(80,5);
				if (isDone){
					isDone=false;
					step++;
				}
			}
			//drive more or shoot
		}
		else{
			if (autoSelected==autoNameLeft){
				if (step==1){
					isDone=robotd->driveDistance(60,.5);
					if (isDone){
						isDone=false;
						step++;
					}
				}
				else if (step==2){
					isDone=robotd->turnLeft(90);
					if (isDone){
						isDone=false;
						step++;
					}
				}
						//drive more or shoot
			}

		}*/
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
