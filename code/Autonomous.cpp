/*
 * Autonomous.cpp
 *
 *  Created on: Jan 31, 2016
 *      Authors: Eric and Jack
 */

#include <Autonomous.h>



Autonomous::Autonomous(DriveTrain *dt) {
	chooser = new SendableChooser();
	chooser->AddDefault(dN, (void*)&dN);

	SmartDashboard::PutData("Auto Modes", chooser);
	autoSelected = *((std::string*)chooser->GetSelected());
	std::string autoSelected = SmartDashboard::GetString("Auto Selector", dN);
	std::cout << "Auto selected: " << autoSelected << std::endl;
	robotd=dt;
	timer= new Timer();


}
	void Autonomous::doNothing(){
		robotd->DriveSet(0.0,0.0);
	}
	void Autonomous::driveOverDefense(){
		robotd->driveDistance(60, .3);
		//robotd->turnRight(90);

	}
	bool Autonomous::attackTower(std::string position){
		//Angle/drive based on position
		return false;
	}
	void Autonomous::startTimer(){
		timer->Start();
	}
