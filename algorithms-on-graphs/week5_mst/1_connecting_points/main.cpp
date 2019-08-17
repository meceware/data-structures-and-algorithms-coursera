#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>

using std::vector;
using std::map;

struct DoubleVal {
public:
  DoubleVal() : isInfinity(true), value(0.0) {}
  DoubleVal(double value) : isInfinity(false), value(value) {}

  DoubleVal& operator = (const double &d) {
    isInfinity = false;
    value = d;
    return *this;
  }

  DoubleVal& operator = (const DoubleVal &d) {
    isInfinity = d.isInfinity;
    value = d.value;
    return *this;
  }

  bool operator > (const DoubleVal &d) const {
    return (!isInfinity && !d.isInfinity ) ? value > d.value : isInfinity && !d.isInfinity;
  }

  bool isFinite() const {
    return !isInfinity;
  }

  double getValue() const {
    return value;
  }

private:
  bool isInfinity;
  double value;
};

struct Point {
  int x;
  int y;
};

struct Edge {
  unsigned int index;
  DoubleVal cost;
};

DoubleVal getDistance(const Point &p1, const Point &p2) {
  return { hypot(static_cast<double>(p1.x - p2.x), static_cast<double>(p1.y - p2.y)) };
}

// Prims's algorithm
double minimum_distance(const vector<Point> &points) {
  const unsigned int pointsSize = points.size();

  const auto comparison = [](const Edge &p1, const Edge &p2) {
    return p1.cost > p2.cost;
  };

  std::priority_queue<Edge, vector<Edge>, decltype(comparison)> pq(comparison);
  vector<bool> processed(pointsSize, false);

  pq.push({0, DoubleVal(0.0)});
  for (unsigned int i = 1; i < pointsSize; ++i) {
    pq.push({i, DoubleVal()});
  }

  double result = 0.0;
  while (!pq.empty()) {
    Edge p = pq.top();
    pq.pop();

    if (processed[p.index]) {
      continue;
    }
    processed[p.index] = true;

    result += p.cost.isFinite() ? p.cost.getValue() : 0.0;
    for (unsigned int i = 0; i < pointsSize; ++i) {
      if (processed[i]) {
        continue;
      }

      const auto dist = getDistance(points[p.index], points[i]);
      pq.push({i, dist});
    }
  }

  return result;
}

int main() {
  size_t n;
  std::cin >> n;

  vector<Point> points(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> points[i].x >> points[i].y;
  }

  std::cout << std::fixed << std::setprecision(10) << minimum_distance(points) << std::endl;
}


/*
13
1 58
28 80
42 84
89 54
44 28
36 64
54 39
20 14
66 41
36 84
24 84
16 64
9 80
199.6756033
*/