FROM adoptopenjdk/openjdk11:jdk-11.0.11_9-debian

RUN DEBIAN_FRONTEND="noninteractive"  apt-get update && apt-get install -y tar

RUN apt-get update \
  && apt-get install -y build-essential \
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

RUN pip3 install conan

RUN conan remote add ecdc https://artifactoryconan.esss.dk/artifactory/api/conan/ecdc \
    && conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan

ENV CONAN_REVISIONS_ENABLED=1

RUN apt-get update && apt-get install -y pkg-config && apt-get clean

ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

CMD ["/bin/bash"]