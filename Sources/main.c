/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"
#include<assert.h>


//------------------FUNÇOES UART 3--------------------

void uart3_putchar (uint8_t ch)
{
/* Wait until space is available in the FIFO */
while(!(UART3_S1 & UART_S1_TDRE_MASK));

assert(ch == 'F');
 UART3_D =ch;
}

uint8_t uart3_getchar ()
{
	//uint8_t expectedResult = 'F';
	/* Wait until character has been received */
	while (!(UART3_S1 & UART_S1_RDRF_MASK));
	/* Return the 8-bit data from the receiver */

	assert(UART3_D == 'F');
	GPIOE_PCOR |= 1<<26;
	return UART3_D;
}

//----------------FUNÇOES UART4-------------------

void uart4_putchar (uint8_t ch)
{
/* Wait until space is available in the FIFO */
while(!(UART4_S1 & UART_S1_TDRE_MASK));

assert(ch == 'F');
 UART4_D =ch;
}

uint8_t uart4_getchar ()
{
	/* Wait until character has been received */
	while (!(UART4_S1 & UART_S1_RDRF_MASK));
	/* Return the 8-bit data from the receiver */
	assert(UART4_D == 'F');
	GPIOE_PCOR |= 1<<26;
	return UART4_D;
}


int main(void)
{
	uint16_t ubd;
	uint8_t temp;
	uint8_t ch;
	int x=0;

	// --------------------CONFIGURANDO A UART 3------------------------------------------------------

	SIM_SCGC4 |= SIM_SCGC4_UART3_MASK; /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

	PORTB_PCR10 |= PORT_PCR_MUX(3);// seleciona a alternativa 2 para GPAIO, Rx
	PORTB_PCR11 |= PORT_PCR_MUX(3);// seleciona a alternativa 2 para GPAIO, Tx

	UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); // desabilita a trasimição e recepçaõ da uart0
		// isso deve ser feito antes de configurá-la.

		UART3_C1 = 0;// registrador 1 setado no modo padrão

		// calculando a o baud rate

		ubd = (uint16_t)((21000*1000)/(9600 * 16));

		temp = UART3_BDH & ~(UART_BDH_SBR(0x1F)); /*Save the value of UART0_BDH except SBR*/
		UART3_BDH = temp | (((ubd & 0x1F00) >> 8));
		UART3_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

		UART3_C2 |=(UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter*/


		//------------ CONFIGURANDO A UART 4--------------------------------------



		SIM_SCGC1 |= SIM_SCGC1_UART4_MASK; /*Enable the UART clock*/
		SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

			PORTB_PCR24 |= PORT_PCR_MUX(3);// seleciona a alternativa 2 para GPAIO, Rx
			PORTB_PCR25 |= PORT_PCR_MUX(3);// seleciona a alternativa 2 para GPAIO, Tx

			UART4_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK ); // desabilita a trasimição e recepçaõ da uart0
				// isso deve ser feito antes de configurá-la.

				UART4_C1 = 0;// registrador 1 setado no modo padrão

				// calculando a o baud rate

				ubd = (uint16_t)((21000*1000)/(9600 * 16));

				temp = UART4_BDH & ~(UART_BDH_SBR(0x1F)); /*Save the value of UART0_BDH except SBR*/
				UART4_BDH = temp | (((ubd & 0x1F00) >> 8));
				UART4_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

				UART4_C2 |=(UART_C2_TE_MASK |UART_C2_RE_MASK); /* Enable receiver and transmitter*/

		//---------------------------------------------------------------------------------------
			// configura LED RGB
			SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
			PORTE_PCR26 |= PORT_PCR_MUX(1);
			GPIOE_PDDR |= 1<<26;
			GPIOE_PSOR |= 1<<26;

		while(1){

			uart3_putchar ('F');

			ch= uart3_getchar();

			//if (ch=='G')


			//assert(ch == 'F');
/*			if(ch=='F'){
			while (x++<2000000);

					GPIOE_PTOR |= 1<<26;// alterna nível lógico de RGB (acende apaga)
					x=0;
		}*/
		}

		return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
