FROM debian:stretch AS dependencies

RUN apt-get update && apt-get install -y \
  apt-utils                              \
  build-essential                        \
  pkg-config				 \
  cmake                                  \
  curl                                   \
  git                                    \
  lsb-release                            \
  libboost-system-dev                    \
  libboost-regex-dev                     \
  libboost-program-options-dev           \
  libboost-date-time-dev                 \
  libboost-filesystem-dev                \
  libboost-test-dev                      \
  libcppunit-dev			 \
  libhdf5-dev

FROM dependencies AS pnicore

RUN git clone -b 1.0.X https://github.com/pni-libraries/libpnicore.git

WORKDIR libpnicore

RUN mkdir build

WORKDIR build

RUN cmake -DCMAKE_INSTALL_PREFIX=/opt/pni ..

RUN make install


FROM dependencies AS pniio

RUN git clone https://github.com/pni-libraries/libpniio.git

WORKDIR libpniio

RUN git checkout v1.1.1 && mkdir build

WORKDIR build

COPY --from=pnicore /opt/pni /usr/

RUN cmake -DCMAKE_INSTALL_PREFIX=/opt/pni ..

RUN make install

FROM dependencies

RUN apt-get update && apt-get install -y \
  openjdk-8-jdk-headless                              

ARG APP_UID=2000

ARG APP_GID=2000

COPY --from=pnicore /opt/pni /usr/

COPY --from=pniio /opt/pni /usr/
