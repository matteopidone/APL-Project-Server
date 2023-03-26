FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y git gcc g++ build-essential cmake openssl libssl-dev zlib1g-dev libcurl4-openssl-dev libjsoncpp-dev libmariadb-dev uuid-dev

RUN git clone https://github.com/an-tao/drogon.git && \
    cd drogon && \
    git submodule update --init && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

COPY . /app
WORKDIR /app/build

RUN cmake ..
RUN make

CMD ["./APL-Project-Server"]
