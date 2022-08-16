# pkos - PageKey Operating System

Welcome to PKOS! This is an operating system written completely from scratch, working its way up from assembly to higher level languages like C. This was created for educational purposes and documented in the OS Series from PageKey Tech

Check out the accomapnying video/blog article series: https://pagekeytech.com/projects/pkos.

## Getting Started

Try these commands to get started in a hurry.

1. Ensure you have `docker` and `docker-compose` installed and ready to go on your system.

2. Run `./scripts/docker_shell` to build the dev environment and get a shell inside of it to work in.

3. From inside the system, run the OS with: `./scripts/os.py run`.

## Commands

Run `./scripts/os.py` with no arguments to list the usage. It includes subcommands for building, testing, and running the OS.

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
git clone https://gitlab.com/pagekeytech/pkos
cd pkos
git checkout (whichever tag)
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
docker login registry.gitlab.com
docker-compose build
docker-compose push
```

## Running Tests

- Integration tests:
  - `pip install -r requirements.txt`
  - `pytest`
- Unit tests:
  - `./scripts/test_unit`
  - Use `NOCOV=1 ./scripts/test_unit` to skip coverage
