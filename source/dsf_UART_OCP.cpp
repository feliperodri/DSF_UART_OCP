/*
 * dsf_UART_OCP.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#include "dsf_UART_OCP.h"
#include "../../PiscaLedSemSuportes/Includes/MK64F12.h"
using namespace std;

#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)

dsf_UART_OCP::dsf_UART_OCP()
{
	//TODO
} // end dsf_UART_OCP constructor

dsf_UART_OCP::~dsf_UART_OCP()

{
	//TODO
} // end dsf_UART_OCP destructor

void dsf_UART_OCP::BindPeripheral(t_OCP ocp)
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

void dsf_UART_OCP::Initialize()
{
	if(this->ocp == dsf_UART0)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; /*Enable the UART clock*/
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable the PORTB clock*/
		PORTB_PCR16 |= PORT_PCR_MUX(3);
		PORTB_PCR17 |= PORT_PCR_MUX(3);
		UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /*Disable Tx and Rx*/
		UART0_C1 = 0; /*Default settings of the register*/
		this->baudRateModuloDivisor = (t_Word)((21000*1000)/(this->boudRate * 16)); /* Calculate baud settings */
		UART0_BDH = (UART0_BDH & ~(UART_BDH_SBR(0x1F))) | (((this->baudRateModuloDivisor & 0x1F00) >> 8));
		UART0_BDL = (t_Byte)(this->baudRateModuloDivisor & UART_BDL_SBR_MASK);
		UART0_C2 |=(UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter*/
#if 0
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
#endif
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

void dsf_UART_OCP::SetFrame(t_Byte LenData, t_Parity parity, t_Stop stop)
{

} // end function SetFrame

void dsf_UART_OCP::SetBaudRate(t_Dwword rate)
{
	this->boudRate = rate;
} // end function SetBaudRate

void dsf_UART_OCP::SendData(t_Byte data)
{
	this->WaitComm(dsf_Tx);
	UART0_D = (t_Byte)data; /* Send the character */
} // end function SendData

t_Byte dsf_UART_OCP::ReceiveData()
{
	this->WaitComm(dsf_Rx);
	return UART0_D; /* Return the 8-bit data from the receiver */
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
	if(comm == dsf_Tx)
	{
		while(!(UART0_S1 & UART_S1_TDRE_MASK)); /* Wait until space is available in the FIFO */
	}
	else
	{
		while (!(UART0_S1 & UART_S1_RDRF_MASK)); /* Wait until character has been received */
	}
} // end function WaitComm

void dsf_UART_OCP::SetExceptionHandle(t_Exception e)
{

} // end function SetExceptionHandle
