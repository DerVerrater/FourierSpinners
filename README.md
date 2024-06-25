# Fourier Spinners

project was started as a way to better familiarize myself with C++, and to create something visually interesting. This particular goal was ripped straight from Daniel Shiffman's CodingTrain video series on the Fourier Transform. 

# Compilation

The Makefile orchestrates the building. Just run `make` to build the program:

```sh
# build
make [-j<nproc>]

# and install
make install
```

There's also a target to clean the build files

```sh
make clean
```

## Dependencies

- SDL2	- just the base, none of the extras for images or sound
- And a working compiler, of course

On Debian, and it's derivatives:

```sh
apt install build-essential libsdl2-dev
```
