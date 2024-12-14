FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    linux-headers-generic \
    make

COPY . /usr/src/tsu
WORKDIR /usr/src/tsu

CMD ["make"]
/Users/sergei.samoilov/Documents/Учеба/Учеба_3.1/Операционные системы/OS/lab3