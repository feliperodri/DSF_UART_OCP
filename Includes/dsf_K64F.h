/*
 * dsf_K64F.h
 *
 *  Created on: May 21, 2017
 *      Author: Felipe R. Monteiro, Francisco Félix, Maildo Lopes, Miguel Grimm and Vinícius Souza
 */

#ifndef SOURCES_DSF_K64F_H_
#define SOURCES_DSF_K64F_H_

/* GENERAL PERIPHERALS */
typedef enum { dsf_GPIOA = 0, dsf_GPIOB, dsf_GPIOC, dsf_GPIOD, dsf_GPIOE,
               dsf_TPM0, dsf_TPM1, dsf_TPM2, dsf_CMP,
               dsf_DAC, dsf_ADC, dsf_I2C0, dsf_I2C1, dsf_SPI0, dsf_SPI1,
               dsf_UART2, dsf_UART3, dsf_UART4, dsf_USB0TG } OCP_t;

/**/
typedef enum { dsf_PTA1 = 0, dsf_PTA2, dsf_PTA4, dsf_PTA5, dsf_PTA12, dsf_PTA13, dsf_PTA16, dsf_PTA17,
               dsf_PTB0, dsf_PTB1, dsf_PTB2, dsf_PTB3, dsf_PTB8, dsf_PTB9, dsf_PTB10, dsf_PTB11,
               dsf_PTC0, dsf_PTC1, dsf_PTC2, dsf_PTC3, dsf_PTC4, dsf_PTC5, dsf_PTC6, dsf_PTC7, 
               dsf_PTC8, dsf_PTC9, dsf_PTC10, dsf_PTC11, dsf_PTC12, dsf_PTC13, dsf_PTC16, dsf_PTC17,
               dsf_PTD0, dsf_PTD1, dsf_PTD2, dsf_PTD3, dsf_PTD4, dsf_PTD5, dsf_PTD6, dsf_PTD7,
               dsf_PTE0, dsf_PTE1, dsf_PTE2, dsf_PTE3, dsf_PTE4, dsf_PTE5, dsf_PTE20, dsf_PTE21, 
               dsf_PTE22, dsf_PTE23, dsf_PTE29, dsf_PTE30, dsf_PTE31,
               dsf_SDA_PTD5, dsf_RESET_PTA20 } Pin_t;

/**/
typedef enum { dsf_Ok = 0, dsf_OverWriteError, dsf_ParityError, dsf_TimeOutError, dsf_FramingError, dsf_NoiseError, dsf_OverrunError } Exception_t;

/* GPIOA, GPIOB, GPIOC, GPIOC and GPIOD PERIPHERALS */
typedef enum { dsf_Input = 0, dsf_Output, dsf_InputWithPullUpResistor } Mode_t;

/**/
typedef enum { dsf_Rising = 0, dsf_Falling } Edge_t;

/**/
typedef enum { dsf_Low= 0, dsf_High = 1 } Level_t;

/* TPM0, TPM1, TPM2 and TPM3 PERIPHERALS */
typedef enum { dsf_Ch0TPM = 0, dsf_Ch1TPM, dsf_Ch2TPM, dsfCh3_TPM } ChTPM_t;

/**/
typedef enum { dsf_Div1 = 0, dsf_Div2, dsf_Div4, dsf_Div8, dsf_Div16,
               dsf_Div32, dsf_Div64, dsf_Div128 } Div_t;

/* PIT PERIPHERAL */
typedef enum { dsf_Ch0PIT = 0, dsf_Ch1PIT } ChPIT_t;

/* UART0, UART1 and UART2 PERIPHERALS */
typedef enum { dsf_7bit = 7, dsf_8bit, dsf_9bit } LenghtData_t;

/**/
typedef enum { dsf_Odd = 0, dsf_Even, dsf_None } Parity_t;

/**/
typedef enum { dsf_One = 0, dsf_Two} StopBit_t;

/**/
typedef enum { dsf_LSB = 0, dsf_MSB } FistBit_t;

/* Abstract class for OCPs */
class dsf_K64F_ocp
{
public:
	virtual void bindPeripheral(OCP_t ocp) = 0;
	virtual void initializePeripheral() = 0;
}; //end class dsf_K64F_ocp

#endif
