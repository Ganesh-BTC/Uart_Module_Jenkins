# Use Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Enable i386 architecture for 32-bit support
RUN dpkg --add-architecture i386

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Update system and install required dependencies in a single step
RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y --no-install-recommends \
    make cmake libc6:i386 libx11-6:i386 libxext6:i386 libstdc++6:i386 libexpat1:i386 && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Create Jenkins user
RUN useradd jenkins

# Copy the Microchip archive into the container
COPY ./jenkins/microchip.tar.gz /tmp/

# Extract the libraries and binaries
RUN tar xzf /tmp/microchip.tar.gz -C / && rm /tmp/microchip.tar.gz


# Ensure correct permissions for the XC32 license manager
RUN if [ -f "/opt/microchip/xc32/v4.35/bin/xclm" ]; then \
        chown root:root /opt/microchip/xc32/v4.35/bin/xclm && chmod 4755 /opt/microchip/xc32/v4.35/bin/xclm; \
    else \
        echo "Warning: xclm not found, skipping permissions update."; \
    fi

# Switch to the Jenkins user for safer builds
USER jenkins

# Default command to start a shell session
CMD ["/bin/bash"]
