/*
 * Camera.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Owner
 */

#include <Camera.h>

/*
 * creates Network table and focal length variable
 */
Camera::Camera() {
	table = NetworkTable::GetTable("GRIP/myContoursReport");
	focalLength =kConstantDistance*kConstantPixelHeight/kActualHeight;

}

//goes through the area vectors to find the biggest targetIndex
int Camera::getTargetIndex(std::vector<double> areas)
{

	float maxArea = kMaxArea;
	int maxAreaIndex = kMaxAreaIndex;
	int i = kI;

	for( auto area : areas){
		if(area > maxArea){
			maxArea = area;
			maxAreaIndex = i;
		}
		i++;
	}
	return maxAreaIndex;


}

//finds width of the target.
double Camera::getTargetWidth(int contoursIndex){
	SmartDashboard::PutNumber("Check1", 1);
	SmartDashboard::PutNumber("Width", widths [contoursIndex]);
	return widths [contoursIndex];
}

//finds height of the target.
double Camera::getTargetHeight(int contoursIndex){
	SmartDashboard::PutNumber("Check3", 1);
	SmartDashboard::PutNumber("Height", heights [contoursIndex]);
	return heights [contoursIndex];
}

//finds the center of the target.
double Camera::getTargetCenterX(int contoursIndex){
	SmartDashboard::PutNumber("CenterX", centerXs [contoursIndex]);
	double centerX = centerXs [contoursIndex];
	return centerX;
}

//finds the distance away from the target laterally.
double Camera::getTargetDistance(std::vector<double> areas){
	//gets the target distance of the best area
	SmartDashboard::PutNumber("Check2", 2);
	int contoursIndex = getTargetIndex(areas);
	if (contoursIndex == kContoursIndexCheck){
		return kContoursIndexCheck;
	}
	double width = getTargetWidth(contoursIndex);
	double height = getTargetHeight(contoursIndex);
	if (width <= kHeightWidth || height<=0.1){
		return kError;
	}
	//double x =(1.96078 * height) - (.9802*sqrt((6.04242*height *height)-(width*width)));
	//height = height-x;
	double TargetDistance = kActualHeight*focalLength/height;
	return TargetDistance;

}

//finds the lateral angle away from the target
double Camera::getTargetAngle( int contoursIndex){
	if (contoursIndex == kContoursIndexCheck){
		return kAngleError;
	}
	double centerX = getTargetCenterX(contoursIndex);
	double TargetAngle = (atan((centerX-kHalfPixelWidth)/(kHalfPixelWidth * sqrt(kRootConstant)))) * kConstantConfusingNumber; //error from left side
	return TargetAngle;
}

//publishes distance/angle to SmartDashboard
void Camera::cameraTeleop(){

	widths = table->GetNumberArray("width", llvm::ArrayRef<double>());
	heights= table->GetNumberArray("height", llvm::ArrayRef<double>());
	areas = table->GetNumberArray("area", llvm::ArrayRef<double>());
	centerXs = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	if (widths.size()==heights.size()&&widths.size()==areas.size()&&widths.size()==centerXs.size()){
		int contoursIndex = getTargetIndex(areas);
		SmartDashboard::PutNumber("contourIndex", contoursIndex);
		if (getTargetDistance(areas)!=kMaxAreaIndex){
			SmartDashboard::PutNumber("Distance", getTargetDistance(areas));
		}
		if (getTargetAngle(contoursIndex)!=kAngleError){
			SmartDashboard::PutNumber("TargetAngle", getTargetAngle(contoursIndex));
		}
	}
}

//used for getting the distance in other classes
double Camera::getDis(){
	return getTargetDistance(areas);
}

//used for getting the angle in other classes
double Camera::getAng(){
	int contoursIndex = getTargetIndex(areas);
	return getTargetAngle(contoursIndex);
}
