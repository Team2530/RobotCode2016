/*
 * Camera.h
 *
 *  Created on: Feb 3, 2016
 *      Authors: Eric and Jack
 */
#include "WPILib.h"
#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_



class Camera {
	AxisCamera *camera;
public:
	Camera();
	bool shouldWeShoot(Image*);
};


#endif /* SRC_CAMERA_H_ */
