# UART Module - Local Build Guide

## 📁 Project Structure

```
UART_MODULE/
├── README.md                    # Complete project documentation
├── BUILD_GUIDE.md              # This simple build guide
├── Dockerfile                  # Docker image configuration
├── complete_build.sh           # Main build script
├── validate_build.sh           # Build validation script
└── UART5_Debug/                # Source code directory
    └── firmware/
        ├── src/                # Source files
        ├── Application/        # Application code
        ├── HAL/               # Hardware abstraction
        └── build/             # Build output (generated)
            ├── UART_Module.elf # Executable file
            └── UART_Module.hex # Programming file
```

## 🚀 Quick Build (30 seconds)

### Prerequisites
- Docker installed and running
- `free_rtos_v1:latest` Docker image available

### Build Commands
```bash
# Navigate to project directory
cd /home/ganesh/Myfolder/UART_MODULE

# Run the build
./complete_build.sh

# Validate the build (optional)
./validate_build.sh
```

## 📋 What Each Script Does

### `complete_build.sh`
- **Purpose**: Main build script
- **What it does**:
  - Sets up build environment
  - Creates system headers
  - Compiles source code using XC32 compiler
  - Links executable
  - Generates HEX file for programming
- **Output**: ELF and HEX files in `UART5_Debug/firmware/build/`

### `validate_build.sh`
- **Purpose**: Validates build results
- **What it does**:
  - Checks if output files exist
  - Validates file formats
  - Verifies file sizes
  - Shows memory usage
- **Output**: Build validation report

## 📊 Expected Results

### Successful Build Output
```
🚀 Starting UART Module Build Process
======================================
📋 Build Environment:
  - Compiler: pic32m-gcc (Microchip XC32 Compiler v4.35) 8.3.1
  - Project: /workspace/UART5_Debug/firmware
  - Build Dir: /workspace/UART5_Debug/firmware/build

🔨 Starting compilation...
  Compiling: sys_implementation.c -> sys_implementation.o
    ✅ Success
  Compiling: main.c -> main.o
    ✅ Success

🔗 Linking executable...
  ✅ Linking successful: UART_Module.elf

📦 Generating HEX file...
  ✅ HEX file generated: UART_Module.hex

🎉 Build completed successfully!
```

### Build Artifacts
- **UART_Module.elf** (~243KB) - Executable file with debug info
- **UART_Module.hex** (~7.5KB) - Intel HEX file for device programming

## 🔧 Troubleshooting

### Common Issues

#### Docker Image Not Found
```bash
# Check if image exists
docker images | grep free_rtos_v1

# If missing, build it:
docker build -t free_rtos_v1:latest .
```

#### Permission Issues
```bash
# Fix script permissions
chmod +x *.sh

# Fix Docker permissions
sudo usermod -aG docker $USER
newgrp docker
```

#### Build Fails
```bash
# Check Docker is running
docker ps

# Check project files exist
ls -la UART5_Debug/firmware/src/

# Run with verbose output
docker run --rm -v $(pwd):/workspace -w /workspace free_rtos_v1:latest bash -c "./complete_build.sh"
```

## 🎯 Usage Examples

### Basic Build
```bash
./complete_build.sh
```

### Build with Validation
```bash
./complete_build.sh && ./validate_build.sh
```

### Clean Build
```bash
# Remove previous build
rm -rf UART5_Debug/firmware/build/*

# Run fresh build
./complete_build.sh
```

## 📦 Using Build Artifacts

### Programming the Device
1. Use **UART_Module.hex** with MPLAB IPE
2. Target device: PIC32MX795F512L
3. Connect programmer (ICD4/PICkit4)
4. Program and verify

### File Information
- **ELF file**: Contains debug symbols, use for debugging
- **HEX file**: Intel HEX format, use for device programming
- **Memory usage**: ~1.7KB program memory

---

**Simple Local Build Guide**  
**Version**: 1.0  
**Last Updated**: July 25, 2025  
**Status**: Ready for Use ✅
