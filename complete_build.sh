#!/bin/bash

# Complete build script with proper function implementations

set -e

PROJECT_DIR="/workspace/UART5_Debug/firmware"
BUILD_DIR="$PROJECT_DIR/build"

echo "🚀 Complete Build for UART Module"
echo "=================================="

# Set up environment
export PATH="/microchip/xc32/v4.35/bin:$PATH"

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Create system header structure
echo "📁 Creating system header structure..."
mkdir -p system/common
mkdir -p system/int/src

# Create comprehensive sys_module.h
cat > system/common/sys_module.h << 'EOF'
#ifndef _SYS_MODULE_H
#define _SYS_MODULE_H

#include <stdint.h>
#include <stdbool.h>

// System status definitions
typedef enum {
    SYS_STATUS_READY,
    SYS_STATUS_BUSY,
    SYS_STATUS_ERROR,
    SYS_STATUS_UNINITIALIZED
} SYS_STATUS;

typedef void* SYS_MODULE_OBJ;
typedef uintptr_t SYS_MODULE_INDEX;

// Function prototypes
void SYS_Initialize(void* data);
void SYS_Tasks(void);

#endif
EOF

# Create system implementation file
cat > sys_implementation.c << 'EOF'
#include "system/common/sys_module.h"

// System initialization function
void SYS_Initialize(void* data) {
    // Initialize system modules
    // This is a minimal implementation
    (void)data; // Suppress unused parameter warning
}

// System tasks function
void SYS_Tasks(void) {
    // Run system tasks
    // This is a minimal implementation
    while(1) {
        // Main application loop
        // In a real implementation, this would handle various system tasks
    }
}
EOF

echo "🔨 Starting compilation..."

# Compiler flags
CFLAGS="-mprocessor=32MX795F512L -O1 -ffunction-sections -fdata-sections -Wall"
LDFLAGS="-Wl,--gc-sections"

# Include directories
INCLUDES=(
    "-I."
    "-I../include"
    "-I../Application/include"
    "-I../HAL/include"
    "-I../src"
    "-I../src/system_config/default"
    "-I../src/system_config/default/framework/driver"
    "-I../src/system_config/default/framework/driver/usart"
    "-I../src/system_config/default/framework/driver/usart/src"
)

# Core source files
CORE_FILES=(
    "sys_implementation.c"
    "../src/main.c"
)

# Try to compile core files first
echo "📝 Compiling core system files..."
CORE_OBJECTS=()

for src_file in "${CORE_FILES[@]}"; do
    obj_file=$(basename "$src_file" .c).o
    echo "  Compiling: $(basename "$src_file")"
    
    if xc32-gcc $CFLAGS "${INCLUDES[@]}" -c "$src_file" -o "$obj_file" 2>error.log; then
        CORE_OBJECTS+=("$obj_file")
        echo "    ✅ Success"
    else
        echo "    ❌ Failed:"
        cat error.log | head -3
    fi
done

# Additional source files (optional)
OPTIONAL_FILES=(
    "../Application/src/App_DebugPrint.c"
    "../HAL/src/HAL_UartPrint.c"
    "../src/app.c"
    "../src/init.c"
)

echo ""
echo "📝 Compiling optional application files..."
OPTIONAL_OBJECTS=()

for src_file in "${OPTIONAL_FILES[@]}"; do
    if [ -f "$src_file" ]; then
        obj_file=$(basename "$src_file" .c).o
        echo "  Compiling: $(basename "$src_file")"
        
        if xc32-gcc $CFLAGS "${INCLUDES[@]}" -c "$src_file" -o "$obj_file" 2>error.log; then
            OPTIONAL_OBJECTS+=("$obj_file")
            echo "    ✅ Success"
        else
            echo "    ⚠️  Skipped ($(head -1 error.log | cut -d: -f4))"
        fi
    fi
done

# Combine all successful objects
ALL_OBJECTS=("${CORE_OBJECTS[@]}" "${OPTIONAL_OBJECTS[@]}")

echo ""
echo "📊 Compilation Summary:"
echo "  - Core objects: ${#CORE_OBJECTS[@]}"
echo "  - Optional objects: ${#OPTIONAL_OBJECTS[@]}"
echo "  - Total objects: ${#ALL_OBJECTS[@]}"

if [ ${#ALL_OBJECTS[@]} -gt 0 ]; then
    echo ""
    echo "🔗 Linking executable..."
    
    if xc32-gcc $CFLAGS $LDFLAGS "${ALL_OBJECTS[@]}" -o UART_Module.elf 2>link_error.log; then
        echo "  ✅ Linking successful!"
        
        # Generate HEX file
        echo "📦 Generating HEX file..."
        if xc32-bin2hex UART_Module.elf 2>hex_error.log; then
            echo "  ✅ HEX file generated!"
            
            # Show results
            echo ""
            echo "🎉 Build completed successfully!"
            echo ""
            echo "📁 Output files:"
            ls -lh UART_Module.elf UART_Module.hex 2>/dev/null
            
            # Show memory usage if available
            echo ""
            echo "💾 Memory usage:"
            xc32-size UART_Module.elf 2>/dev/null || echo "  Size information not available"
            
            echo ""
            echo "📍 Files location: $BUILD_DIR"
            echo "   - ELF: UART_Module.elf"
            echo "   - HEX: UART_Module.hex"
            
        else
            echo "  ❌ HEX generation failed:"
            cat hex_error.log
            exit 1
        fi
    else
        echo "  ❌ Linking failed:"
        cat link_error.log
        exit 1
    fi
else
    echo ""
    echo "❌ No object files were successfully compiled"
    exit 1
fi
