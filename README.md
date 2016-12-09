# C Library for LIFX lightbulbs

A C implementation of the [LIFX LAN protocol](https://lan.developer.lifx.com) to interact with lightbulbs in the local network.

This library is not, in any way, affiliated or related to LiFi Labs, Inc. Use it at your own risk.

### Requirements
- LIFX lightbulbs with firmware 2.0 or higher
- A POSIX compatible machine for code compilation & execution (currently tested on macOS)

### Supported functionality
- Discovery of bulbs (currently limited to up to 10)
- Retrieval & change of power (i.e. turning light on and off) 
- Retrieval & change of color

### Documentation
- `app.c` simple example demonstrating the implemented functionality
- `lifx.h` & `lifx.c` implementation of the library
- `bulb.h` definition of the `bulb_service_t` struct, which represents a single lightbulb in software
- `color.h` defintion of the `color_t` struct, a collection of hue, saturation, brightness & color temperature representing together a certain 'color'

## Usage
Use `make` to build `app.c` and the library, resulting in an executable called `app`.

`make debug` enables more console output, which will currently print all sent & received packets.

`make clean` removes the executable and all intermediate files.
