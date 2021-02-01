FROM registry.gitlab.com/m-whitaker-registry/general/protobuf

RUN DEBIAN_FRONTEND="noninteractive" apt-get -y install tzdata
RUN apt-get -y install git cmake

### Setup Google Test ###

RUN git clone https://github.com/google/googletest.git /tmp/googletest

WORKDIR /tmp/googletest/build

RUN cmake ..
RUN make
RUN make install

RUN rm -rf /tmp/*

### Setup Proc-Server ###
WORKDIR /
