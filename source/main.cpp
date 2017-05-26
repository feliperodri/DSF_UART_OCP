#include "dsf_UART_OCP.h"

t_Byte dado;
dsf_UART_OCP uart;

void rot_exc(t_Exception e){
	//handle "e" exception
}

void setup(){
	uart.BindPeripheral(dsf_UART0);
	uart.SetBaudRate(9600);
	//uart.SetExceptionHandle(rot_exc);
	uart.Initialize();
}

void put(char *ptr_str)
{
	while(*ptr_str)
		uart.SendData(*ptr_str++);
}

int main(void)
{
	setup();

	put("\r\nExample\r\n");

	//while(1) {
	dado = uart.ReceiveData();
	uart.SendData(dado);
	//BLUE_TOGGLE;
	//}
	return 0;
}
