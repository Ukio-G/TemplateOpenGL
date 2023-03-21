#!/bin/bash

# dependency.sh - A script to install dependencies for OpenGL template project
# Supports Arch Linux, Debian, CentOS, Fedora, and macOS (using Homebrew)

# Check for supported operating systems
if [ -f /etc/os-release ]; then
    # freedesktop.org and systemd
    . /etc/os-release
    OS=$NAME
    # VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
    # linuxbase.org
    OS=$(lsb_release -si)
    # VER=$(lsb_release -sr)
else
    OS=$(uname -s)
fi

# macOS case
if [ "$OS" = "Darwin" ]; then
    OS="macOS"
fi

echo "Detected OS: $OS"

install_dependencies() {
    echo "Installing dependencies for $1..."
    eval "$2"
    echo "Dependencies installed."
}

# Install dependencies based on the detected OS
case "$OS" in
    "Arch Linux")
        install_dependencies "Arch Linux" "sudo pacman -S --needed glfw glew glm glfw-x11"
        ;;

    "Debian" | "Ubuntu")
        install_dependencies "Debian/Ubuntu" "sudo apt-get update && sudo apt-get install -y libglfw3-dev libglew-dev libglm-dev libstb-dev libglfw3"
        ;;

    "CentOS")
        sudo yum -y install epel-release
        install_dependencies "CentOS" "sudo yum -y install glfw-devel glew-devel glm-devel glfw"
        ;;

    "Fedora")
        install_dependencies "Fedora" "sudo dnf -y install glfw-devel glew-devel glm-devel glfw"
        ;;

    "macOS")
        if ! command -v brew &> /dev/null; then
            echo "Error: Homebrew is not installed. Please install Homebrew from https://brew.sh and try again."
            exit 1
        fi
        install_dependencies "macOS" "brew install glfw glew glm stb"
        ;;

    *)
        echo "Error: Unsupported OS. This script supports Arch Linux, Debian, Ubuntu, CentOS, Fedora, and macOS."
        exit 1
        ;;
esac