#include "WPILib.h"
#include "DriveTrain.h"
#include "Autonomous.h"
#include "Shooter.h"
#include "AHRS.h"
#include "Camera.h"



/*
 * MAIN CLASS FOR DRIVING ROBOT
 * ALL FUNCTIONS ARE INHERITED
 * IMPLEMENTS ITERATIVEROBOT INTERFACE
 * INCLUDES ALL OTHER OBJECTS
 */


class Robot: public IterativeRobot{
private:

	/*declare string constants for sendable chooser and auto modes
	 * add pointers for necessary auto/telop objects
	 */
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	SendableChooser *chooser2;
	const std::string DoNothing = "Do Nothing";
	const std::string autoNameLeft = "Left Low Goal";
	const std::string autoNameRight = "Right Low Goal";
	const std::string autoNameOver= "Drive Over Defense";
	const std::string autoNameP1= "P1 High";
	const std::string autoNameP2= "P2 High";
	const std::string autoNameP3= "P3 High";
	const std::string autoNameP4= "P4 High";
	const std::string autoNameP5= "P5 High";
	const std::string autoNameRW= "Rock Wall or Moat";
	std::string autoSelected;
	std::string testSelected;

	Autonomous *autonomous;
	DriveTrain *Drive;
	const std::string autoNameTest1= "right turn Test";
	const std::string autoNameTest2= "left turn Test";
	const std::string autoNameTest3= "drive distance test";
	const std::string autoNameTest4= "angle ball test";



	/*Initializes objects necessary for teleop
	 * Adds options to sendable chooser on SmartDashboard
	 */
	void RobotInit(){
		/*if (fork()==0){
			system("/home/lvuser/start_vision &");
		}*/

		//creates DriveTrain and sendable choosers
		Drive= new DriveTrain();
		chooser = new SendableChooser();
		chooser2 = new SendableChooser();


		//adds options to both
		chooser->AddDefault(DoNothing, (void*)&DoNothing);
		chooser->AddObject(autoNameLeft, (void*)&autoNameLeft);
		chooser->AddObject(autoNameRight, (void*)&autoNameRight);
		chooser->AddObject(autoNameOver, (void*)&autoNameOver);
		chooser->AddObject(autoNameP1, (void*)&autoNameP1);
		chooser->AddObject(autoNameP2, (void*)&autoNameP2);
		chooser->AddObject(autoNameP3, (void*)&autoNameP3);
		chooser->AddObject(autoNameP4, (void*)&autoNameP4);
		chooser->AddObject(autoNameP5, (void*)&autoNameP5);
		chooser->AddObject(autoNameRW, (void*)&autoNameRW);
		SmartDashboard::PutData("Auto Modes", chooser);


		chooser2->AddDefault(autoNameTest1, (void*)&autoNameTest1);
		chooser2->AddObject(autoNameTest2, (void*)&autoNameTest2);
		chooser2->AddObject(autoNameTest3, (void*)&autoNameTest3);
		chooser2->AddObject(autoNameTest4, (void*)&autoNameTest4);
		SmartDashboard::PutData("Auto Modes 2", chooser2);
		Drive->AutonomousInit();
		autonomous = new Autonomous(Drive, *((std::string*)chooser->GetSelected()));

		//passes driveTrain and sendable chooser option to Autonomous class and creates it!

	}



	void AutonomousInit(){
		autonomous->setSelected(*((std::string*)chooser->GetSelected()));
		//autoSelected = SmartDashboard::GetString("Auto Selector", *((std::string*)chooser->GetSelected()));
		autoSelected = *((std::string*)chooser->GetSelected());
		//testSelected= SmartDashboard::GetString("Auto Selector", *((std::string*)chooser2->GetSelected()));
		testSelected = *((std::string*)chooser2->GetSelected());

		Drive->AutonomousInit();
		autonomous->startTimer();
		autonomous->reset();

	}

	/*
	 * Checks if the string from the Auto Modes meets any of the constants above. If so, it runs that Auto Mode.
	 * Right now has testing modes, but autonomous->driveOverDefense(); will do the checking for us.
	 */
	void AutonomousPeriodic(){
		autonomous->driveOverDefense();
		const double kModesEqual=0;
		//autonomous->test();
		SmartDashboard::PutString("Auto Selected", autoSelected);
		if (autoSelected.compare(DoNothing)==kModesEqual){
			autonomous->doNothing();
			SmartDashboard::PutString("DN TEST", "Done");
		}
		else if (autoSelected.compare("Drive Over Defense")==kModesEqual){
			autonomous->driveOverDefense();

		}
		else if (autoSelected.compare(autoNameRW)==kModesEqual){

			autonomous->rockWallOrMoat();
		}
		else if (autoSelected.compare(autoNameLeft)==kModesEqual){


			autonomous->leftLowGoal();
		}
		else if (autoSelected.compare(autoNameRight)==kModesEqual){

			autonomous->rightLowGoal();

		}
		else if (autoSelected.compare(autoNameP1)==kModesEqual){

			autonomous->p1High();
		}

		else if (autoSelected.compare(autoNameP2)==kModesEqual){

			autonomous->p2High();
		}

		else if (autoSelected.compare(autoNameP3)==kModesEqual){

			autonomous->p3High();
		}
		else if (autoSelected.compare(autoNameP4)==kModesEqual){

			autonomous->p4High();
		}


		else if (autoSelected.compare(autoNameP5)==kModesEqual){
			autonomous->p5High();

		}


	}

	/*
	 * resets encoders, step, navX, and starts the spike relay
	 */
	void TeleopInit(){
		Drive->TeleopInit();
		autonomous->reset();
	}

	//completes all necessary functions for teleop driving/operating
	void TeleopPeriodic(){
		Drive->Drive();

	}

	//This is not used.
	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
