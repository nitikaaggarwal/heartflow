#include <cmath>
#include <sstream>
#include "point3.h"

Point3::Point3(const double x, const double y, const double z) {
  _coord[0] = x;
  _coord[1] = y;
  _coord[2] = z;
}


Point3::Point3(const double coord[3]) {
  for (size_t k = 0; k < K; k++) {
    _coord[k] = coord[k];
  }
}


Point3::Point3(const Point3& p) {
  for (size_t k = 0; k < K; k++) {
    _coord[k] = p._coord[k];
  }
}


static inline double squared_norm2(const double* p, const size_t K) {
  // TODO(nitikaaggarwal): Can we make this computation stable?
  double s(0.0);
  for (size_t k = 0; k < K; k++) {
    s += p[k] * p[k];
  }
  return s;
}


double Point3::sqnorm2(void) const {
  return squared_norm2(_coord, K);
}


double Point3::norm2(void) const {
  return sqrt(sqnorm2());
}


double Point3::euclidean_dist(const Point3& p) const {
  double diff[K];
  for (size_t k = 0; k < K; k++) {
    diff[k] = _coord[k] - p._coord[k];
  }
  return sqrt(squared_norm2(diff, K));
}


std::string Point3::to_str(void) const {
  std::stringstream ss;
  ss << "(";
  for (size_t k = 0; k < K; k++) {
    ss << _coord[k];
    if ((k + 1) < K) {
      ss << ", ";
    }
  }
  ss << ")";
  return ss.str();
}


Point3 Point3::operator-(const Point3& p) const {
  double diff[K];
  for (size_t k = 0; k < K; k++) {
    diff[k] = _coord[k] - p._coord[k];
  }
  return Point3(diff);
}


Point3 Point3::operator+(const Point3& p) const {
  double sum[K];
  for (size_t k = 0; k < K; k++) {
    sum[k] = _coord[k] + p._coord[k];
  }
  return Point3(sum);
}

Point3 Point3::operator*(const double alpha) const {
  double scaled[K];
  for (size_t k = 0; k < K; k++) {
    scaled[k] = _coord[k] * alpha;
  }
  return Point3(scaled);
}


double Point3::dot(const Point3& p) const {
  double dot = 0.0;
  for (size_t k = 0; k < K; k++) {
    dot += _coord[k] * p._coord[k];
  }
  return dot;
}


Point3 Point3::cross(const Point3& p) const {
  // NOTE: This is a poor implementation from a clean coding
  // perspective. An attempt has been made in this file to
  // avoid magic numbers. Ideally, one would want to implement
  // a generalized cross product in K dimensions, but this
  // will compromise speed.
  double cross[K];
  cross[0] = _coord[1] * p._coord[2] - _coord[2] * p._coord[1];
  cross[1] = _coord[2] * p._coord[0] - _coord[0] * p._coord[2];
  cross[2] = _coord[0] * p._coord[1] - _coord[1] * p._coord[0];
  return Point3(cross);
}
