/*
 * utils.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro
 */

#ifndef SOURCE_UTILS_H_
#define SOURCE_UTILS_H_


typedef enum {dsf_GPIOA, dsf_GPIOB, dsf_GPIOC, dsf_GPIOD, dsf_GPIOE, dsf_TPM0,
			  dsf_TPM1, dsf_TPM2, dsf_CMP, dsf_PIT, dsf_DAC, dsf_ADC, dsf_I2C0,
			  dsf_I2C1, dsf_SPI0, dsf_SPI1, dsf_UART0, dsf_UART1, dsf_UART2,
			  dsf_USB0TG} t_OCP;

typedef enum {dsf_Ch0_TPM, dsf_Ch1_TPM, dsf_Ch2_TPM, dsf_Ch3_TPM} t_Ch_TPM;

typedef enum {dsf_Ch0_PIT, dsf_Ch1_PIT } t_Ch_PIT;

typedef enum {dsf_Input, dsf_Output } t_Signal;

typedef enum {dsf_Rising, dsf_Falling } t_Edge;

typedef enum {dsf_Div1, dsf_Div2, dsf_Div4, dsf_Div8, dsf_Div16, dsf_Div32,
			  dsf_Div64, dsf_Div128} t_Div;

typedef enum {dsf_Tx, dsf_Rx} t_Comm;

typedef enum {dsf_One, dsf_Onehalf, dsf_Two } t_Stop;

typedef enum {dsf_Odd, dsf_Even } t_Parity;

typedef enum {ok=0, dsf_OverWrite, dsf_ParityError} t_Exception;

typedef uint8_t t_Byte;

typedef uint16_t t_Word;

typedef uint32_t t_Dwword;

#endif /* SOURCE_UTILS_H_ */
