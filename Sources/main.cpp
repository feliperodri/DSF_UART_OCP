#include"../Includes/dsf_UART_OCP.h"
#include<assert.h>

dsf_UART_OCP uart;

void setup(){
	uart.bindPeripheral(dsf_UART3);
	uart.setFrame(dsf_8bit,dsf_None,dsf_One, dsf_LSB);
	uart.setBaudRate(9600);
	uart.initializePeripheral();
}

int main(){
	uint16_t data;
	uint16_t receptor = 0;
	data = 'a';

	setup();

	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE_PCR26 |= PORT_PCR_MUX(1);
	GPIOE_PDDR |= 1<<26;
	GPIOE_PSOR |= 1<<26;

	while(true)
	{
		/* Transfer data */
		uart.waitDataTransfer();
		uart.sendData(data);

		/* Receive data */
		uart.waitDataAvaliable();
		receptor = uart.receiveData();

		if(data == receptor)
		{
			GPIOE_PSOR &= ~(1<<26);
			GPIOE_PCOR |= 1<<26;
		}
	}
	return 0;
} //EOF
