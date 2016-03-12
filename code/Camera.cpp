/*
 * Camera.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Owner
 */

#include <Camera.h>

Camera::Camera() {
	table = NetworkTable::GetTable("GRIP/myContoursReport");
	focalLength =kConstantDistance*kConstantPixelHeight/kActualHeight;

}
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

double Camera::getTargetWidth(int contoursIndex){
	SmartDashboard::PutNumber("Check1", 1);
	SmartDashboard::PutNumber("Width", widths [contoursIndex]);
	return widths [contoursIndex];
}

double Camera::getTargetHeight(int contoursIndex){
	SmartDashboard::PutNumber("Check3", 1);
	SmartDashboard::PutNumber("Height", heights [contoursIndex]);
	return heights [contoursIndex];
}

double Camera::getTargetCenterX(int contoursIndex){
	SmartDashboard::PutNumber("CenterX", centerXs [contoursIndex]);
	double centerX = centerXs [contoursIndex];
	return centerX;
}

double Camera::getTargetDistance(std::vector<double> areas){
	//gets the target distance of the best area
		SmartDashboard::PutNumber("Check2", 2);
		int contoursIndex = getTargetIndex(areas);
		if (contoursIndex == kContoursIndexCheck){
			return kContoursIndexCheck;
		}
		double width = getTargetWidth(contoursIndex);
		double height = getTargetHeight(contoursIndex);
		if (width <= kHeightWidth || height<=0){
			return kError;
		}
		//double x =(1.96078 * height) - (.9802*sqrt((6.04242*height *height)-(width*width)));
		//height = height-x;
		double TargetDistance = kActualHeight*focalLength/height;
		return TargetDistance;

}

double Camera::getTargetAngle( int contoursIndex){
		if (contoursIndex == kContoursIndexCheck){
				return kAngleError;
		}
		double centerX = getTargetCenterX(contoursIndex);
		double TargetAngle = (atan((centerX-kHalfPixelWidth)/(kHalfPixelWidth * sqrt(kRootConstant)))) * kConstantConfusingNumber; //error from left side
		return TargetAngle;
}

void Camera::cameraTeleop(){

		widths = table->GetNumberArray("width", llvm::ArrayRef<double>());
		heights= table->GetNumberArray("height", llvm::ArrayRef<double>());
		areas = table->GetNumberArray("area", llvm::ArrayRef<double>());
		centerXs = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
		int contoursIndex = getTargetIndex(areas);
		SmartDashboard::PutNumber("contourIndex", contoursIndex);
		if (getTargetDistance(areas)!=kMaxAreaIndex){
		SmartDashboard::PutNumber("Distance", getTargetDistance(areas));
		}
		if (getTargetAngle(contoursIndex)!=kAngleError){
		SmartDashboard::PutNumber("TargetAngle", getTargetAngle(contoursIndex));
		}

}

double Camera::getDis(){
	return getTargetDistance(areas);
}

double Camera::getAng(){
	int contoursIndex = getTargetIndex(areas);
	return getTargetAngle(contoursIndex);
}
