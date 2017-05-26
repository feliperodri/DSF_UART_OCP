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
	~dsf_UART_OCP();
	void BindPeripheral(t_OCP ocp) override;
	void Initialize() override;
	void SetAddrSlave(t_Byte addr);
	void SetFrame(t_Byte LenData, t_Parity parity, t_Stop stop);
	void SetBaudRate(t_Dwword rate);
	void SendData(t_Byte data);
	t_Byte ReceiveData();
	void SendDataTo(t_Byte data, int addr);
	t_Byte ReceiveDataAny(int *addr);
	void ClearPeripheral();
	void CancelSend();
	void ResetPeripheral();
	void WaitComm(t_Comm comm);
	void SetExceptionHandle(t_Exception e);
private:
	t_OCP ocp;
	t_Word baudRateModuloDivisor;
	t_Dwword boudRate;
}; // end class dsf_UART_OCP

#endif /* SOURCE_DSF_UART_OCP_H_ */
