/* ************************************************************************** */
/*
  Company    : BTC POWER. 
 
  Author	 : Krushna C
 
  Created    : 12 April 2025
 
  File Name  : App_DebugPrint.c

  Summary    : This file contains functions related to application-level debugging and UART communication, specifically for sending debug messages over UART. 
    The `AppDebugPrint` function ensures that valid debug strings are sent over UART for output and handles error checking during the process.

Description  : This file primarily includes the function `AppDebugPrint`, which is designed to facilitate the printing of debug messages to a UART interface.
    It first checks if the provided debug message (`debugBuffer`) is valid (i.e., not `NULL`). 
    If valid, the function calculates the length of the string and attempts to send it over UART using the `UartWritePacket` function. 
    If the message is successfully transmitted, the function returns a `SUCCESS` status. If any error occurs,
    including an invalid pointer or failure in UART communication, the appropriate error code is returned.

 */
/* ************************************************************************** */


/* Section: Included Files                                                    */
#include <stdint.h>
#include <stdbool.h>
#include "app.h"


/* Section: Interface Functions                                         */

/************************************************************************************************
Function:  
    int8_t AppDebugPrint(char *uartBuffer);

Summary:  
    Sends a string to a UART interface for debugging output, checking for errors in the process.

Description:  
    This function takes a debug string (`debugBuffer`), checks if the buffer pointer is valid, 
    and attempts to send the string through UART for debugging purposes. 
    The function first ensures that the `debugBuffer` is not NULL. If the buffer is valid,
    it calculates the length of the string and attempts to print it using the `UartWritePacket` function. 
    If the UART print operation is successful, it returns `SUCCESS`; otherwise,
    it returns the error code from the UART print function. If the buffer pointer is NULL, 
    it returns an invalid pointer error.

Parameters:  
    debugBuffer[]: A null-terminated string to be sent over UART for debugging output.

Returns:  
    - SUCCESS: The string was successfully sent via UART.
    - e_ERROR_UART_INVALID_POINTER: The input debugBuffer was NULL.
    - Any other error code from UartWritePacket in case of failure.

Remarks:  
    This function is typically used for debugging purposes in embedded systems 
    where UART communication is used to print log messages or debug information.
    It ensures that invalid input pointers are properly handled, and 
    any issues with UART communication are reported.
    The function depends on the `UartWritePacket` function to handle the actual transmission of data over UART.

 ************************************************************************************************/
int8_t AppDebugPrint(char *uartBuffer)
{
    int8_t status = SUCCESS;
    uint8_t writeCount = RESET;

    if(uartBuffer == NULL) //buffer data is NULL or not?
    {
        return e_ERROR_UART_INVALID_POINTER;
    }
    else
    {
        writeCount = strlen(uartBuffer);
        if(writeCount == ZERO)
        {
            return e_ERROR_BUFFER_SIZE_INVALID;
        }
        else
        {
            status = UartWritePacket(uartBuffer,writeCount);//status value update with UartWritePacket

        }
    }
    return status;
}

/* *****************************************************************************
 End of File -:  App_DebugPrint.c
 */