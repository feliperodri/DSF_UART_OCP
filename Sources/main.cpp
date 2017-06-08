#include"dsf_UART_OCP.h"
#include<assert.h>

dsf_UART_OCP uart;

/*
extern "C" {
	void UART0_IRQHandler(){
		//handle interruption
	}
}
 */

void setup(){
	uart.BindPeripheral(dsf_UART3);
	uart.BindChannel(dsf_PORTB);
	//uart.SetFrame(8,dsf_None,dsf_One);
	uart.SetBaudRate(9600);
	uart.Initialize();
}

void main(){
	uint8_t data;
	uint8_t receptor;
	data = 'F';

	setup();

	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE_PCR26 |= PORT_PCR_MUX(1);
	GPIOE_PDDR |= 1<<26;
	GPIOE_PSOR |= 1<<26;

	while(true)
	{
		// Transfer data
		uart.WaitComm(dsf_Tx);
		uart.SendData(data);

		// Receive data
		uart.WaitComm(dsf_Rx);
		uart.ReceiveData(&receptor);

		// Check if transfer was successful
		assert(receptor == 'F');

		if(receptor == 'F')
			GPIOE_PCOR |= 1<<26;
	}
} //EOF
