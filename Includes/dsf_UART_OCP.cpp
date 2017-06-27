/*
 * dsf_UART_OCP.cpp
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
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
	if(ocp == dsf_UART2 || ocp == dsf_UART3 || ocp == dsf_UART4){
		this->ocp = ocp;
		if(ocp == dsf_UART2)
		{
			UARTx = SIM_SCGC4_UART2_MASK;
			cUART_SimSCGC =    (uint32_t *)(0x40048034);
			addressPortPCRtx = (uint32_t *)(0x4004C00C);
			addressPortPCRrx = (uint32_t *)(0x4004C008);
			addressUARTx_BDH = (uint8_t *)(0x4006C000);
			addressUARTx_BDL = (uint8_t *)(0x4006C001);
			addressUARTxS1 =   (uint8_t *)(0x4006C004);
			addressUARTxS2 =   (uint8_t *)(0x4006C005);
			addressUARTxC1 = (uint8_t *)(0x4006C002);
			addressUARTxC2 = (uint8_t *)(0x4006C003);
			addressUARTxC3 = (uint8_t *)(0x4006C006);
			addressUARTxC4 = (uint8_t *)(0x4006C00A);
			clockEnablePort = (uint32_t) (0x0200 << 3);
		}
		else if(ocp == dsf_UART3)
		{
			UARTx = SIM_SCGC4_UART3_MASK;
			cUART_SimSCGC =    (uint32_t *)(0x40048034);
			addressPortPCRtx = (uint32_t *)(0x4004A02C);
			addressPortPCRrx = (uint32_t *)(0x4004A028);
			addressUARTx_BDH = (uint8_t *)(0x4006D000);
			addressUARTx_BDL = (uint8_t *)(0x4006D001);
			addressUARTxS1 =   (uint8_t *)(0x4006D004);
			addressUARTxS2 =   (uint8_t *)(0x4006D005);
			addressUARTxC1 = (uint8_t *)(0x4006D002);
			addressUARTxC2 = (uint8_t *)(0x4006D003);
			addressUARTxC3 = (uint8_t *)(0x4006D006);
			addressUARTxC4 = (uint8_t *)(0x4006D00A);
			clockEnablePort = (uint32_t) (0x0200 << 1);
		}
		else /* dsf_UART4 */
		{
			UARTx = SIM_SCGC1_UART4_MASK;
			cUART_SimSCGC =    (uint32_t *)(0x40048028);
			addressPortPCRtx = (uint32_t *)(0x4004B03C);
			addressPortPCRrx = (uint32_t *)(0x4004B038);
			addressUARTx_BDH = (uint8_t *)(0x400EA000);
			addressUARTx_BDL = (uint8_t *)(0x400EA001);
			addressUARTxS1 =   (uint8_t *)(0x400EA004);
			addressUARTxS2 =   (uint8_t *)(0x400EA005);
			addressUARTxC1 = (uint8_t *)(0x400EA002);
			addressUARTxC2 = (uint8_t *)(0x400EA003);
			addressUARTxC3 = (uint8_t *)(0x400EA006);
			addressUARTxC4 = (uint8_t *)(0x400EA00A);
			clockEnablePort = (uint32_t) (0x0200 << 2);
		}
	}
	else
	{
		//TODO
	}
} // end function BindPeripheral

void dsf_UART_OCP::initializePeripheral()
{
	*cUART_SimSCGC |= SIM_SCGC4_UART3_MASK; /* Enable the UART clock */
	SIM_SCGC5 |= clockEnablePort; /* Enable the PORTB clock */

	*addressPortPCRtx |= PORT_PCR_MUX(3); /* Select alternative 3 for TX */
	*addressPortPCRrx |= PORT_PCR_MUX(3); /* Select alternative 3 for RX */

	*addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Unable RX and TX for register 2 */
	/*Set frame configuration for register 1 */
	*addressUARTxC1 = 0;

	/* Stop configuration */
	if(stop==dsf_One) /* 1-bit */
	{
		*addressUARTx_BDH &= ~UART_BDH_SBNS_MASK;
	}
	else /* 2-bit */
	{
		*addressUARTx_BDH |= UART_BDH_SBNS_MASK;
	}

	/* lengthData and parity configuration */
	if(parity == dsf_None) /* parity off */
	{
		*addressUARTxC1 &= ~UART_C1_PE_MASK;

		if(lengthData == dsf_8bit )  /* 8-bit */
		{
			*addressUARTxC1 &= ~UART_C1_M_MASK;
		}
		else if(lengthData == dsf_9bit)  /* 9-bit */
		{
			*addressUARTxC1 |= UART_C1_M_MASK;
		}
		else
		{
			//TODO
		}
	}
	else /* Parity on */
	{
		*addressUARTxC1 |= UART_C1_PE_MASK;

		if(lengthData == dsf_7bit )	 /* 7-bit */
		{
			*addressUARTxC1 &= ~UART_C1_M_MASK;
			*addressUARTxC4 &=	~UART_C4_M10_MASK;
		}
		else if(lengthData == dsf_8bit)  /* 8-bit */
		{
			*addressUARTxC1 |=  UART_C1_M_MASK;
			*addressUARTxC4 &=	~UART_C4_M10_MASK;
		}
		else  /* 9-bit */
		{
			*addressUARTxC1 |= UART_C1_M_MASK;
			*addressUARTxC4 |=	UART_C4_M10_MASK;
		}

		/* Parity type configuration */
		if(parity == dsf_Even)
		{
			*addressUARTxC1 &= ~UART_C1_PT_MASK;
		}
		else /* dsf_Odd */
		{
			*addressUARTxC1 |= UART_C1_PT_MASK;
		}
	}

	/* Fist bit configuration */
	if(fistBit == dsf_LSB)
	{
		*addressUARTxS2 &= ~UART_S2_MSBF_MASK;
	}
	else
	{
		*addressUARTxS2 |= UART_S2_MSBF_MASK;
	}

	/* Baud rate configuration */

	*addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Unable RX and TX for register 2 */

	this->baudRateModuloDivisor = (uint16_t)((21000*1000)/(this->boudRate * 16)); /* Calculate baud settings */
	*addressUARTx_BDH = (*addressUARTx_BDH & ~(UART_BDH_SBR(0x1F))) | (((this->baudRateModuloDivisor & 0x1F00) >> 8));
	*addressUARTx_BDL = (uint8_t)(this->baudRateModuloDivisor & UART_BDL_SBR_MASK);

	*addressUARTxC2 |= (UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter*/
} // end function Initialize


void dsf_UART_OCP::enablePeripheral()
{
	*cUART_SimSCGC |= SIM_SCGC4_UART3_MASK;
	SIM_SCGC5 |= clockEnablePort;
} // end function enablePeripheral

void dsf_UART_OCP::disablePeripheralAndSavePower()
{
	*cUART_SimSCGC &= ~SIM_SCGC4_UART3_MASK;
	SIM_SCGC5 &= ~clockEnablePort;
} // end function disablePeripheralAndSavePower


void dsf_UART_OCP::setFrame(LenghtData_t length_data, Parity_t parity, StopBit_t stop, FistBit_t fistBit)
{
	this->lengthData = length_data;
	this->parity = parity;
	this->stop = stop;
	this->fistBit = fistBit;
} // end function SetFrame

void dsf_UART_OCP::setBaudRate(uint32_t rate)
{
	this->boudRate = rate;
} // end function SetBaudRate

void dsf_UART_OCP::sendData(uint16_t data) /* Send the character */
{
	bool dataM=0;
	uint8_t dataL = data & 0xFF;

	if(*addressUARTxS1 & UART_S1_TDRE_MASK)
	{
		if(lengthData == dsf_9bit)
		{
			dataM = (bool)(data & (1<<8));
			if(dataM == true)
			{
				*addressUARTxC3|= UART_C3_T8_MASK	;
			}
			else
			{
				*addressUARTxC3 &= ~UART_C3_T8_MASK;
			}
		}
		UART3_D = dataL;
	}
} // end function SendData

uint16_t dsf_UART_OCP::receiveData()/* Return the 8-bit data from the receiver */
{
	uint16_t data;
	bool dataM;
	uint8_t dataL;

	if(*addressUARTxS1& UART_S1_RDRF_MASK)
	{
		if(lengthData == dsf_9bit)
		{
			dataM = (bool)(*addressUARTxC3 & UART_C3_R8_MASK);

			data = UART3_D;
			data |= (dataM << 8);
		}
		else
		{
			data = UART3_D;
		}
	}
	return data;
} // end function ReceiveData

void dsf_UART_OCP::clearPeripheral()
{
	*addressUARTxC2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); /* Unable RX and TX for register 2 */
	this->ocp = dsf_GPIOA; 									  /* default is dsf_GPIOA */
	this->port = dsf_PORTA; 								  /* default is dsf_PTA1 */
	this->lengthData = dsf_8bit;							  /* default is 8bit */
	this->parity = dsf_None;								  /* default is dsf_None */
	this->stop = dsf_One;									  /* default is dsf_One */
	this->baudRateModuloDivisor = 0;						  /* default is 0 */
	this->boudRate = 0;										  /* default is 0 */
} // end function ClearPeripheral

void dsf_UART_OCP::cancelSend()
{
	*addressUARTxC2 |= UART_C2_SBK_MASK;
} // end function CancelSend

void dsf_UART_OCP::waitDataTransfer()
{
	*addressUARTxC2 &= ~UART_C2_SBK_MASK;
	while(!(*addressUARTxS1 & UART_S1_TDRE_MASK));
} // end function waitDataTransfer

Exception_t dsf_UART_OCP::waitDataAvaliable()
{
	while (!(*addressUARTxS1 & UART_S1_RDRF_MASK));

	if(*addressUARTxS1 & UART_S1_PF_MASK)
	{
		return dsf_ParityError;
	}
	else if(*addressUARTxS1 & UART_S1_FE_MASK)
	{
		return dsf_FramingError;
	}
	else if(*addressUARTxS1 & UART_S1_NF_MASK)
	{
		return dsf_NoiseError;
	}
	else if(*addressUARTxS1 & UART_S1_OR_MASK)
	{
		return dsf_OverrunError;
	}
	else
	{
		return dsf_Ok;
	}

} // end function waitDataAvaliable

bool dsf_UART_OCP::startBitAvaliable()
{
	if(*addressUARTxS1 & UART_S1_RDRF_MASK)
	{
		return true;
	}
	else
	{
		return false;
	}
} // end function startBitAvaliable
