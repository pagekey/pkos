# pkos - PageKey Operating System

Welcome to PKOS! This is an operating system written completely from scratch, working its way up from assembly to higher level languages like C. This was created for educational purposes and documented in the OS Series from PageKey Tech

Check out the accomapnying video/blog article series: https://pagekeytech.com/projects/pkos.

## Docs

See the [docs folder](docs/) for all of the messy notes used to make these videos. You can open it as an Obsidian vault for a nicer experience. It'll also allow you to view the `.canvas` files properly.

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

## How to Debug and Set Breakpoints

1. Run `./scripts/docker_shell` to get into the container.

2. Run `./scripts/os.py run_debug` to start in debug mode.

3. In the GDB prompt in your terminal, type `whatever.c:1` to break when line 1 of `whatever.c` is executed.

## How to Create Bootable USB on Linux

1. Run `./scripts/docker_shell` to get into the container.

2. Run `./scripts/os.py build` build the OS.

3. Exit the container: `exit`

4. Plug in a USB drive that you don't mind erasing. Run `dmesg -w` before plugging it in to watch and see which device name it is assigned.

5. Run the following command (replace `/dev/sdx` with the USB device path):

```bash
dd if=dist/pkos.iso of=/dev/sdx
```

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

## Videos

[Full Playlist](https://www.youtube.com/playlist?list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW)

- [OS1: Installing VirtualBox & Debian on Windows](https://www.youtube.com/watch?v=NtZzb9ZJ5Fo&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=2)
  - tag: `vid/os001`
- [OS2: Running Our First Bootloader](https://www.youtube.com/watch?v=1lAuJoPZ3Q0&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=2)
  - tag: `vid/os002`
- [OS3: Hone the Power of the BIOS!](https://www.youtube.com/watch?v=W3DdyiO3Fy8&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=3)
  - tag: `vid/os003`
- [OS4: Deciphering BIOS Challenges](https://www.youtube.com/watch?v=9dU7CyKkHew&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=4)
  - tag: `vid/os004`
- [OS5: Going Over print_hex](https://www.youtube.com/watch?v=IvUl1ocS64g&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=5)
  - tag: `vid/os005`
- [OS6: Reading the Disk](https://www.youtube.com/watch?v=mktENQzbm6k&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=6)
  - tag: `vid/os006`
- [OS7: Making the Jump](https://www.youtube.com/watch?v=IU9zXYdYV9I&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=7)
  - tag: `vid/os007`
- [OS8: C at Last!](https://www.youtube.com/watch?v=5RWjI83C47k&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=8)
  - tag: `vid/os008`
- [OS9: Multiboot (Bootloader Breakup)](https://www.youtube.com/watch?v=UraQLWvn9Vg&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=9)
  - tag: `vid/os009`
- [OS10: Real Hardware](https://www.youtube.com/watch?v=-V-eKSKwexs&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=10)
  - tag: `vid/os010`
- [OS11: Calling Assembly from C](https://www.youtube.com/watch?v=ZsnKjqsFwwY&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=11)
  - tag: `vid/os011`
- [OS12: Basic Keyboard Driver (x86 Interrupts)](https://www.youtube.com/watch?v=YtnNX074jMU&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=12)
  - tag: `vid/os012`
- [OS13: Docker Dev Environment](https://www.youtube.com/watch?v=qN_24B2OJ5U&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=13)
  - tag: `vid/os013`
- [OS14: Organizing Our OS Code](https://www.youtube.com/watch?v=Qa-WjNWkNeA&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=14)
  - tag: `vid/os014`
- [OS15: Writing a Simple VGA Driver (Graphics)](https://www.youtube.com/watch?v=GllPGcVLEDY&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=15)
  - tag: `vid/os015`
- [OS16: Testing QEMU in CI/CD Using Pytest](https://www.youtube.com/watch?v=zcqJHKUKipg&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=16)
  - tag: `vid/os016`
  - MR: !1
- [OS17: Unit Testing C Code with Gtest, LCOV, Genhtml](https://www.youtube.com/watch?v=M4JG1Ej4x-c&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=17)
  - tag: `vid/os017`
  - MR: !2
- [OS18: Shredding the Makefile](https://www.youtube.com/watch?v=XLzVL8VA7Yc&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=18)
  - tag: `vid/os018`
  - MR: !3
- [OS19: More VGA, stdlib, mmeory](https://www.youtube.com/watch?v=E26AtZNIj8c&list=PL3Kz_hCNpKSTFCTJtP4-9mkYDVM7rAprW&index=19)
  - tag: `vid/os019`
  - MR: !4
