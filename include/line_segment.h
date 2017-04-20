#ifndef __MY_LINE_SEGMENT_H__
#define __MY_LINE_SEGMENT_H__

#include <ostream>
#include "point3.h"

class LineSegment {
 public:
  // Constructors.
  LineSegment(const Point3& p1, const Point3& p2);

  // Utility.
  double min_dist(const LineSegment& seg) const;
  std::string to_str(void) const;

 private:
  Point3 _p1;
  Point3 _p2;
};

#endif
