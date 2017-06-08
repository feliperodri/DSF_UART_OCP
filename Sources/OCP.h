/*
 * t_OCP.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_OCP_H_
#define SOURCE_OCP_H_

#include"../utilities/utils.h"

class OCP
{
public:
	virtual void BindPeripheral(t_OCP ocp) = 0;
	virtual void Initialize() = 0;
}; //end class OCP

#endif /* SOURCE_OCP_H_ */