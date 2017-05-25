/*
 * dsf_UART_OCP.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */
//#include <stdint.h>
#include "dsf_UART_OCP.h"
using namespace std;

#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)

dsf_UART_OCP::dsf_UART_OCP()
{

} // end dsf_UART_OCP constructor

dsf_UART_OCP::~dsf_UART_OCP()

{

} // end dsf_UART_OCP destructor

void dsf_UART_OCP::BindPeripheral(OCP ocp) const
{
	if(ocp == dsf_UART0 || ocp == dsf_UART1 || ocp == dsf_UART2 )
	{
		this->ocp = ocp;
	}
	else
	{
		//System(0);
	}
} // end function BindPeripheral

/*
void dsf_UART_OCP::BindPin(int pin) const
{

} // end function BindPin
 */

void dsf_UART_OCP::Initialize() const
{
	if(this->ocp == dsf_UART0)
	{
		CLOCK_EnableClock(kCLOCK_PortB); /* Port B Clock Gate Control: Clock enabled */
		PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3); /* PORTB16 (pin 62) is configured as UART0_RX */
		PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3); /* PORTB17 (pin 63) is configured as UART0_TX */
		SIM->SOPT5 = ((SIM->SOPT5 &
				(~(SIM_SOPT5_UART0TXSRC_MASK))) /* Mask bits to zero which are setting */
				| SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX) /* UART 0 transmit data source select: UART0_TX pin */
		);

	    BOARD_BootClockRUN();

	    /* Calculate the baud rate modulo divisor */
	   this->baudRateModuloDivisor = DEMO_UART_CLK_FREQ / (this->boudRate * 16);

	}
	else if (this->ocp == dsf_UART1)
	{
		//TODO
	}
	else
	{
		//TODO
	}
} // end function Initialize

void dsf_UART_OCP::SetAddrSlave(t_Byte addr)
{

} // end function SetAddrSlave

void dsf_UART_OCP::SetFrame(t_Byte LenData, t_parity Parity, t_stop stop)
{

} // end function SetFrame

void dsf_UART_OCP::SetBaudRate(uint32_t rate)
{
	this->boudRate = rate;
} // end function SetBaudRate

void dsf_UART_OCP::SendData(t_Byte data)
{

} // end function SendData

int dsf_UART_OCP::ReceiveData()
{

} // end function ReceiveData

void dsf_UART_OCP::SendDataTo(t_Byte data, int addr)
{

} // end function SendDataTo

t_Byte dsf_UART_OCP::ReceiveDataAny(int *addr)
{

} // end function ReceiveDataAny

void dsf_UART_OCP::ClearPeripheral()
{

} // end function ClearPeripheral

void dsf_UART_OCP::CancelSend()
{

} // end function CancelSend

void dsf_UART_OCP::ResetPeripheral()
{

} // end function ResetPeripheral

void dsf_UART_OCP::WaitComm(t_Comm comm)
{

} // end function WaitComm

void dsf_UART_OCP::SetExceptionHandle(t_Except e)
{

} // end function SetExceptionHandle
