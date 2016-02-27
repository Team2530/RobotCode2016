/*
 * ControllerConstants.h
 *
 *  Created on: Feb 20, 2016
 *      Author: Owner
 */
#include "WPILib.h"
#ifndef SRC_CONTROLLERCONSTANTS_H_
#define SRC_CONTROLLERCONSTANTS_H_

class ControllerConstants{
public:
	//raw values for buttons
    enum xBoxButtonMap {
         kAbutton=1,
		 kBbutton=2,
		 kXbutton=3,
		 kYbutton=4,
		 kLBbutton=5,
         kRBbutton=6,
         kLSbutton=9,
		 kRSbutton=10,
		 kBackbutton=7,
		 kStartbutton=8,
    };
    // raw values for axes
    enum xBoxAxisMap{
    	kLSXAxis= 0,
		kLSYAxis= 1,
		kLTAxis= 2,
		kRTAxis= 3,
		kRSXAxis= 4,
		kRSYAxis= 5,
    };

};




#endif /* SRC_CONTROLLERCONSTANTS_H_ */
