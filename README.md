# UART Module - PIC32MX795F512L Embedded Project

## 📋 Table of Contents
1. [Project Overview](#project-overview)
2. [Prerequisites](#prerequisites)
3. [Project Structure](#project-structure)
4. [Build Environment Setup](#build-environment-setup)
5. [Manual Build Process](#manual-build-process)
6. [Jenkins Pipeline Setup](#jenkins-pipeline-setup)
7. [Troubleshooting](#troubleshooting)
8. [Development Workflow](#development-workflow)

## 🎯 Project Overview

This is an embedded firmware project for the PIC32MX795F512L microcontroller, implementing UART communication functionality. The project uses the Microchip XC32 compiler and is designed to be built in a containerized environment for consistent, reproducible builds.

### Key Features
- **Target MCU**: PIC32MX795F512L (MIPS32r2 architecture)
- **Communication**: UART5 Debug interface
- **Build System**: Docker-based with XC32 compiler
- **Output**: Intel HEX format for device programming

### Technical Specifications
- **Compiler**: Microchip XC32 v4.35
- **Architecture**: 32-bit MIPS
- **Memory Usage**: ~1.7KB program memory
- **Build Environment**: Ubuntu 22.04 based Docker container

## 🔧 Prerequisites

### Required Software
- **Docker**: Version 20.10 or later
- **Git**: For version control
- **Text Editor**: VS Code, Vim, or similar

### Required Hardware (for programming)
- PIC32MX795F512L development board
- MPLAB ICD/PICkit programmer
- USB cables for programming interface

### Docker Image
The project uses a pre-built Docker image: `free_rtos_v1:latest`

**Image Contents:**
- Ubuntu 22.04 base
- Microchip XC32 Compiler v4.35
- MPLAB X tools
- Required 32-bit libraries

## 📁 Project Structure

```
UART_MODULE/
├── README.md                           # This documentation
├── Dockerfile                          # Docker image configuration
├── jenkins/
│   └── microchip.tar.gz               # Microchip toolchain archive (169MB)
├── UART5_Debug/
│   └── firmware/
│       ├── build/                     # Build output directory
│       │   ├── UART_Module.elf       # Executable file
│       │   └── UART_Module.hex       # Programming file
│       ├── Application/               # Application layer
│       │   ├── include/
│       │   └── src/
│       │       └── App_DebugPrint.c
│       ├── HAL/                       # Hardware Abstraction Layer
│       │   ├── include/
│       │   └── src/
│       │       └── HAL_UartPrint.c
│       ├── src/                       # System source files
│       │   ├── main.c                # Main application entry
│       │   ├── app.c                 # Application logic
│       │   ├── init.c                # Initialization
│       │   └── system_config/        # System configuration
│       ├── include/                   # Global headers
│       ├── CMakeLists.txt            # CMake build configuration
│       └── Dockerfile                # Firmware-specific Docker config
├── build_scripts/                     # Build automation scripts
│   ├── complete_build.sh             # Main build script
│   ├── validate_build.sh             # Build validation
│   └── clean_build.sh                # Clean build environment
├── jenkins/                           # Jenkins pipeline files
│   ├── Jenkinsfile                   # Pipeline definition
│   └── pipeline-config.yaml         # Pipeline configuration
└── docs/                             # Additional documentation
    ├── BUILD_SUMMARY.md              # Detailed build information
    └── PROGRAMMING_GUIDE.md          # Device programming guide
```

## 🐳 Build Environment Setup

### 1. Verify Docker Installation

```bash
# Check Docker version
docker --version

# Verify Docker is running
docker info

# Test Docker with hello-world
docker run hello-world
```

### 2. Verify Docker Image

```bash
# Check if the Docker image exists
docker images | grep free_rtos_v1

# If image doesn't exist, build it from Dockerfile
cd /path/to/UART_MODULE
docker build -t free_rtos_v1:latest .
```

### 3. Set Up Project Directory

```bash
# Clone or navigate to project directory
cd /home/ganesh/Myfolder/UART_MODULE

# Verify project structure
ls -la

# Make build scripts executable
chmod +x build_scripts/*.sh
```

## 🔨 Manual Build Process

### Quick Build (Recommended)

```bash
# Navigate to project root
cd /home/ganesh/Myfolder/UART_MODULE

# Run the complete build script
docker run --rm --privileged -u $(id -u):$(id -g) \
           -v $(pwd):/workspace -w /workspace \
           free_rtos_v1:latest bash -c "./complete_build.sh"
```

### Step-by-Step Build Process

#### Step 1: Clean Previous Build

```bash
# Remove previous build artifacts
rm -rf UART5_Debug/firmware/build/*
mkdir -p UART5_Debug/firmware/build
```

#### Step 2: Start Docker Container

```bash
# Start interactive Docker container
docker run -it --privileged -u $(id -u):$(id -g) \
           -v $(pwd):/workspace -w /workspace \
           free_rtos_v1:latest bash
```

#### Step 3: Set Up Build Environment (Inside Container)

```bash
# Set up compiler path
export PATH="/microchip/xc32/v4.35/bin:$PATH"

# Verify compiler installation
xc32-gcc --version

# Navigate to build directory
cd UART5_Debug/firmware/build
```

#### Step 4: Create System Headers (Inside Container)

```bash
# Create minimal system structure
mkdir -p system/common

# Create sys_module.h
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
```

#### Step 5: Compile Source Files (Inside Container)

```bash
# Compiler flags
CFLAGS="-mprocessor=32MX795F512L -O1 -ffunction-sections -fdata-sections -Wall"
LDFLAGS="-Wl,--gc-sections"

# Include directories
INCLUDES="-I. -I../include -I../Application/include -I../HAL/include -I../src"

# Compile system implementation
xc32-gcc $CFLAGS $INCLUDES -c sys_implementation.c -o sys_implementation.o

# Compile main application
xc32-gcc $CFLAGS $INCLUDES -c ../src/main.c -o main.o
```

#### Step 6: Link and Generate Output (Inside Container)

```bash
# Link object files
xc32-gcc $CFLAGS $LDFLAGS sys_implementation.o main.o -o UART_Module.elf

# Generate HEX file
xc32-bin2hex UART_Module.elf

# Verify output files
ls -la UART_Module.*
```

#### Step 7: Validate Build

```bash
# Exit Docker container
exit

# Run validation script
./build_scripts/validate_build.sh
```

### Build Output

After successful build, you should have:

```
UART5_Debug/firmware/build/
├── UART_Module.elf    # Executable file (243KB)
├── UART_Module.hex    # Programming file (7.5KB)
└── build artifacts    # Intermediate files
```

## 🔄 Jenkins Pipeline Setup

### 1. Jenkins Prerequisites

#### Required Jenkins Plugins
```bash
# Install these plugins in Jenkins
- Docker Pipeline Plugin
- Git Plugin
- Pipeline Plugin
- Blue Ocean (optional, for better UI)
- Workspace Cleanup Plugin
```

#### Jenkins System Configuration
```bash
# Configure Docker in Jenkins
Manage Jenkins → Global Tool Configuration → Docker
- Name: docker
- Installation root: /usr/bin/docker

# Configure Git
Manage Jenkins → Global Tool Configuration → Git
- Name: Default
- Path to Git executable: git
```

### 2. Create Jenkins Pipeline

#### Option A: Pipeline from SCM (Recommended)

1. **Create New Pipeline Job**
   ```
   Jenkins Dashboard → New Item → Pipeline → Enter name: "UART_Module_Build"
   ```

2. **Configure Pipeline**
   ```
   Pipeline Definition: Pipeline script from SCM
   SCM: Git
   Repository URL: https://github.com/your-username/uart-module.git
   Branch: */main
   Script Path: jenkins/Jenkinsfile
   ```

#### Option B: Direct Pipeline Script

Create a new Pipeline job and paste the following script:

```groovy
pipeline {
    agent any
    
    environment {
        DOCKER_IMAGE = 'free_rtos_v1:latest'
        PROJECT_NAME = 'UART_Module'
        BUILD_DIR = 'UART5_Debug/firmware/build'
    }
    
    stages {
        stage('Checkout') {
            steps {
                checkout scm
                echo 'Source code checked out successfully'
            }
        }
        
        stage('Verify Environment') {
            steps {
                script {
                    sh '''
                        echo "=== Environment Verification ==="
                        docker --version
                        docker images | grep free_rtos_v1 || echo "Docker image not found"
                        ls -la
                    '''
                }
            }
        }
        
        stage('Clean Build') {
            steps {
                script {
                    sh '''
                        echo "=== Cleaning Previous Build ==="
                        rm -rf ${BUILD_DIR}/*
                        mkdir -p ${BUILD_DIR}
                        echo "Build directory cleaned"
                    '''
                }
            }
        }
        
        stage('Build Firmware') {
            steps {
                script {
                    sh '''
                        echo "=== Building UART Module Firmware ==="
                        docker run --rm --privileged \
                                   -u $(id -u):$(id -g) \
                                   -v $(pwd):/workspace \
                                   -w /workspace \
                                   ${DOCKER_IMAGE} \
                                   bash -c "./complete_build.sh"
                    '''
                }
            }
        }
        
        stage('Validate Build') {
            steps {
                script {
                    sh '''
                        echo "=== Validating Build Output ==="
                        ./validate_build.sh
                    '''
                }
            }
        }
        
        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: "${BUILD_DIR}/UART_Module.elf, ${BUILD_DIR}/UART_Module.hex", 
                                fingerprint: true
                echo 'Build artifacts archived successfully'
            }
        }
        
        stage('Generate Reports') {
            steps {
                script {
                    sh '''
                        echo "=== Generating Build Report ==="
                        echo "Build Date: $(date)" > build_report.txt
                        echo "Build Number: ${BUILD_NUMBER}" >> build_report.txt
                        echo "Git Commit: $(git rev-parse HEAD)" >> build_report.txt
                        
                        if [ -f "${BUILD_DIR}/UART_Module.elf" ]; then
                            echo "ELF Size: $(stat -c%s ${BUILD_DIR}/UART_Module.elf) bytes" >> build_report.txt
                        fi
                        
                        if [ -f "${BUILD_DIR}/UART_Module.hex" ]; then
                            echo "HEX Size: $(stat -c%s ${BUILD_DIR}/UART_Module.hex) bytes" >> build_report.txt
                        fi
                        
                        cat build_report.txt
                    '''
                }
                archiveArtifacts artifacts: "build_report.txt", fingerprint: true
            }
        }
    }
    
    post {
        always {
            cleanWs()
        }
        success {
            echo 'Build completed successfully!'
            // Add notification here (email, Slack, etc.)
        }
        failure {
            echo 'Build failed!'
            // Add failure notification here
        }
    }
}
```

### 3. Advanced Jenkins Configuration

#### Multi-Branch Pipeline

For projects with multiple branches, create a Multi-branch Pipeline:

```groovy
// jenkins/Jenkinsfile for multi-branch
pipeline {
    agent any
    
    parameters {
        choice(
            name: 'BUILD_TYPE',
            choices: ['Debug', 'Release'],
            description: 'Select build type'
        )
        booleanParam(
            name: 'CLEAN_BUILD',
            defaultValue: true,
            description: 'Perform clean build'
        )
    }
    
    environment {
        DOCKER_IMAGE = 'free_rtos_v1:latest'
        BUILD_TYPE = "${params.BUILD_TYPE}"
    }
    
    stages {
        stage('Build') {
            when {
                anyOf {
                    branch 'main'
                    branch 'develop'
                    branch 'feature/*'
                }
            }
            steps {
                script {
                    if (params.CLEAN_BUILD) {
                        sh 'rm -rf UART5_Debug/firmware/build/*'
                    }
                    
                    sh '''
                        docker run --rm --privileged \
                                   -u $(id -u):$(id -g) \
                                   -v $(pwd):/workspace \
                                   -w /workspace \
                                   -e BUILD_TYPE=${BUILD_TYPE} \
                                   ${DOCKER_IMAGE} \
                                   bash -c "./complete_build.sh"
                    '''
                }
            }
        }
    }
}
```

#### Parallel Builds

For building multiple configurations:

```groovy
stage('Parallel Builds') {
    parallel {
        stage('Debug Build') {
            steps {
                script {
                    sh '''
                        docker run --rm --privileged \
                                   -v $(pwd):/workspace \
                                   -w /workspace \
                                   -e BUILD_TYPE=Debug \
                                   ${DOCKER_IMAGE} \
                                   bash -c "./complete_build.sh"
                    '''
                }
            }
        }
        stage('Release Build') {
            steps {
                script {
                    sh '''
                        docker run --rm --privileged \
                                   -v $(pwd):/workspace \
                                   -w /workspace \
                                   -e BUILD_TYPE=Release \
                                   ${DOCKER_IMAGE} \
                                   bash -c "./complete_build.sh"
                    '''
                }
            }
        }
    }
}
```

## 🔧 Troubleshooting

### Common Issues and Solutions

#### 1. Docker Permission Issues

**Problem**: Permission denied when running Docker commands

**Solution**:
```bash
# Add user to docker group
sudo usermod -aG docker $USER

# Restart session or run
newgrp docker

# Verify Docker access
docker run hello-world
```

#### 2. XC32 License Issues

**Problem**: XCLM license manager errors

**Solution**:
```bash
# Run Docker with privileged mode
docker run --rm --privileged -u root \
           -v $(pwd):/workspace -w /workspace \
           free_rtos_v1:latest bash -c "
           chown root:root /microchip/xc32/v4.35/bin/xclm
           chmod 4755 /microchip/xc32/v4.35/bin/xclm
           "
```

#### 3. Missing Dependencies

**Problem**: Compilation fails due to missing headers

**Solution**:
```bash
# Verify Docker image contents
docker run --rm free_rtos_v1:latest bash -c "
    find /microchip -name 'xc32-gcc'
    ls -la /microchip/xc32/v4.35/bin/
"

# Rebuild Docker image if necessary
docker build -t free_rtos_v1:latest .
```

#### 4. Build Artifacts Not Generated

**Problem**: ELF or HEX files not created

**Solution**:
```bash
# Check build logs for errors
docker run --rm -v $(pwd):/workspace -w /workspace \
           free_rtos_v1:latest bash -c "./complete_build.sh" 2>&1 | tee build.log

# Verify compiler output
grep -i error build.log
grep -i warning build.log
```

#### 5. Jenkins Build Failures

**Problem**: Jenkins pipeline fails

**Solution**:
```bash
# Check Jenkins logs
# Go to Jenkins → Build → Console Output

# Common fixes:
# 1. Verify Docker is available in Jenkins
# 2. Check workspace permissions
# 3. Ensure Docker image is available on Jenkins node
# 4. Verify build scripts are executable
```

## 🚀 Development Workflow

### 1. Local Development

```bash
# 1. Make code changes
vim UART5_Debug/firmware/src/main.c

# 2. Test build locally
./complete_build.sh

# 3. Validate build
./validate_build.sh

# 4. Commit changes
git add .
git commit -m "Update UART functionality"
git push origin feature/uart-update
```

### 2. Continuous Integration

```bash
# 1. Create feature branch
git checkout -b feature/new-functionality

# 2. Make changes and commit
git add .
git commit -m "Add new functionality"

# 3. Push to trigger Jenkins build
git push origin feature/new-functionality

# 4. Monitor Jenkins build
# Check Jenkins dashboard for build status

# 5. Merge after successful build
git checkout main
git merge feature/new-functionality
```

### 3. Release Process

```bash
# 1. Create release branch
git checkout -b release/v1.0.0

# 2. Update version information
echo "v1.0.0" > VERSION

# 3. Build and test
./complete_build.sh
./validate_build.sh

# 4. Tag release
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0

# 5. Deploy artifacts from Jenkins
# Download artifacts from Jenkins build
# Program device using UART_Module.hex
```

## 📚 Additional Resources

### Documentation Files
- `BUILD_SUMMARY.md` - Detailed build information
- `PROGRAMMING_GUIDE.md` - Device programming instructions
- `API_REFERENCE.md` - Code API documentation

### Useful Commands

```bash
# View build logs
tail -f jenkins/logs/build.log

# Check Docker container status
docker ps -a

# Clean Docker system
docker system prune -f

# Monitor build progress
watch -n 1 'ls -la UART5_Debug/firmware/build/'

# Extract build information
xc32-objdump -h UART_Module.elf
xc32-size UART_Module.elf
```

### External Links
- [Microchip XC32 Compiler Documentation](https://www.microchip.com/xc32)
- [PIC32MX795F512L Datasheet](https://www.microchip.com/pic32mx)
- [Jenkins Pipeline Documentation](https://jenkins.io/doc/book/pipeline/)
- [Docker Documentation](https://docs.docker.com/)

---

**Project**: UART Module for PIC32MX795F512L  
**Version**: 1.0.0  
**Last Updated**: July 25, 2025  
**Author**: Ganesh  
**Build System**: Docker + Jenkins CI/CD
