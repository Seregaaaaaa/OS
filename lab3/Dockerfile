FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    linux-headers-generic \
    kmod

COPY . /usr/src/tsulab

WORKDIR /usr/src/tsulab

RUN make

CMD ["bash"]