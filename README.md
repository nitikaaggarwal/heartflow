## Build

This code was developed and tested with g++ 5.4.0. Since it does not
rely on non-standard CPP libraries, I have supplied a Makefile
instead of building from a CMake project.

To build the code, run the following command:

```bash
make all
```

## Launch

The executable binary `run` is created inside the `build` folder.
The program requires the input file (say `segments.txt`) containing
line segments as its one and only command-line argument. Example
run:

```bash
build/run segments.txt
```

## Input file format

The segment file input above should contain exactly one segment
per line. A segment is represented as a sequence of six, space-separated
floating point numbers, each representing one of the 3D coordinates of
the segment end points. For example, if a segment has end points
`(x1, y1, z1)` and `(x2, y2, z2)`, then it will be written in the file as:

```
x1 y1 z1 x2 y2 z2
```
