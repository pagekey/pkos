FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN dpkg --add-architecture i386
RUN apt update && apt install -y \
    build-essential \
    g++-multilib \
    gcc-multilib \
    gdb \
    git \
    grub2-common \
    grub-pc-bin \
    lcov \
    libgtest-dev:i386 \
    nasm \
    qemu-system-i386 \
    xorriso \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos

COPY requirements.txt .
RUN pip install -r requirements.txt
