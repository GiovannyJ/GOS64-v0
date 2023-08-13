# GOS64-v0

## About
This project involves creating a basic operating system using ASM and C. The main purpose of this OS is to display the text "OK" on the screen after the booting process. While this project may seem minimal, it serves as a foundational stepping stone for future projects that delve deeper into OS development.

## Requirements
Before getting started, ensure that you have the following tools installed:

1. Docker
2. QEMU

## How to Run
Follow these steps to run the simple OS:

### 1. Create Docker Container
```sh
docker build buildenv -t YOU_NAME_IT
```

### 2. attach docker container to local env
```sh
BASH:
docker run --rm -it -v %cd%:/root/env myos-buildenv

POWERSHELL:
docker run --rm -it -v ${PWD}:/root/env myos-buildenv

-MAC/LINUX:
docker run --rm -it -v $(pwd):/root/env myos-buildenv
```

### 3. run the make command inside the docker attached terminal order to create the iso file
```sh
make build-x86_64
```
### 4. run the ISO using qemu in your local terminal
```sh
qemu-system-x86_64 -cdrom .\dist\x86_64\kernel.iso 
```