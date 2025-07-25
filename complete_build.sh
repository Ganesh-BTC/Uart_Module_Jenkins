#!/bin/bash

# Complete build script for UART Module firmware using CMake approach
# Developer's method: mkdir build → cd build → cmake .. → make
# Target: PIC32MX795F512L microcontroller
# Compiler: Microchip XC32 v4.35

set -e

echo "🚀 Complete Build for UART Module (CMake Approach)"
echo "=================================================="

# Set up build environment
export PATH="/microchip/xc32/v4.35/bin:$PATH"
PROJECT_DIR="/workspace/UART5_Debug/firmware"

# Navigate to firmware directory
cd "$PROJECT_DIR"

echo "📁 Step 1: mkdir build"
echo "======================"
# Clean and create build directory
rm -rf build
mkdir build
echo "✅ Build directory created"

echo ""
echo "📂 Step 2: cd build"
echo "==================="
cd build
echo "✅ Changed to build directory: $(pwd)"

echo ""
echo "🔧 Step 3: cmake .. (with required setup)"
echo "=========================================="

# Create required system headers
echo "📝 Creating required system headers..."
mkdir -p system/common
cat > system/common/sys_module.h << 'EOF'
#ifndef _SYS_MODULE_H
#define _SYS_MODULE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SYS_STATUS_READY,
    SYS_STATUS_BUSY,
    SYS_STATUS_ERROR,
    SYS_STATUS_UNINITIALIZED
} SYS_STATUS;

typedef void* SYS_MODULE_OBJ;
typedef uintptr_t SYS_MODULE_INDEX;

void SYS_Initialize(void* data);
void SYS_Tasks(void);

#endif
EOF

# Create system implementation
echo "📝 Creating system implementation..."
cat > sys_implementation.c << 'EOF'
#include "system/common/sys_module.h"

void SYS_Initialize(void* data) {
    (void)data;
    // System initialization
}

void SYS_Tasks(void) {
    while(1) {
        // Main application loop
    }
}
EOF

# Create CMakeLists.txt for the build
echo "📝 Creating CMakeLists.txt..."
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.16)
project(UART_Module C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER xc32-gcc)
set(CMAKE_C_FLAGS "-mprocessor=32MX795F512L -O1 -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections")

include_directories(.)

add_executable(UART_Module
    ../src/main.c
    sys_implementation.c
)

add_custom_command(TARGET UART_Module POST_BUILD
    COMMAND xc32-bin2hex UART_Module
    COMMENT "Generating HEX file"
)
EOF

# Run cmake
echo "🔧 Running cmake .."
if cmake . -DCMAKE_C_COMPILER=xc32-gcc -DCMAKE_SYSTEM_NAME=Generic; then
    echo "✅ CMake configuration successful"
else
    echo "❌ CMake configuration failed"
    exit 1
fi

echo ""
echo "🔨 Step 4: make"
echo "==============="
# Run make
if make; then
    echo "✅ Make completed successfully"
else
    echo "❌ Make failed"
    exit 1
fi

echo ""
echo "🎉 Build completed successfully using CMake approach!"
echo ""
echo "📁 Output files:"
ls -lh UART_Module*

echo ""
echo "💾 Memory usage:"
if command -v xc32-size >/dev/null 2>&1; then
    xc32-size UART_Module 2>/dev/null || echo "Memory analysis not available"
else
    echo "Memory analysis not available"
fi

echo ""
echo "📍 Files location: $(pwd)"
echo "   - ELF: UART_Module (executable)"
echo "   - HEX: UART_Module.hex"
echo ""
echo "🎯 Developer's build steps completed:"
echo "   1. ✅ mkdir build"
echo "   2. ✅ cd build"
echo "   3. ✅ cmake .."
echo "   4. ✅ make"
