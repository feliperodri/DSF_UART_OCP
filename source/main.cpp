/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

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
	//uart.BindPin(16);
	//uart.SetAddrSlave(1);
	//uart.SetFrame(7, dsf_odd, dsf_two);
	uart.SetBaudRate(9600);
	//uart.SetExceptionHandle(rot_exc);
	uart.Initialize();
}

int main(void) {
	/* Init board hardware. */
	//BOARD_InitPins();
	//BOARD_BootClockRUN();

	setup();
	// Transmissão de dados
	uart.SendData(dado);
	uart.WaitComm(dsf_Tx);
	// Recepção de dados
	uart.WaitComm (dsf_Rx);
	dado = uart.ReceiveData();

	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}
