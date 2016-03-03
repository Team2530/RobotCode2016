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
	const std::string autoNamedN = "Do Nothing";
	const std::string autoNameLeft = "Left Low Goal";
	const std::string autoNameRight = "Right Low Goal";
	const std::string autoNameOver= "Drive Over Defense";
	std::string autoSelected;



	Camera *camera;
	Autonomous *autonomous;
	DriveTrain *Drive;







	void RobotInit(){


		Drive= new DriveTrain();
		chooser = new SendableChooser();
		chooser->AddObject(autoNamedN, (void*)&autoNamedN);
		chooser->AddObject(autoNameLeft, (void*)&autoNameLeft);
		chooser->AddObject(autoNameRight, (void*)&autoNameRight);
		chooser->AddObject(autoNameOver, (void*)&autoNameOver);
		SmartDashboard::PutData("Auto Modes", chooser);


		camera = new Camera();
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
		autonomous = new Autonomous(Drive, *((std::string*)chooser->GetSelected()));

		Drive->AutonomousInit();
		autonomous->startTimer();

	}

	void AutonomousPeriodic(){
			//autonomous->driveOverDefense();
		SmartDashboard::PutString("selected", autoSelected);

	}

	void TeleopInit(){
		Drive->TeleopInit();
	}

	void TeleopPeriodic(){
		Drive->Drive();
		camera->cameraTeleop();
	}

	void TestPeriodic(){
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
