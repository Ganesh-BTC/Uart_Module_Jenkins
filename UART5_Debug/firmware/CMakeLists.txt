cmake_minimum_required(VERSION 3.15)
project(UART_Module C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER xc32-gcc)
set(CMAKE_C_FLAGS "-mprocessor=32MX795F512L -O1 -ffunction-sections -fdata-sections -Wl,--gc-sections")

# Hardcoded full path to Harmony framework
include_directories(
    include
    Application/include
    HAL/include
    src
    src/system_config/default
    src/system_config/default/
    src/system_config/default/framework/driver
    src/system_config/default/framework/driver/usart
    src/system_config/default/framework/driver/usart/src/
    src/system_config/default/framework/driver/usart
    /opt/microchip/Harmony-v2/framework
    /opt/microchip/Harmony-v2/framework/system/int/src
    /opt/microchip/Harmony-v2/framework/system/init/
)

add_executable(UART_Module
    Application/src/App_DebugPrint.c
    HAL/src/HAL_UartPrint.c
    src/app.c
    src/init.c
    src/main.c
    src/system_config/default/system_exceptions.c
    src/system_config/default/system_init.c
    src/system_config/default/system_interrupt.c
    src/system_config/default/system_tasks.c
    src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c
    src/system_config/default/framework/driver/usart/src/drv_usart_static.c
    src/system_config/default/framework/driver/usart/src/drv_usart_static_read_write.c
    src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c
    src/system_config/default/framework/system/devcon/src/sys_devcon.c
    src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c
    src/system_config/default/framework/system/ports/src/sys_ports_static.c
    /opt/microchip/Harmony-v2/framework/system/int/src/sys_int_pic32.c

    
)

add_custom_command(TARGET UART_Module POST_BUILD
    COMMAND xc32-bin2hex UART_Module
    COMMENT "Generating HEX file from ELF"
)

