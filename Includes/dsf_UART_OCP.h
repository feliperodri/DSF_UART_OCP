/*
 * dsf_K64F.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro, Francisco Félix, Maildo Lopes, Miguel Grimm and Vinícius Souza
 */

#ifndef SOURCE_DSF_UART_OCP_H_
#define SOURCE_DSF_UART_OCP_H_

#include "MK64F12.h"
#include "dsf_K64F.h"

typedef enum {dsf_PORTA = 0, dsf_PORTB, dsf_PORTC, dsf_PORTD, dsf_PORTE} Port_t;

class dsf_UART_OCP : public dsf_K64F_ocp
{
public:
	dsf_UART_OCP();
	void bindPeripheral(OCP_t ocp) override;
	void initializePeripheral() override;
	void enablePeripheral();
	void disablePeripheralAndSavePower();
	void setFrame(LenghtData_t length_data, Parity_t parity, StopBit_t stop, FistBit_t fistBit);
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
	volatile uint32_t * cUART_SimSCGC;
	volatile uint32_t * addressPortPCRtx;
	volatile uint32_t * addressPortPCRrx;
	volatile uint8_t * addressUARTxC1;
	volatile uint8_t * addressUARTxC2;
	volatile uint8_t * addressUARTxC3;
	volatile uint8_t * addressUARTxC4;
	volatile uint8_t * addressUARTx_BDH;
	volatile uint8_t * addressUARTx_BDL;
	volatile uint8_t * addressUARTxS1;
	volatile uint8_t * addressUARTxS2;
	uint32_t       	   clockEnablePort;
	uint32_t			UARTx;
	Port_t port;
	LenghtData_t lengthData;
	Parity_t parity;
	StopBit_t stop;
	FistBit_t fistBit;
	uint16_t baudRateModuloDivisor;
	uint32_t boudRate;
}; // end class dsf_UART_OCP

#endif /* SOURCE_DSF_UART_OCP_H_ */
