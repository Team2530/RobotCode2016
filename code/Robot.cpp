#include "WPILib.h"
#include "DriveTrain.h"
#include "Autonomous.h"
#include "Camera.h"
#include "Shooter.h"
#include "AHRS.h"

class Robot: public IterativeRobot{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;


	Autonomous *autonomous;
	DriveTrain *Drive;



	int step=0;



	void RobotInit(){


		Drive= new DriveTrain();
		SmartDashboard::PutNumber("Proportional", 0);
		SmartDashboard::PutNumber("Integral", 0);
		SmartDashboard::PutNumber("Derivative", 0);


		autonomous = new Autonomous(Drive);
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


		Drive->TeleopInit();
		autonomous->startTimer();

	}

	void AutonomousPeriodic(){
			autonomous->driveOverDefense();

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
