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

} // end dsf_UART_OCP constructor

dsf_UART_OCP::~dsf_UART_OCP()
{

} // end dsf_UART_OCP destructor

void dsf_UART_OCP::BindPeripheral(t_OCP ocp) const
{

} // end function BindPeripheral

void dsf_UART_OCP::BindPin(int pin) const
{

} // end function BindPin

void dsf_UART_OCP::Initialize() const
{

} // end function Initialize

void dsf_UART_OCP::SetAddrSlave(t_Byte addr)
{

} // end function SetAddrSlave

void dsf_UART_OCP::SetFrame(t_Byte LenData, t_parity Parity, t_stop stop)
{

} // end function SetFrame

void dsf_UART_OCP::SetBaudRate(int rate)
{

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
