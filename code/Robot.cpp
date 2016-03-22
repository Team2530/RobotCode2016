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
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	SendableChooser *chooser2;
	const std::string autoNamedN = "Do Nothing";
	const std::string autoNameLeft = "Left Low Goal";
	const std::string autoNameRight = "Right Low Goal";
	const std::string autoNameOver= "Drive Over Defense";
	const std::string autoNameP1= "P1 High";
	const std::string autoNameP2= "P2 High";
	const std::string autoNameP3= "P3 High";
	const std::string autoNameP4= "P4 High";
	const std::string autoNameP5= "P5 High";
	std::string autoSelected;

	Autonomous *autonomous;
	DriveTrain *Drive;
	const std::string autoNameTest1= "test 1";
	const std::string autoNameTest2= "test 2";

	void RobotInit(){
		/*if (fork()==0){
			system("/home/lvuser/start_vision &");
		}*/

		Drive= new DriveTrain();
		chooser = new SendableChooser();
		chooser2 = new SendableChooser();
		chooser->AddDefault(autoNamedN, (void*)&autoNamedN);
		chooser->AddObject(autoNameLeft, (void*)&autoNameLeft);
		chooser->AddObject(autoNameRight, (void*)&autoNameRight);
		chooser->AddObject(autoNameOver, (void*)&autoNameOver);
		chooser->AddObject(autoNameP1, (void*)&autoNameP1);
		chooser->AddObject(autoNameP2, (void*)&autoNameP2);
		chooser->AddObject(autoNameP3, (void*)&autoNameP3);
		chooser->AddObject(autoNameP4, (void*)&autoNameP4);
		chooser->AddObject(autoNameP5, (void*)&autoNameP5);
		SmartDashboard::PutData("Auto Modes", chooser);

		chooser2->AddDefault(autoNameTest1, (void*)&autoNameTest1);
		chooser2->AddObject(autoNameTest2, (void*)&autoNameTest2);
		SmartDashboard::PutData("Auto Modes 2", chooser2);
		autonomous = new Autonomous(Drive, *((std::string*)chooser->GetSelected()));
	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit(){
		autoSelected = SmartDashboard::GetString("Auto Selector", *((std::string*)chooser->GetSelected()));


		Drive->AutonomousInit();
		autonomous->startTimer();
		autonomous->reset();

	}

	void AutonomousPeriodic(){
			autonomous->driveOverDefense();
		//autonomous->test();
		SmartDashboard::PutString("selected", autoSelected);

	}

	void TeleopInit(){
		Drive->TeleopInit();
	}

	void TeleopPeriodic(){
		Drive->Drive();

	}

	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
