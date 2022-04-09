FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y \
    build-essential \
    gdb \
    git \
    grub2-common \
    grub-pc-bin \
    nasm \
    qemu-system-i386 \
    xorriso \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos