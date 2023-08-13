FROM brett/gcc-cross-x86_64-elf

# Update package lists and install packages
RUN sed -i 's/stretch/buster/g' /etc/apt/sources.list && \
    apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y nasm xorriso grub-pc-bin grub-common

VOLUME /root/env
WORKDIR /root/env
