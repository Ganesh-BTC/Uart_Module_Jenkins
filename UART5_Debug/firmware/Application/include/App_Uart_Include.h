/* ************************************************************************** */
/**
  Company   : BTC Power

  Author    : Krushna C

  Created   : 26 June 2025

  File Name : App_Uart_Include.h

  Summary   : Header file containing macro definitions and UART debug dependencies
              for debug messaging within application layers.

  Description :
    - Defines reusable constants and macros used in debug formatting.
    - Serves as a central include point for UART-based diagnostic utilities.
*/
/* ************************************************************************** */

#ifndef APP_UART_INCLUDE_H
#define APP_UART_INCLUDE_H

/* ************************************************************************** */
/* Macro Definitions                                                          */
/* ************************************************************************** */
#define ZERO                      0
#define ONE                       1
#define NO_DATA                   0
#define SET                       1
#define RESET                     0
#define SUCCESS                   0

#define BUFFER_SIZE              100
#define MAX_FRAME_SIZE          200
#define MAX_MSG_BUFF_SIZE       100U
#define UART_WRITE_TIMEOUT    60000U

/* ************************************************************************** */
/* Included Modules                                                           */
/* ************************************************************************** */
#include "../include/App_DebugPrint.h"
#include "../../HAL/include/HAL_UartPrint.h"

#endif /* APP_UART_INCLUDE_H */

/* ************************************************************************** */
/* End of File                                                                */
/* ************************************************************************** */