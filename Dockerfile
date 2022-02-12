FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y \
    build-essential \
    git \
    grub2-common \
    nasm \
    qemu-system-i386 \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos