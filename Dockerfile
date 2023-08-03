FROM ubuntu:23.04

ENV DEBIAN_FRONTEND noninteractive

RUN dpkg --add-architecture i386
RUN apt update && apt install -y \
    build-essential \
    g++-multilib \
    gcc-multilib \
    gdb \
    ghex \
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
    python3-venv \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos

COPY requirements.txt .

RUN python3 -m venv venv \
    && . venv/bin/activate \
    && pip install --upgrade pip \
    && pip install -r requirements.txt
