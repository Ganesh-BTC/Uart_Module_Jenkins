/*******************************************************************************
Company     : BTC POWER. 
 
Author      : Krushna C

Created     : 12 April 2025
 
File Name   : main.c
 
Summary:
  This file contains the "main" function for an MPLAB Harmony project.

Description:
  This file contains the "main" function for an MPLAB Harmony project.  The
  "main" function calls the "SYS_Initialize" function to initialize the state 
  machines of all MPLAB Harmony modules in the system and it calls the 
  "SYS_Tasks" function from within a system-wide "super" loop to maintain 
  their correct operation. These two functions are implemented in 
  configuration-specific files (usually "system_init.c" and "system_tasks.c")
  in a configuration-specific folder under the "src/system_config" folder 
  within this project's top-level folder.  An MPLAB Harmony project may have
  more than one configuration, each contained within it's own folder under
  the "system_config" folder.
 *******************************************************************************/

/* Section: Included Files                                                    */
/* Defines NULL */
#include <stddef.h>

/* Defines true and false */
#include <stdbool.h>

/* Defines EXIT_FAILURE and general utilities */
#include <stdlib.h>

/* SYS function prototypes */
#include "system/common/sys_module.h"

/*
 *****************************************************************************
 *****************************************************************************
 * Section: Main Entry Point
 *****************************************************************************
 *****************************************************************************
 */
int main(void)
{
    /* Initialize all MPLAB Harmony modules, including application(s). */
    SYS_Initialize(NULL);

    while(true)
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
    }

    /* Execution should not come here during normal operation */
    return( EXIT_FAILURE);
}

/*******************************************************************************
  End of File
 *******************************************************************************/