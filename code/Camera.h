/*
 * Camera.h
 *
 *  Created on: Feb 29, 2016
 *      Author: Owner
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
#include "WPILib.h"
#include <unistd.h>
#include <stdio.h>
#include "AHRS.h"
#include <iostream>//experimental GRIP stuff
// for the two included above, they were added by the GRIP to C++ code. Are the familiar with them?
// do we have them or are they something that we need to get?
/** real-time display of navX-MXP values
 * operatorControl() method is where data is retrieved
 * and output to SmartDashboard. they include:
 * yaw, pitch, and roll angles, linear acceleration data, motion indicators
 * compass heading and 9-axis fused heading (requires Magnetometer calibration
 * estimated velocity and displacement, quaternion Data
 * raw gyro, accelermeter and magnetometer data
 * board information can be used for debugging
 * connectivity issues after installation of navX-MXP sensor
 * all of the above are implemented but some are commented out due to necessity
 */
	//GRIP to C++ and navx data monitor


class Camera {
	std::shared_ptr<NetworkTable> table;
	int autoLoopCounter;
	std::vector<double> widths;
	std::vector<double> areas;
	std::vector<double> centerXs;
	std::vector<double> heights;
	double focalLength;

	double kConstantDistance=162;
	double kActualHeight =12;
	double kConstantPixelHeight=37;
	float kMaxArea=0;
    int kMaxAreaIndex =-1;
   	int kI=0;
   	int kContoursIndexCheck=-1;
   	int kHeightWidth=0;
   	int kError= -2;
   	double kAngleError= 999;
   	double kHalfPixelWidth= 160;
   	double kRootConstant= 3;
   	double kConstantConfusingNumber= 57.29577951;

public:

	Camera();
	int getTargetIndex(std::vector<double>);
	double getTargetWidth(int);
	double getTargetCenterX(int);
	double getTargetDistance(std::vector<double>);
	double getTargetAngle(int);
	void cameraTeleop();
	double getDis();
	double getAng();
	double getTargetHeight(int);
};



#endif /* SRC_CAMERA_H_ */
