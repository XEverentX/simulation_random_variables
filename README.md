[![Build Status](https://travis-ci.org/XEverentX/simulation_random_variables.svg?branch=master)](https://travis-ci.org/XEverentX/simulation_random_variables)  

# Simulation of random variables
Laboratory work for Theory of probability. Simulation of random variables by given distribution density.

### Setup
To work with this repo you need to install:
 - CMake
 - g++(Linux) or vsc(Windows)
 - QT
 - Boost library
 
To setup it on linux use:
```bash
 sudo apt install g++
 sudo apt install cmake
 sudo apt update
 sudo apt install qt5-default
 sudo apt-get install libboost-all-dev
```

### Build & Run
To build application simply follow a few steps:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config RELEASE
```

Use `simulation` as `<excecutable>`.

To run under `linux` use:

```bash
./samples/<executable>
```

To run under `windows` use:

```bash
.\samples\Release\<executable>.exe
```

### Configuration

You can specify the parameters of simulation by tow way:

- Input interface in the begin of the program
- Transfer by execution arguments using flowing keys:
  - `-l` lambda
  - `-c` count
