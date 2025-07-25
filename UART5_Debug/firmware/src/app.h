/* ************************************************************************** */
/**
 * Company     : BTC POWER
 * 
 * Author      : Surya B
 * 
 * Created     : 14 April 2025
 *
 * File Name   : app.h
 *
 * Summary:
 *   This header file provides prototypes and definitions for the application.
 *
 * Description:
 *   - Defines application state machine and initialization/task APIs.
 *   - Declares the application data structure.
 *   - To be used with MPLAB Harmony framework.
 */
/* ************************************************************************** */

#ifndef APP_H
#define APP_H

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "../include/Uart_Module_Version.h"
#include "../Application/include/App_Uart_Include.h"

/* ************************************************************************** */
/* Section: Application States                                                */
/* ************************************************************************** */
/**
 * Enum:
 *   APP_STATES
 *
 * Description:
 *   Defines possible states of the application task scheduler.
 */
typedef enum
{
    APP_STATE_INIT = 0,         /* Initial application state */
    APP_STATE_SERVICE_TASKS     /* Main application loop */
} APP_STATES;

/* ************************************************************************** */
/* Section: Application Data Structure                                       */
/* ************************************************************************** */
/**
 * Struct:
 *   APP_DATA
 *
 * Description:
 *   Holds the current state of the application.
 */
typedef struct
{
    APP_STATES state;           /* Current application state */
} APP_DATA;

/* ************************************************************************** */
/* Section: Application Initialization and Tasks                             */
/* ************************************************************************** */
/**
 * Function:
 *   void APP_Initialize(void)
 *
 * Description:
 *   Initializes the Harmony application and places the system into its
 *   initial application state. Should be called in SYS_Initialize().
 */
void APP_Initialize(void);

/**
 * Function:
 *   void APP_Tasks(void)
 *
 * Description:
 *   Implements the application task logic. Should be called repeatedly
 *   from SYS_Tasks().
 */
void APP_Tasks(void);

#endif /* APP_H */

/* ************************************************************************** */
/* End of File                                                                */
/* ************************************************************************** */