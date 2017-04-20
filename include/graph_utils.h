#ifndef __MY_GRAPH_UTILS_H__
#define __MY_GRAPH_UTILS_H__

#include <vector>
#include "line_segment.h"


// The maximum distance between line segments
// to consider them as neighbors.
#define MAX_DIST 0.001


void compute_connectivity_graph(
    const std::vector<LineSegment>& line_segments,
    std::vector<std::vector<size_t> >& connectivity_graph);


size_t count_groups(
    const std::vector<std::vector<size_t> >& connectivity_graph);

#endif
