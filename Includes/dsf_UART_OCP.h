/*
 * dsf_UART_OCP.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro, Francisco Félix, Maildo Lopes, and Vinícius Souza
 */

#ifndef SOURCE_DSF_UART_OCP_H_
#define SOURCE_DSF_UART_OCP_H_

#include "MK64F12.h"
#include "dsf_K64F.h"

class dsf_UART_OCP : public dsf_K64F_ocp
{
public:
	dsf_UART_OCP();
	void bindPeripheral(OCP_t ocp) override;
	void initializePeripheral() override;
	void bindChannel(Pin_t port);
	void setFrame(LenghtData_t length_data, Parity_t parity, StopBit_t stop);
	void setBaudRate(uint32_t rate);
	void sendData(uint16_t data);
	uint16_t receiveData();
	void clearPeripheral();
	void cancelSend();
	void waitDataTransfer();
	Exception_t waitDataAvaliable();
	bool startBitAvaliable();

private:
	OCP_t ocp;
	Pin_t port;
	LenghtData_t lengthData;
	Parity_t parity;
	StopBit_t stop;
	uint16_t baudRateModuloDivisor;
	uint32_t boudRate;
}; // end class dsf_UART_OCP

#endif /* SOURCE_DSF_UART_OCP_H_ */
