FROM ubuntu:22.04

LABEL maintainer="krushna@example.com"
LABEL description="Docker image for PIC32 development with XC32 and Harmony v2"

# Install base dependencies and 32-bit compatibility libs for XC32
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    curl \
    libncurses5 \
    libx11-6 \
    libxext6 \
    libxtst6 \
    libxi6 \
    lib32z1 \
    lib32ncurses6 \
    lib32stdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Copy and extract XC32 compiler
COPY xc32-v2.10.tar.gz /opt/
RUN mkdir -p /opt/microchip/xc32 && \
    tar -xzf /opt/xc32-v2.10.tar.gz -C /opt/microchip/xc32 && \
    rm /opt/xc32-v2.10.tar.gz

# Add compiler to PATH
ENV PATH="/opt/microchip/xc32/xc32-v2.10/v2.10/bin:$PATH"

# Set working directory
WORKDIR /workspace

# Default shell
CMD ["/bin/bash"]

