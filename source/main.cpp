/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

//#include "board.h"
//#include "pin_mux.h"
//#include "clock_config.h"
#include"dsf_UART_OCP.h"
/*!
 * @brief Application entry point.
 */
t_Byte dado;
dsf_UART_OCP uart;

volatile void rot_exc(t_Except e){
	//handle "e" exception
}

void setup(){
	uart.BindPheripheral(dsf_UART0);
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
	// Transmissão de dados
	//uart.SendData(dado);
	//uart.WaitComm(dsf_Tx);
	// Recepção de dados
	//uart.WaitComm (dsf_Rx);
	//dado = uart.ReceiveData();

	put("\r\nSerial code example\r\n");

	//while(1) {
		dado = uart.ReceiveData();
		uart.SendData(dado);
		//BLUE_TOGGLE;
	//}
}
