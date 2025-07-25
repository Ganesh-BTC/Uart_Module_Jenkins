/* ************************************************************************** */
/*
  Company     : BTC POWER. 
 
  Author	  : Krushna C
 
  Created 	  : 12 April 2025
 
  File Name   :  HAL_UartPrint.c

  Summary     : This file contains the "UartWritePacket" function for write data on UART5.

  Description : This file contains the "UartWritePacket" function which except two arguments buffer and data size 
              In this function data is write on uart5 in byte by byte format.
 */
/* ************************************************************************** */


/* Section: Included Files                                                    */
#include <stdint.h>
#include <stdbool.h>
#include "app.h"


/* Section: Interface Functions                                         */

/************************************************************************************************
 * Function    : int8_t UartWritePacket(char *uartBuffer,int writeCount) 
 * 
 * Summary     : The `UartWritePacket` function transmits data through UART5. It takes a data 
 *               buffer and the number of bytes to write, ensuring proper error handling 
 *               for invalid pointers, buffer overflow, and timeouts. Returns status codes 
 *               to indicate success or the type of failure.
 * 
 * Description : This function is responsible for transmitting data via UART5.
 *               It writes the specified number of bytes from the provided data buffer
 *               to the UART interface while handling errors such as invalid pointers,
 *               buffer overflows, or timeouts.
 * 
 * Parameters  :
 *              uartBuffer[]  - Data buffer containing the data to be sent via UART. Must not be NULL.
 *              writeCount    - The number of bytes to transmit. Must be less than MAX_FRAME_SIZE.
 * 
 * Returns     :
 *              Status =  SUCCESS - Data was successfully written to UART.
 *              Status =  UART_TIMEOUT - Write operation failed due to timeout.
 *              Other error codes:
 *                  - e_ERROR_UART_INVALID_POINTER: Buffer pointer is NULL.
 *                  - e_ERROR_UART_BUFFER_OVERFLOW: writeCount exceeds MAX_FRAME_SIZE.
 *                 -  e_NO_DATA: No data to write (writeCount = 0).
 ************************************************************************************************/
int8_t UartWritePacket(char *uartBuffer,int writeCount)
{
    int8_t status = SUCCESS;
    int8_t resultValue = RESET;
    int8_t currentCount = RESET;
    uint16_t uartWriteTimeout = RESET;

    if(uartBuffer == NULL)
    {
        status = e_ERROR_UART_INVALID_POINTER;
    }
    else if(writeCount >= MAX_FRAME_SIZE)
    {
        status = e_ERROR_UART_BUFFER_OVERFLOW;
    }
    else if(writeCount == NO_DATA)
    {
        status = e_NO_DATA;
    }
    else if(writeCount < ZERO)
    {
        status = e_ERROR_BUFFER_SIZE_INVALID;
    }
    else
    {
        while(currentCount <= writeCount)
        {
            if(uartWriteTimeout <= UART_WRITE_TIMEOUT)
            {
                if(currentCount < writeCount)
                {
                    resultValue = DRV_USART0_Write(&uartBuffer[currentCount],writeCount - currentCount);
                    if(resultValue < RESET)
                    {
                        status = e_ERROR_FAILED_WRITE_UART;
                    }
                    else
                    {
                        currentCount += resultValue;
                    }
                }
                else
                {
                    // MISRA-C 2023
                }
            }
            else
            {
                status = e_UART_TIMEOUT;
                break;
            }
            ++uartWriteTimeout;
        }
    }
    return status;
}

/* *****************************************************************************
 End of File -: HAL_UartPrint.c
 */