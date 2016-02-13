/*
 * Camera.cpp
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */

#include <Camera.h>



Camera::Camera() {
	std::string x= "10.25.30.11";
	camera = new AxisCamera(x);

}
bool shouldWeShoot(Image* image){
	//scan image, see if we should shoot
	return false;
}
