# pkos - PageKey Operating System

Welcome to PKOS! This is an operating system written completely from scratch, working its way up from assembly to higher level languages like C. This was created for educational purposes and documented in the [OS Series from PageKey Solutions on YouTube](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW).

## Quick Help

Try these commands to get started in a hurry.

* `make` - Build the OS

* `make run` - Run the OS in Qemu, an x86 emulator

* `make iso` - Build an ISO image of the OS. This file can be burned to a disk or USB drive. Then you can run it on real hardware!

## About This Repository 

This repository will hold all versions of PKOS, from the simplest to the latest. To follow along with the tutorial, each increment of the OS will be accessible to you as a "release" on GitHub. You just have to clone this repository and checkout the right tag for the video you watched. Then, you should be able to build the code and run it on your own system.

## Running the Code

Use the "Release Tag" listed below for the video you would like to run the code for. Replace `TAG` with the actual Release Tag in what's below:

```
git clone https://github.com/stephengrice/pkos
cd pkos
git checkout TAG
make
make run
```

## Videos

### [OS1: Installation](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os1`**

In this video, we go through the steps for installing VirtualBox so that we can develop our OS on a sandboxed Linux system. You can also use Windows Subsystem for Linux (WSL) or any other Linux system that you prefer.

There is no code for this tutorial - your only task is to go set up a Linux system somewhere so that we can install all of the required software!
