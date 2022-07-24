FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y \
    build-essential \
    gdb \
    git \
    grub2-common \
    grub-pc-bin \
    libgtest-dev \
    nasm \
    qemu-system-i386 \
    xorriso \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists

WORKDIR /pkos

COPY requirements.txt .
RUN pip install -r requirements.txt
