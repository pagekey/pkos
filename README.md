# pkos - PageKey Operating System

Welcome to PKOS! This is an operating system written completely from scratch, working its way up from assembly to higher level languages like C. This was created for educational purposes and documented in the OS Series from PageKey Solutions

Check out the accomapnying video/blog article series: https://pagekeytech.com/projects/pkos.

## Getting Started

Try these commands to get started in a hurry.

- `docker-compose up` - Build and run the OS (added in OS13)
  - You must have Docker/`docker-compose` installed and configured for GUI applications to run within a container.
  - Also available:
    - `scripts/docker_build`: (Re)build your Docker dev container with the latest `Dockerfile`
    - `scripts/docker_run`: Same as `docker-compose up` - run it now
    - `scripts/docker_shell`: Get a shell inside the docker environment to do as you please
- `make` - Build the OS
- `make run` - Run the OS in Qemu, an x86 emulator
- `make iso` - Build an ISO image of the OS. This file can be burned to a disk or USB drive. Then you can run it on real hardware!

## Troubleshooting

- If you're getting errors initializing the display when using Docker:
  - Try the following if you're on Mac or Linux: `xhost local:root`
  - If you're on Windows, make sure that you have an X11 server installed and running.
    - Try [xming](https://sourceforge.net/projects/xming/) or [VcXsrv](https://sourceforge.net/projects/vcxsrv/)

## About This Repository 

This repository will hold all versions of PKOS, from the simplest to the latest. To follow along with the tutorial, each increment of the OS will be accessible to you as a "release" on GitHub. You just have to clone this repository and checkout the right tag for the video you watched. Then, you should be able to build the code and run it on your own system.

## Running the Code

Use the "Release Tag" listed below for the video you would like to run the code for. Replace `TAG` with the actual Release Tag in what's below:

```bash
git clone https://github.com/stephengrice/pkos
cd pkos
git checkout TAG
make
make run
```

## Resources

Aside from a ton of StackOverflow answers, the following were super helpful in pulling together the information for these lessons:

* [os-dev PDF from University of Birmingham (Nick Blundell)](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
* [os-tutorial by cfenollosa on GitHub](https://github.com/cfenollosa/os-tutorial)
* [Ralph Brown's BIOS Interrupt List (Download)](http://www.cs.cmu.edu/~ralf/files.html)

More sources are availble on the writeup for each post in [the series](https://pagekeytech.com/projects/pkos).

## Building the Docker Image

The Docker image is built manually and pushed to GitLab. The following steps are used to do that:

```bash
docker login registry.gitlab.com:443
docker-compose build
docker-compose push
```
