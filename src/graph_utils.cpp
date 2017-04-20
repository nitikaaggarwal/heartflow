#include <vector>
#include "graph_utils.h"


void compute_connectivity_graph(
    const std::vector<LineSegment>& line_segments,
    std::vector<std::vector<size_t> >& connectivity_graph) {
  // Allocate capacity for graph.
  connectivity_graph.resize(line_segments.size());
  // Do this pairwise, for now.
  for (size_t i = 0; i < line_segments.size(); i++) {
    for (size_t j = 0; j < line_segments.size(); j++) {
      // No self-loops allowed.
      if (j == i) {
        continue;
      }
      if (line_segments[i].min_dist(line_segments[j]) < MAX_DIST) {
        connectivity_graph[i].push_back(j);
      }
    }
  }
}


void dfs(
    const std::vector<std::vector<size_t> >& connectivity_graph,
    const size_t i,
    std::vector<bool>& visited) {
  if (visited[i]) {
    return;
  }
  visited[i] = true;
  for (size_t j = 0; j < connectivity_graph[i].size(); j++) {
    dfs(connectivity_graph, connectivity_graph[i][j], visited);
  }
}


void mark_neighbors_visited(
    const std::vector<std::vector<size_t> >& connectivity_graph,
    const size_t i,
    std::vector<bool>& visited) {
  // For now, we use DFS. This might lead to a very deep recursion
  // stack, which will be heavy on memory. It may be beneficial
  // to use BFS instead.
  dfs(connectivity_graph, i, visited);
}


size_t count_groups(
    const std::vector<std::vector<size_t> >& connectivity_graph) {
  size_t group_count = 0;
  // Keeps track of visited node indices.
  std::vector<bool> visited(connectivity_graph.size(), false);
  // For each unvisited node, mark all connected nodes as visited.
  for (size_t i = 0; i < connectivity_graph.size(); i++) {
    if (visited[i]) {
      continue;
    }
    mark_neighbors_visited(connectivity_graph, i, visited);
    group_count++;
  }
  return group_count;
}
