/* ************************************************************************** */
/*
  Company     : BTC POWER. 
 
  Author	  : Krushna C
 
  Created 	  : 12 April 2025
 
  File Name   : HAL_UartPrint_.h

  Summary     : The file provides an interface for debugging via UART, 
				including error codes for common issues and a function 
				(`UartWritePacket`) to transmit data. The function ensures 
				safe and reliable data transfer, providing status codes 
				to indicate success or failure.
 
  Description : This header file contains the declarations related to UART 
				debug functionality. It defines error codes, constants, and 
				the `UartWritePacket` function, which is responsible for transmitting 
			   data via UART. The file includes error handling mechanisms 
				such as buffer overflow detection, invalid pointer checks, 
			   and timeout handling.
 ************************************************************************* */

#ifndef HAL_UARTPRINT_H   
#define HAL_UARTPRINT_H

/* Enum for UART write failure error codes */
typedef enum
{
	e_NO_DATA = -1, // No data to write
	e_ERROR_BUFFER_SIZE_INVALID = -2, // No data to write
	e_ERROR_UART_BUFFER_OVERFLOW = -3, // UART buffer overflow error (newly added)
	e_UART_TIMEOUT = -4, // UART write timeout error
	e_ERROR_UART_INVALID_POINTER = -5, // UART invalid pointer error
	e_ERROR_FAILED_WRITE_UART = -6
} e_UARTErrorCode_t;

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
int8_t UartWritePacket(char *uartBuffer, int writeCount);


#endif /* _HAL_UARTPRINT_H */
/* *****************************************************************************
 End of File
 */