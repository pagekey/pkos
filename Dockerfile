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
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos

RUN pip install -r test/requirements.txt
