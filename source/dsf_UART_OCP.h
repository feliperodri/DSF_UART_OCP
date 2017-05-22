/*
 * dsf_UART_OCP.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_DSF_UART_OCP_H_
#define SOURCE_DSF_UART_OCP_H_

#include "OCP.h"

class dsf_UART_OCP : public OCP
{
public:
	dsf_UART_OCP();
	virtual ~dsf_UART_OCP();
	virtual void BindPeripheral(t_OCP ocp) const;
	virtual void BindPin(int pin) const;
	virtual void Initialize() const;
	void SetAddrSlave(t_Byte addr);
	void SetFrame(t_Byte LenData, t_parity Parity, t_stop stop);
	void SetBaudRate(int rate);
	void SendData(t_Byte data);
	int ReceiveData();
	void SendDataTo(t_Byte data, int addr);
	t_Byte ReceiveDataAny(int *addr);
	void ClearPeripheral();
	void CancelSend();
	void ResetPeripheral();
	void WaitComm(t_Comm comm);
	void SetExceptionHandle(t_Except e);
private:
	//parameters
}; // end class dsf_UART_OCP

#endif /* SOURCE_DSF_UART_OCP_H_ */
