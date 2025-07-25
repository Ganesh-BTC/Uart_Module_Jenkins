/* ************************************************************************** */
/**
  Company   : BTC Power

  Author    : Krushna C

  Created   : 12 June 2025

  File Name : Uart_Module_Version.h

  Summary   : Firmware versioning header using semantic version format.

  Description :
    This header defines firmware version constants (MAJOR.MINOR.PATCH) that can be used
    across build metadata, logging, or update mechanisms for traceability and compatibility checks.
*/
/* ************************************************************************** */

#ifndef UART_VERSION_H
#define UART_VERSION_H

/* ************************************************************************** */
/* Firmware Version Definition                                                */
/* ************************************************************************** */
#define UART_FIRMWARE_MAJOR     1     // Major release: backward-incompatible changes
#define UART_FIRMWARE_MINOR     0     // Minor release: backward-compatible enhancements
#define UART_FIRMWARE_PATCH     0     // Patch release: bug fixes, no interface changes

#endif /* UART_VERSION_H */

/* ************************************************************************** */
/* End of File                                                                */
/* ************************************************************************** */