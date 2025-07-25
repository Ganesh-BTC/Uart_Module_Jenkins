/* ************************************************************************** */
/*
  Company     : BTC POWER. 
 
  Author	  : Krushna C
 
  Created 	  : 12 April 2025
 
  File Name   : App_DebugPrint_.h

  Summary     : The file provides an interface for debugging via UART, 
				including error codes for common issues and a function 
				(`AppDebugPrint`) to transmit data. The function ensures 
				safe and reliable data transfer, providing status codes 
				to indicate success or failure.
 
  Description : This header file contains the declarations related to UART 
				debug functionality. It defines error codes, constants, and 
				the `AppDebugPrint` function, which is responsible for transmitting 
			   data via UART. The file includes error handling mechanisms 
				such as buffer overflow detection, invalid pointer checks, 
			   and timeout handling.
 ************************************************************************* */

#ifndef APP_DEBUGPRINT_H   
#define APP_DEBUGPRINT_H

#define DEBUG_COLOR_RED      "\x1B[31m"
#define DEBUG_COLOR_GREEN    "\x1B[32m"
#define DEBUG_COLOR_YELLOW   "\x1B[33m"
#define DEBUG_COLOR_BLUE     "\x1B[34m"
#define DEBUG_COLOR_MAGENTA  "\x1B[35m"
#define DEBUG_COLOR_CYAN     "\x1B[36m"
#define DEBUG_COLOR_WHITE    "\x1B[37m"
#define DEBUG_COLOR_RESET    "\x1B[0m\n\r"

#define LOGGING_PRE                     \
    unsigned char uartData[MAX_MSG_BUFF_SIZE] = { };  \
    unsigned char uartData2[MAX_MSG_BUFF_SIZE] = { }; 

#define LOGGING_WARNING(...)                                \
        {                                                   \
            LOGGING_PRE;                                    \
            sprintf(uartData2, __VA_ARGS__);               \
            sprintf(uartData, "\n\r%s():%d:%s%s%s",        \
            __FUNCTION__, __LINE__, DEBUG_COLOR_MAGENTA,    \
            uartData2, DEBUG_COLOR_RESET);                 \
            AppDebugPrint(uartData);                     \
        }

#define LOGGING_DEBUG(...)                                 \
        {                                                  \
            LOGGING_PRE;                                   \
            sprintf(uartData2, __VA_ARGS__);              \
            sprintf(uartData, "\n\r%s():%d:%s%s%s",       \
            __FUNCTION__, __LINE__, DEBUG_COLOR_GREEN,     \
            uartData2, DEBUG_COLOR_RESET);                \
            AppDebugPrint(uartData);                    \
        }

#define LOGGING_ERROR(...)                                 \
        {                                                  \
            LOGGING_PRE;                                   \
            sprintf(uartData2, __VA_ARGS__);              \
            sprintf(uartData, "\n\r%s():%d:%s%s%s",       \
            __FUNCTION__, __LINE__, DEBUG_COLOR_RED,       \
            uartData2, DEBUG_COLOR_RESET);                \
            AppDebugPrint(uartData);                    \
        }

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
int8_t AppDebugPrint(char *uartBuffer);

#endif /* APP_DEBUGPRINT_H */
/* *****************************************************************************
 End of File
 */