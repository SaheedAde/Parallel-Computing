FROM ubuntu:20.10

LABEL maintainer="Sascha Hunold <sascha.hunold@tuwien.ac.at>"

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    curl \
    git \
    make \
    cmake \
    vim \
    wget \
    gcc \
    gdb \
    valgrind \
    mpich \
    libpng-dev \
    python3 \
    python3-matplotlib \
    python3-numpy \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/* \
 && update-alternatives --install /usr/bin/python python /usr/bin/python3 1

