/*
 * dsf_UART_OCP.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro, Francisco Félix, Maildo Lopes, and Vinícius Souza
 */

#include "dsf_UART_OCP.h"
using namespace std;

dsf_UART_OCP::dsf_UART_OCP()
{
	this->baudRateModuloDivisor = 0x0;
	this->boudRate = 0x0;
} // end dsf_UART_OCP constructor

void dsf_UART_OCP::bindPeripheral(OCP_t ocp)
{
	if(ocp == dsf_UART3)
	{
		this->ocp = ocp;
	}
	else
	{
		//TODO
	}
} // end function bindPeripheral


void dsf_UART_OCP::bindChannel(Pin_t port)
{
	if(this->ocp == dsf_UART3 && ((port == dsf_PORTB) || (port == dsf_PORTC))){
		this->port = port;
	} else {
		//TODO
	}
} // end function bindChannel


void dsf_UART_OCP::initializePeripheral()
{
	if(this->ocp == dsf_UART3)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART3_MASK; /* Enable the UART clock */

		if(this->port == dsf_PORTB)
		{
			SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /* Enable the PORTB clock */
			PORTB_PCR10 |= PORT_PCR_MUX(3); /* Select alternative 3 for RX */
			PORTB_PCR11 |= PORT_PCR_MUX(3); /* Select alternative 3 for TX */
		} else {
			SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; /* Enable the PORTC clock */
			PORTC_PCR16 |= PORT_PCR_MUX(3); /* Select alternative 3 for RX */
			PORTB_PCR17 |= PORT_PCR_MUX(3); /* Select alternative 3 for TX */
		}

		/* Set frame configuration for register 1 */
		UART3_C1 = 0;

		/* Stop configuration */
		if(stop==dsf_One) /* 1-bit */
		{
			UART3_BDH &= ~UART_BDH_SBNS_MASK;
		}
		else /* 2-bit */
		{
			UART3_BDH |= UART_BDH_SBNS_MASK;
		}

		/* lengthData and parity configuration */
		if(parity == dsf_None) /* Parity off */
		{
			UART3_C1 &= ~UART_C1_PE_MASK;

			if(lengthData == dsf_8bit ) /* 8-bit */
			{
				UART3_C1 &= ~UART_C1_M_MASK;
			}
			else if(lengthData == dsf_9bit) /* 9-bit */
			{
				UART3_C1 |= UART_C1_M_MASK;
			}
			else
			{
				//TODO
			}
		}
		else /* Parity on */
		{
			UART3_C1 |= UART_C1_PE_MASK;

			if(lengthData == dsf_7bit )	/* 7-bit */
			{
				UART3_C1 &= ~UART_C1_M_MASK;
				UART3_C4 &=	~UART_C4_M10_MASK;
			}
			else if(lengthData == dsf_8bit) /* 8-bit */
			{
				UART3_C1 |=  UART_C1_M_MASK;
				UART3_C4 &=	~UART_C4_M10_MASK;
			}
			else /* 9-bit */
			{
				UART3_C1 |= UART_C1_M_MASK;
				UART3_C4 |=	UART_C4_M10_MASK;
			}

			/*Parity type configuration*/
			if(parity == dsf_Even)
			{
				UART3_C1 &= ~UART_C1_PT_MASK;
			}
			else /* dsf_Odd */
			{
				UART3_C1 |= UART_C1_PT_MASK;
			}
		}

		UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Unable RX and TX for register 2 */

		this->baudRateModuloDivisor = (uint16_t)((21000*1000)/(this->boudRate * 16)); /* Calculate baud settings */
		UART3_BDH = (UART3_BDH & ~(UART_BDH_SBR(0x1F))) | (((this->baudRateModuloDivisor & 0x1F00) >> 8));
		UART3_BDL = (uint8_t)(this->baudRateModuloDivisor & UART_BDL_SBR_MASK);

		UART3_C2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter */
	}
} // end function initializePeripheral

void dsf_UART_OCP::setFrame(LenghtData_t length_data, Parity_t parity, StopBit_t stop)
{
	this->lengthData = length_data;
	this->parity = parity;
	this->stop = stop;
} // end function setFrame

void dsf_UART_OCP::setBaudRate(uint32_t rate)
{
	this->boudRate = rate;
} // end function setBaudRate

void dsf_UART_OCP::sendData(uint16_t data) /* Send the character */
{
	bool dataMSB = 0;
	uint8_t dataLSB = data & 0xFF;

	if(this->ocp == dsf_UART3)
	{
		if(UART3_S1 & UART_S1_TDRE_MASK)
		{
			if(lengthData == dsf_9bit)
			{
				dataMSB = (bool)(data & (1<<8));
				if(dataMSB == true)
				{
					UART3_C3 |= UART_C3_T8_MASK	;
				}
				else
				{
					UART3_C3 &= ~UART_C3_T8_MASK;
				}
			}
			UART3_D = dataLSB;
		}
	}
} // end function sendData

uint16_t dsf_UART_OCP::receiveData() /* Return data from the receiver */
{
	uint16_t data;
	bool dataMBS;
	if(this->ocp == dsf_UART3)
	{
		if(UART3_S1 & UART_S1_RDRF_MASK)
		{
			if(lengthData == dsf_9bit)
			{
				dataMBS = (bool)(UART3_C3 & UART_C3_R8_MASK);

				data = UART3_D;
				data |= (dataMBS << 8);
			}
			else
			{
				data = UART3_D;
			}
		}
	}
	return data;
} // end function receiveData

void dsf_UART_OCP::clearPeripheral()
{
	if(this->ocp == dsf_UART3)
	{
		UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Unable RX and TX for register 2 */
	}
	this->ocp = dsf_GPIOA; 				/* default is dsf_GPIOA */
	this->port = dsf_PTA1; 				/* default is dsf_PTA1 */
	this->lengthData = dsf_8bit; 		/* default is 8bit */
	this->parity = dsf_None; 			/* default is dsf_None */
	this->stop = dsf_One;  				/* default is dsf_One */
	this->baudRateModuloDivisor = 0; 	/* default is 0 */
	this->boudRate = 0; 				/* default is 0 */
} // end function clearPeripheral

void dsf_UART_OCP::cancelSend()
{
	if(this->ocp == dsf_UART3)
	{
		UART3_C2 |= UART_C2_SBK_MASK;

	}
} // end function cancelSend

void dsf_UART_OCP::waitDataTransfer()
{
	if(this->ocp == dsf_UART3)
	{
		UART3_C2 &= ~UART_C2_SBK_MASK;
		while(!(UART3_S1 & UART_S1_TDRE_MASK));
	}
} // end function waitDataTransfer

Exception_t dsf_UART_OCP::waitDataAvaliable()
{
	if(this->ocp == dsf_UART3)
	{
		while (!(UART3_S1 & UART_S1_RDRF_MASK));

		if(UART3_S1 & UART_S1_PF_MASK)
		{
			return dsf_ParityError;
		}
		else
		{
			return dsf_Ok;
		}
	}
} // end function waitDataAvaliable

bool dsf_UART_OCP::startBitAvaliable()
{
	if(this->ocp == dsf_UART3)
	{
		if(UART3_S1 & UART_S1_RDRF_MASK)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
} // end function startBitAvaliable()
