[![Build Status](https://travis-ci.org/XEverentX/simulation_random_variables.svg?branch=master)](https://travis-ci.org/XEverentX/simulation_random_variables)  

# Simulation of random variables
Laboratory work for Theory of probability. Simulation of random variables by given distribution density.

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
