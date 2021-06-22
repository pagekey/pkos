FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt update && apt install -y \
    vim git \
    build-essential nasm qemu-system-i386 \
    && rm -rf /var/lib/apt/lists/*