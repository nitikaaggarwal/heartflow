#include <algorithm>
#include "line_segment.h"

LineSegment::LineSegment(const Point3& p1,
                         const Point3& p2) : _p1(p1), _p2(p2) {
}


std::string LineSegment::to_str(void) const {
  return _p1.to_str() + std::string(" -- ") + _p2.to_str();
}


static inline double clamp(const double val,
                           const double minval,
                           const double maxval) {
  return std::max(minval, std::min(maxval, val));
}


static double parallel_dist(const Point3& p1,
                            const Point3& p2,
                            const Point3& d1,
                            const Point3& d2) {
  Point3 d1_cross_d2 = d1.cross(d2);
  return abs(d1_cross_d2.dot(p1 - p2) / d1_cross_d2.norm2());
}


double LineSegment::min_dist(const LineSegment& seg) const {
  const double PARALLEL_THRESHOLD = 0.000001;  // Randomly chosen.
  Point3 d1 = _p2 - _p1;
  Point3 d2 = seg._p2 - seg._p1;
  Point3 p1(_p1), p2(seg._p1);
  Point3 p = p1 - p2;

  // Pre-compute dot-products.
  double d1_dot_d2 = d1.dot(d2);
  double d1_2 = d1.sqnorm2();
  double d2_2 = d2.sqnorm2();
  double d1_dot_p = d1.dot(p);
  double d2_dot_p = d2.dot(p);

  // Compute common denominator for both lambdas.
  double denom = d1_dot_d2 * d1_dot_d2 - d1_2 * d2_2;

  // TODO(nitikaaggarwal): If `denom` approaches zero, the segments
  // are parallel. Use standard formulation to compute minimum distance.
  if (abs(denom) < PARALLEL_THRESHOLD) {
    return parallel_dist(p1, p2, d1, d2);
  }

  double lambda1 = (d2_2 * d1_dot_p - d1_dot_d2 * d2_dot_p) / denom;
  double lambda2 = (d1_dot_d2 * d1_dot_p - d1_2 * d2_dot_p) / denom;

  // Clamp the lambda values to lie between 0 and 1.
  lambda1 = clamp(lambda1, 0.0, 1.0);
  lambda2 = clamp(lambda2, 0.0, 1.0);

  // Get the endpoints of the shortest line-segment joining
  // the two segments.
  Point3 endpt1 = p1 + d1 * lambda1;
  Point3 endpt2 = p2 + d2 * lambda2;

  return (endpt1 - endpt2).norm2();
}
