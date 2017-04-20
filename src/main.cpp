#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "point3.h"
#include "line_segment.h"
#include "graph_utils.h"


bool parse_line(const std::string& line, double p1[3], double p2[3]) {
  size_t idx = 0;
  std::vector<double> vals;
  // Try reading all numbers from the line into memory.
  while (idx < line.size()) {
    size_t offset;
    try {
      vals.push_back(std::stod(line.substr(idx), &offset));
    }
    catch (const std::invalid_argument& ia) {
      return false;
    }
    idx += offset;
  }
  // Make sure we got the right number.
  if (vals.size() != 6) {
    return false;
  }
  // Success! Store them into outputs.
  for (size_t i = 0; i < 3; i++) {
    p1[i] = vals[i];
    p2[i] = vals[i + 3];
  }
  return true;
}


bool load_line_segments(const char* filename,
                        std::vector<LineSegment>& line_segments) {
  // Open file.
  std::ifstream file(filename);
  // Check if file opened successfully.
  if (!file.is_open()) {
    std::cerr << "Failed to open: " << filename << std::endl;
    return false;
  }

  // Read each line and parse.
  std::string line;
  size_t line_idx = 0;
  while (getline(file, line)) {
    double p1[3], p2[3];
    line_idx++;
    if (!parse_line(line, p1, p2)) {
      std::cerr << "Error parsing line number " << line_idx << std::endl;
      return false;
    }
    line_segments.push_back(LineSegment(Point3(p1), Point3(p2)));
  }

  // Success! Close stream and return.
  file.close();
  return true;
}


void print_usage(void) {
  std::cerr << "usage: run <line_segment_file>" << std::endl;
}


bool argument_sanity_check(int argc, char** argv) {
  if (argc != 2) {
    return false;
  }
  return true;
}


int main(int argc, char** argv) {
  if (!argument_sanity_check(argc, argv)) {
    print_usage();
    return 1;
  }

  std::vector<LineSegment> line_segments;
  // Load points.
  if (!load_line_segments(argv[1], line_segments)) {
    return 1;
  }
  // Compute connectivity graph.
  std::vector<std::vector<size_t> > connectivity_graph;
  compute_connectivity_graph(line_segments, connectivity_graph);
  // Count groups.
  std::cout << count_groups(connectivity_graph) << std::endl;
  return 0;
}
