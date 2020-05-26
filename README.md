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

### [OS2: First Bootloader](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os2`**

### [OS3: Hone the Power of the BIOS!](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os3`**

### [OS4: Deciphering BIOS Challenges](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os4`**

### [OS5: Going Over print_hex](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os5`**

### [OS6: Reading the Disk](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os6`**

### [OS7: Making the Jump!](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

**Release Tag: `os7`**

## Resources

Aside from a ton of StackOverflow answers, the following were super helpful in pulling together the information for these lessons:

* [os-dev PDF from University of Birmingham (Nick Blundell)](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)

* [os-tutorial by cfenollosa on GitHub](https://github.com/cfenollosa/os-tutorial)

* [Ralph Brown's BIOS Interrupt List (Download)](http://www.cs.cmu.edu/~ralf/files.html)
~                                                                                         
