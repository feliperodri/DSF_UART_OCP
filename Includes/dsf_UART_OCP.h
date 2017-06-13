/*
 * dsf_UART_OCP.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_DSF_UART_OCP_H_
#define SOURCE_DSF_UART_OCP_H_

#include "MK64F12.h"
#include "OCP.h"

class dsf_UART_OCP : public OCP
{
public:
	dsf_UART_OCP();
	void BindPeripheral(OCP_t ocp) override;
	void Initialize() override;
	void BindChannel(Port_t port);
	void SetFrame(uint8_t lengthData, Parity_t parity, Stop_t stop);
	void SetBaudRate(uint32_t rate);
	void SendData(uint8_t data);
	void ReceiveData(uint8_t *data);
	void ClearPeripheral();
	void CancelSend();
	void ResetPeripheral();
	void WaitComm(Comm_t comm);
	//void dsf_UART_OCP::SetAddrSlave(t_Byte addr);
	//void SendDataTo(uint8_t data, int addr);
	//uint8_t ReceiveDataAny(int *addr);
	//void SetExceptionHandle(t_Exception e);
private:
	OCP_t ocp;
	Port_t port;
	uint8_t lengthData;
	Parity_t parity;
	Stop_t stop;
	uint16_t baudRateModuloDivisor;
	uint32_t boudRate; //o a
}; // end class dsf_UART_OCP

#endif /* SOURCE_DSF_UART_OCP_H_ */
