/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>



Autonomous::Autonomous(DriveTrain *dt) {
	robotd=dt;
	timer= new Timer();
	step=1;


}
	void Autonomous::doNothing(){
		robotd->DriveSet(0.0,0.0);
	}
	void Autonomous::driveOverDefense(){
		robotd->driveDistance(80,.5);
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
	}
	bool Autonomous::attackTower(std::string position){
		//Angle/drive based on position
		return false;
	}
	void Autonomous::startTimer(){
		timer->Start();
	}
