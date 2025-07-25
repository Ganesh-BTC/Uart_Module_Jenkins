pipeline {
    agent any
    
    environment {
        DOCKER_IMAGE = 'free_rtos_v1:latest'
    }
    
    options {
        timeout(time: 30, unit: 'MINUTES')
        timestamps()
    }
    
    stages {
        stage('Git Code Checkout') {
            steps {
                echo '=== Git Code Checkout ==='
                cleanWs()
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/main']],
                    userRemoteConfigs: [[url: 'https://github.com/Ganesh-BTC/Uart_Module_Jenkins.git']]
                ])
                echo '✅ Code checked out successfully'
            }
        }
        
        stage('Build Code') {
            steps {
                echo '=== Build Code ==='
                sh '''
                    # Verify environment
                    docker images | grep -q free_rtos_v1 || { echo "❌ Docker image not found"; exit 1; }
                    [ -f "./complete_build.sh" ] || { echo "❌ Build script not found"; exit 1; }
                    
                    # Build firmware
                    chmod +x *.sh
                    docker run --rm --privileged \\
                               -u $(id -u):$(id -g) \\
                               -v $(pwd):/workspace \\
                               -w /workspace \\
                               ${DOCKER_IMAGE} \\
                               bash -c "./complete_build.sh"
                '''
                echo '✅ Build completed'
            }
        }
        
        stage('Save Artifacts') {
            steps {
                echo '=== Save Artifacts ==='
                sh '''
                    mkdir -p artifacts
                    
                    # Copy ELF file (CMake generates without .elf extension)
                    if [ -f "UART5_Debug/firmware/build/UART_Module" ]; then
                        cp UART5_Debug/firmware/build/UART_Module artifacts/UART_Module.elf
                        echo "✅ ELF file saved to artifacts"
                    else
                        echo "⚠️ ELF not found"
                    fi
                    
                    # Copy HEX file
                    if [ -f "UART5_Debug/firmware/build/UART_Module.hex" ]; then
                        cp UART5_Debug/firmware/build/UART_Module.hex artifacts/
                        echo "✅ HEX file saved to artifacts"
                    else
                        echo "⚠️ HEX not found"
                    fi
                    
                    # Create Jenkins build log
                    cat > artifacts/jenkins_build.log << EOL
=== Jenkins Build Log ===
Build Number: ${BUILD_NUMBER}
Build Date: $(date)
Repository: https://github.com/Ganesh-BTC/Uart_Module_Jenkins.git
Git Commit: ${GIT_COMMIT}
Jenkins Job: ${JOB_NAME}
Jenkins URL: ${BUILD_URL}

Build Results:
EOL
                    
                    # Add file info to log
                    if [ -f "artifacts/UART_Module.elf" ]; then
                        echo "✅ ELF File: $(stat -c%s artifacts/UART_Module.elf) bytes" >> artifacts/jenkins_build.log
                    fi
                    if [ -f "artifacts/UART_Module.hex" ]; then
                        echo "✅ HEX File: $(stat -c%s artifacts/UART_Module.hex) bytes" >> artifacts/jenkins_build.log
                    fi
                    
                    echo "Build Status: SUCCESS" >> artifacts/jenkins_build.log
                '''
                archiveArtifacts artifacts: 'artifacts/*', allowEmptyArchive: true
                echo '✅ Artifacts and build log saved'
            }
        }
    }
    
    post {
        always {
            sh 'docker container prune -f || true'
        }
        success {
            echo '🎉 Pipeline completed successfully!'
        }
        failure {
            echo '❌ Pipeline failed!'
        }
    }
}
