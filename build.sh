#!/bin/bash

set +e

echo_info() {
    echo -e "\e[32m[INFO]\e[0m $1"
}

echo_error() {
    echo -e "\e[31m[ERROR]\e[0m $1"
}


command_exits() {
    command -v "$1" >/dev/null 2>$1
}


if [[ "$EUID" -ne 0 ]]; then

    echo_error "run script with sudo or as root"
    exit 1

fi

echo_info "Updating package index..."
apt-get update

# Some packages could not update
if [ $? -ne 0 ]; then
    echo_error "Warning: Some repositories could not be updated."
fi

echo_info "Installing openssl-dev..."
apt-get install -y libcurl4-openssl-dev

set -e 


echo_info "Installing dependencies..."
apt-get install -y build-essential
apt-get install -y libjansson-dev
apt-get install -y pkg-config
apt-get install -y libssl-dev
apt-get install -y python3-pip

echo_info "All dependencies installed successfully."
