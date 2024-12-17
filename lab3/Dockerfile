FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    linux-headers-generic \
    make

COPY . /usr/src/tsulab
WORKDIR /usr/src/tsulab

CMD ["make"]