#include"../Includes/dsf_UART_OCP.h"

dsf_UART_OCP uart;

void setup(){
	uart.bindPeripheral(dsf_UART3);
	uart.bindChannel(dsf_PORTB);
	uart.setFrame(dsf_8bit,dsf_None,dsf_One);
	uart.setBaudRate(9600);
	uart.initializePeripheral();
}

int main(){
	uint16_t data = 0xFF;
	uint16_t receptor = 0;

	setup();

	/*setup led*/
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE_PCR26 |= PORT_PCR_MUX(1);
	GPIOE_PDDR |= 1<<26;
	GPIOE_PSOR |= 1<<26;

	while(true)
	{
		// Receive data
		uart.waitDataAvaliable();
		receptor = uart.receiveData();

		if(receptor == '1')
		{
			GPIOE_PSOR &= ~(1<<26);
			GPIOE_PCOR |= 1<<26;
		}
		else if(receptor == '2')
		{
			GPIOE_PCOR &= ~(1<<26);
			GPIOE_PSOR |= 1<<26;
		}
		else
		{
			receptor = 0;
		}
	}

	return 0;
} //EOF
