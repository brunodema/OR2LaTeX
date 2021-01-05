#!/bin/bash
sudo apt update 
sudo apt upgrade -y
sudo apt install -y clang-tidy clang-format clangd
mkdir dep/ortools
sudo wget -O- https://github.com/google/or-tools/releases/download/v8.1/or-tools_flatzinc_ubuntu-20.04_v8.1.8487.tar.gz | sudo tar -xvz -C dep/ortools --strip-components 1
sudo apt update 
sudo apt upgrade -y