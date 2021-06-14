FROM adoptopenjdk/openjdk11:jdk-11.0.11_9-debian

RUN DEBIAN_FRONTEND="noninteractive"  apt-get update && apt-get install -y tar git

RUN apt-get update \
  && apt-get install -y build-essential \
      pkg-config \
      gcc \
      g++ \
      gdb \
      clang \
      cmake \
      rsync \
  && apt-get clean

RUN apt-get update \
  && apt-get install -y doxygen \
        libboost-program-options-dev \
        libboost-system-dev \
        libboost-test-dev \
        libboost-regex-dev \
        libboost-filesystem-dev \
        libboost-date-time-dev \
        libhdf5-dev \
        libgtest-dev \
  && apt-get clean

RUN git clone --depth 1 -b v0.4.0 https://github.com/ess-dmsc/h5cpp.git

WORKDIR h5cpp

RUN mkdir build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release -DCONAN=DISABLE .. \
    && make install

WORKDIR /

RUN git clone --depth 1 -b v1.1.1 https://github.com/pni-libraries/libpnicore.git

WORKDIR libpnicore

RUN git clone --depth 1 https://github.com/pni-libraries/cmake.git cmake/common


RUN mkdir build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make install

WORKDIR /

RUN git clone --depth 1 -b v1.3.1 https://github.com/pni-libraries/libpniio.git

WORKDIR libpniio

RUN git clone --depth 1 https://github.com/pni-libraries/cmake.git cmake/common

RUN mkdir build \
    && cd build \
    && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make install

WORKDIR /

ENV LD_LIBRARY_PATH=/usr/local/lib

ENV PKG_CONFIG_PATH=/usr/local/lib/pkgconfig