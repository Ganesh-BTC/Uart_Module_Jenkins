/* ************************************************************************** */
/*
  Company   : BTC Power.

  Author    : Krushna C

  Created   : 14 April 2025

  File Name : init.c

  Description :
    This file initializes system-wide variables used for firmware identification.
    It provides getter and setter interfaces to manage firmware version metadata
    and initializes them via SystemInit() during application startup.
*/
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app.h"

/* ************************************************************************** */
/* Static Firmware Version Variables                                          */
/* ************************************************************************** */
static uint8_t SavedFirmwareMajor = ZERO;    // Stores the major version of the firmware
static uint8_t SavedFirmwareMinor = ZERO;    // Stores the minor version of the firmware
static uint8_t SavedFirmwarePatch = ZERO;    // Stores the patch version of the firmware

/* ************************************************************************** */
/* Setter Functions                                                           */
/* ************************************************************************** */
void SetIMDFirmwareMajor(uint8_t major)
{
    SavedFirmwareMajor = major;
}

void SetIMDFirmwareMinor(uint8_t minor)
{
    SavedFirmwareMinor = minor;
}

void SetIMDFirmwarePatch(uint8_t patch)
{
    SavedFirmwarePatch = patch;
}

/* ************************************************************************** */
/* Getter Functions                                                           */
/* ************************************************************************** */
uint8_t GetIMDFirmwareMajor(void)
{
    return SavedFirmwareMajor;
}

uint8_t GetIMDFirmwareMinor(void)
{
    return SavedFirmwareMinor;
}

uint8_t GetIMDFirmwarePatch(void)
{
    return SavedFirmwarePatch;
}

/* ************************************************************************** */
/* System Initialization Routine                                              */
/* ************************************************************************** */
/**
  Function    : SystemInit

  Description : Initializes firmware version numbers at system startup.
                Uses predefined constants UART_FIRMWARE_MAJOR, _MINOR, _PATCH
                from UART_VERSION.h.

  Total Execution Time : [Add during profiling if needed]
*/
void SystemInit(void)
{
    SetIMDFirmwareMajor(UART_FIRMWARE_MAJOR);
    SetIMDFirmwareMinor(UART_FIRMWARE_MINOR);
    SetIMDFirmwarePatch(UART_FIRMWARE_PATCH);
}

/* ************************************************************************** */
/* End of File                                                                */
/* ************************************************************************** */