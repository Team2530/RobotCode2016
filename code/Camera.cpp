/*
 * Camera.cpp
 *
 *  Created on: Feb 29, 2016
 *      Author: Owner
 */

#include <Camera.h>

Camera::Camera() {
	table = NetworkTable::GetTable("GRIP/myContoursReport");

}
int Camera::getTargetIndex(std::vector<double> areas)
{

	float maxArea = 0;
	int maxAreaIndex = -1;
	int i = 0;

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

double Camera::getTargetCenterX(int contoursIndex){
	SmartDashboard::PutNumber("CenterX", centerXs [contoursIndex]);
	double centerX = centerXs [contoursIndex];
	return centerX;
}

double Camera::getTargetDistance(std::vector<double> areas){
	//gets the target distance of the best area
		SmartDashboard::PutNumber("Check2", 2);
		int contoursIndex = getTargetIndex(areas);
		if (contoursIndex == -1){
			return -1;
		}
		double width = getTargetWidth(contoursIndex);
		if (width <= 0){
			return -2;
		}
		double TargetDistance = 5392.41526 / width;
		return TargetDistance;

}

double Camera::getTargetAngle( int contoursIndex){
		if (contoursIndex == -1){
				return 999;
		}
		double centerX = getTargetCenterX(contoursIndex);
		double TargetAngle = (atan((centerX-160)/(160 * sqrt(3)))) * 57.29577951; //error from left side
		return TargetAngle;
}

void Camera::cameraTeleop(){

		widths = table->GetNumberArray("width", llvm::ArrayRef<double>());
		areas = table->GetNumberArray("area", llvm::ArrayRef<double>());
		centerXs = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
		int contoursIndex = getTargetIndex(areas);
		SmartDashboard::PutNumber("Distance", getTargetDistance(areas));
		SmartDashboard::PutNumber("TargetAngle", getTargetAngle(contoursIndex));
}

double Camera::getDis(){
	return getTargetDistance(areas);
}

double Camera::getAng(){
	int contoursIndex = getTargetIndex(areas);
	return getTargetAngle(contoursIndex);
}
