# Test POCO TCPServer, that reverses every input string

## Prerequirements
To install poco library (on Ubuntu, sudo apt install libpoco-dev)

## How to build
cd BellIntegratorTas
mkdir -p build && cd build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4

## How to run server
./pocoTcpServer

## How to run client (on Linux)
run terminal
telnet localhost 28888
enter text

