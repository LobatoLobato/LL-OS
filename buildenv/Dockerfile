FROM homebrew/ubuntu20.04

RUN sudo apt-get update && sudo apt-get upgrade -y
RUN sudo apt-get install -y nasm
RUN sudo apt-get install -y xorriso
RUN sudo apt-get install -y grub-pc-bin
RUN sudo apt-get install -y grub-common

RUN brew install x86_64-elf-gcc

VOLUME  /root/env
WORKDIR /root/env
