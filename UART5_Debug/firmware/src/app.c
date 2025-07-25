/*******************************************************************************
  Company     : BTC POWER. 
 
  Author      : Krushna C
 
  Created     : 12 April 2025
 
  File Name   : app.c

  Summary     :
    This file contains the source code for the MPLAB Harmony application.

  Description :
    This file contains the source code for the MPLAB Harmony application. It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware. However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called. That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

/*******************************************************************************
  Section: Included Files 
 *******************************************************************************/

#include "app.h"

/*******************************************************************************
  Section: Global Data Definitions
 *******************************************************************************/

/*******************************************************************************
  Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are defined outside this structure.
 *******************************************************************************/
APP_DATA appData;

/*******************************************************************************
  Section: Application Callback Functions
 *******************************************************************************/

/*******************************************************************************
  Section: Application Local Functions
 *******************************************************************************/

/*******************************************************************************
  Section: Application Initialization and State Machine Functions
 *******************************************************************************/

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 *******************************************************************************/
void APP_Initialize(void)
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
}

/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 *******************************************************************************/
void APP_Tasks(void)
{
    /* Buffer for debug UART printing */
    char debugBuff[BUFFER_SIZE] = {ZERO};
    
    /* Check the application's current state. */
    switch(appData.state)
    {
            /* Application's initial state. */
        case APP_STATE_INIT:
        {
            /* Flag to represent initialization status */
            bool appInitialized = true;

            if(appInitialized)
            {
                // Perform system-level initialization (e.g., version setup)
                SystemInit();

                // Print module banner and version info over debug UART
                sprintf(debugBuff, "\r\n==========[ UART MODULE INFO ]==========\r\n");
                AppDebugPrint(debugBuff);

                sprintf(debugBuff, "   Firmware Version : %d.%d.%d\r\n",GetIMDFirmwareMajor(),GetIMDFirmwareMinor(),GetIMDFirmwarePatch());
                AppDebugPrint(debugBuff);

                sprintf(debugBuff, "   Module Name      : UART MODULE\r\n");
                AppDebugPrint(debugBuff);

                sprintf(debugBuff, "=========================================\r\n");
                AppDebugPrint(debugBuff);
                
                /* Transition to next application state */
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

            /* Application's service task state */
        case APP_STATE_SERVICE_TASKS:
        {
            sprintf(debugBuff, "Hello Uart!\r\n");
            AppDebugPrint(debugBuff);
            break;
        }

            /* The default state should never be executed. */
        default:
        {
            /* Handle unexpected state if needed */
            break;
        }
    }
}

/*******************************************************************************
  End of File
 *******************************************************************************/