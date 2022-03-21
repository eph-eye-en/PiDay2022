# Pi Day 2022

A Pi Day project for the AT90USB162 which calculates hexadecimal digits of pi
and displays them in binary on LEDs. More info at
[fency.fun](https://fency.fun).

Note: I am far from a C expert so this is not model C code.

## Files

* `pi.c`: Contains the actual digit calculating code to be used by other files.

* `main.c`: Contains AVR code which uses `pi.c` to calculate digits.

* `test.c`: Code which can be executed directly in a terminal (not loaded
onto the microcontroller) to verify the digits produced by the `pi.c`.

* `USB` directory: Contains AVR +
[LUFA](http://www.fourwalledcubicle.com/LUFA.php) code which sends digits via
USB serial instead of displaying them with LEDs.

## Compiling

* `make main`: Compile the main code into `main.hex`, which can be loaded onto
the microcontroller.

* `make test`: Compile `test.c` to `test.out`.

* `make usb`: Compile the contents of `USB`, producing `usb.hex`, which can be
loaded onto the microcontroller.