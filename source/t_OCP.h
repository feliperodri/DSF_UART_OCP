/*
 * t_OCP.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_T_OCP_H_
#define SOURCE_T_OCP_H_

class t_OCP
{
public:
	virtual void BindPeripheral(t_OCP ocp) const = 0;
	virtual void BindPin(int pin) const = 0;
	virtual void Initialize() const = 0;
}; //end class t_OCP

#endif /* SOURCE_T_OCP_H_ */
