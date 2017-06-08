/*
 * dsf_UART_OCP.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#include "dsf_UART_OCP.h"
using namespace std;

#define DEMO_UART_CLK_FREQ CLOCK_GetFreq(UART0_CLK_SRC)

dsf_UART_OCP::dsf_UART_OCP()
{
	this->baudRateModuloDivisor = 0x0;
	this->boudRate = 0x0;
} // end dsf_UART_OCP constructor

void dsf_UART_OCP::BindPeripheral(OCP_t ocp)
{
	if(ocp == dsf_UART1 || ocp == dsf_UART2 || ocp == dsf_UART3)
	{
		this->ocp = ocp;
	}
	else
	{
		//TODO
	}
} // end function BindPeripheral


void dsf_UART_OCP::BindChannel(Port_t port)
{
	if(this->ocp == dsf_UART3 && ((port == dsf_PORTB) || (port == dsf_PORTC))){
		this->port = port;
	} else {
		//ERROR MESSAGE
	}

} // end function BindPin


void dsf_UART_OCP::Initialize()
{
	if(this->ocp == dsf_UART1)
	{
		//TODO
	}
	else if (this->ocp == dsf_UART2)
	{
		//TODO
	}
	else
	{
		SIM_SCGC4 |= SIM_SCGC4_UART3_MASK; /*Enable the UART clock*/

		if(this->port == dsf_PORTB)
		{
			SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable the PORTB clock*/
			PORTB_PCR10 |= PORT_PCR_MUX(3); /*Select alternative 3 for RX*/
			PORTB_PCR11 |= PORT_PCR_MUX(3); /*Select alternative 3 for TX*/
		} else {
			SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; /*Enable the PORTC clock*/
			PORTC_PCR16 |= PORT_PCR_MUX(3); /*Select alternative 3 for RX*/
			PORTB_PCR17 |= PORT_PCR_MUX(3); /*Select alternative 3 for TX*/
		}

		UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /*Unable RX and TX for register 2*/
		UART3_C1 = 0; /*Set default configuration for register 1 */

		this->baudRateModuloDivisor = (uint16_t)((21000*1000)/(this->boudRate * 16)); /* Calculate baud settings */
		UART3_BDH = (UART3_BDH & ~(UART_BDH_SBR(0x1F))) | (((this->baudRateModuloDivisor & 0x1F00) >> 8));
		UART3_BDL = (uint8_t)(this->baudRateModuloDivisor & UART_BDL_SBR_MASK);

		UART3_C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter*/
	}
} // end function Initialize

void dsf_UART_OCP::SetFrame(uint8_t LenData, Parity_t parity, Stop_t stop)
{
	//TODO
} // end function SetFrame

void dsf_UART_OCP::SetBaudRate(uint32_t rate)
{
	this->boudRate = rate;
} // end function SetBaudRate

void dsf_UART_OCP::SendData(uint8_t data) /* Send the character */
{
	if(this->ocp == dsf_UART3){
		UART3_D = data;
	}
} // end function SendData

void dsf_UART_OCP::ReceiveData(uint8_t *data) /* Return the 8-bit data from the receiver */
{
	if(this->ocp == dsf_UART3){
		*data = UART3_D;
	}
} // end function ReceiveData

void dsf_UART_OCP::ClearPeripheral()
{
	this->ocp = dsf_NULL; // null
} // end function ClearPeripheral

void dsf_UART_OCP::CancelSend()
{

} // end function CancelSend

void dsf_UART_OCP::ResetPeripheral()
{

} // end function ResetPeripheral

void dsf_UART_OCP::WaitComm(Comm_t comm)
{
	if(comm == dsf_Tx)  /* Wait until space is available in the FIFO */
	{
		if(this->ocp == dsf_UART3)
		{
			while(!(UART3_S1 & UART_S1_TDRE_MASK));
		}
	}
	else /* Wait until character has been received */
	{
		if(this->ocp == dsf_UART3)
		{
			while (!(UART3_S1 & UART_S1_RDRF_MASK));
		}

	}
} // end function WaitComm
