/*
 * utils.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_UTILS_H_
#define SOURCE_UTILS_H_

#include<stdint.h>

typedef enum {dsf_NULL, dsf_GPIOA, dsf_GPIOB, dsf_GPIOC, dsf_GPIOD, dsf_GPIOE, dsf_TPM0,
			  dsf_TPM1, dsf_TPM2, dsf_CMP, dsf_PIT, dsf_DAC, dsf_ADC, dsf_I2C0,
			  dsf_I2C1, dsf_SPI0, dsf_SPI1, dsf_UART1, dsf_UART2, dsf_UART3, dsf_USB0TG} OCP_t;

typedef enum {dsf_Ch0_TPM, dsf_Ch1_TPM, dsf_Ch2_TPM, dsf_Ch3_TPM} ChTPM_t;

typedef enum {dsf_Ch0_PIT, dsf_Ch1_PIT } ChPIT_t;

typedef enum {dsf_Input, dsf_Output } Signal_t;

typedef enum {dsf_Rising, dsf_Falling } Edge_t;

typedef enum {dsf_Div1, dsf_Div2, dsf_Div4, dsf_Div8, dsf_Div16, dsf_Div32,
			  dsf_Div64, dsf_Div128} Div_t;

typedef enum {dsf_Tx, dsf_Rx} Comm_t;

typedef enum {dsf_One, dsf_Onehalf, dsf_Two } Stop_t;

typedef enum {dsf_Odd, dsf_Even } Parity_t;

typedef enum {dsf_PullUp, dsf_PullDown, dsf_PullNone } PullResistor_t;

typedef enum {ok=0, dsf_OverWrite, dsf_ParityError} Exception_t;

typedef enum {dsf_PORTA, dsf_PORTB, dsf_PORTC} Port_t;

typedef uint8_t Byte_t;

typedef uint16_t Word_t;

typedef uint32_t Dwword_t;

#endif /* SOURCE_UTILS_H_ */
