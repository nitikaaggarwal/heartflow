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

## Control Flow and Design Philosophy

The present version has been written with clarity and correctness in mind.
The program currently involves `O(n^2)` distance computations for `n` input
segments, i.e., a segment is compared for overlap with every other segment
in memory. This process may be accelerated with implementation of a K-D Tree.
This way, a segment will only be compared with candidates that are close
enough, reducing asymptotic complexity closer to linear time.

The program first reads all line segments into memory. There is no
pre-processing for numerical stability. One option could be to translate
the data points such that the mean lies at the origin.

A line segment is stored in the `LineSegment` data structure, which
stores the end points internally as a `Point3` data structure.

I compare each segment with all other segments to create a graph, such
that each segment has a vertex in the graph, and two vertices (segments)
share an edge if their minimum distance is below a threshold. Such a
criterion is especially useful if the line segments have thickness, as
shown in the original problem illustration. Moreover, two line segments
will seldom, if ever, perfectly intersect. Hence, a small threshold
is the correct way to compute intersection.

The graph is stored as a vector of vectors, such that each index is
mapped to a list of neighbors. For each node, the program performs DFS,
marking each reachable node as visited. The DFS is only initiated
for nodes that have been unvisited by previous DFS calls; I keep
track of this information across DFS calls. Thus, the program is able
to successfully count the number of line segment groups. Note that
while DFS is easy to code, it may not be the most efficient
approach due to creation of recursion stack that could run deep.
Computing reachability via BFS will be better.


# Computing Shortest Distance Between Line Segments

I parameterize the line passing through points `p1` and `p2` with
a scalar `lambda`. The following formulation ensures that a point
lies on the line segment between these points if and only if
`lambda` lies between `0` and `1`:

```
p1 + lambda * (p2 - p1)
```

For two line segments, we compute `lambda1` and `lambda2` respectively
such that the length of the line segment joining the parametric
points is minimized, if the line segments are not roughly parallel.
For the parallel case, we use the standard cross product fomulation
that computes the minimum distance between lines. It is possible
that the points obtained will lie outside the line segments. However,
since the distance function is quadratic in the parametric variables,
we have a convex surface for it, and the distance will increase
monotonically as we move away from optimal lambda values. Thus, we
can safely clamp the optimal parameters to the edges of the `[0, 1]`
interval, and use the points so obtained to compute the minimum distance
between the line segments.
