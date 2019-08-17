#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <queue>
#include <cmath>

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
  int from;
  int to;
  DoubleVal distance;
};

struct DisjointSetsElement {
	// size is how many elements in total are pointing to this element
	// parent is self or other elements
	// rank heigt of this element
	int size;
  int parent;
  int rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) : size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	std::vector<DisjointSetsElement> sets;

	DisjointSets(int size): size(size) {
		for (int i = 0; i < size; i++) {
      sets.push_back({1, i, 0});
		}
	}

	int count() const {
		return size;
	}

	int parent(int table) {
		if (sets[table].parent != table) {
			sets[table].parent = parent(sets[table].parent);
    }
		return sets[table].parent;
	}

  bool same(int i, int j) {
		return parent(i) == parent(j);
	}

	void merge(const int destination, const int source) {
    // Nothing to merge
    if (size == 0) {
      return;
    }

		int d = parent(destination);
		int s = parent(source);

		if (d == s) {
			return;
    }

		size--;
		if (sets[d].rank > sets[s].rank) {
			sets[s].parent = d;
			sets[d].size += sets[s].size;
		} else {
			sets[d].parent = s;
			sets[s].size += sets[d].size;
			if (sets[s].rank == sets[d].rank) {
				sets[s].rank++;
			}
		}
	}
};

DoubleVal getDistance(const Point &p1, const Point &p2) {
  return { hypot(static_cast<double>(p1.x - p2.x), static_cast<double>(p1.y - p2.y)) };
}

double clustering(std::vector<Point> &points, int k) {
  const int pointsSize = points.size();

  const auto comparison = [](const Edge &p1, const Edge &p2) {
    return p1.distance > p2.distance;
  };
  std::priority_queue<Edge, std::vector<Edge>, decltype(comparison)> pq(comparison);

  for (int i = 0; i < pointsSize; ++i) {
    for (int j = 0; j < pointsSize; ++j) {
      pq.push({i, j, getDistance(points[i], points[j])});
    }
  }

  DisjointSets sets(pointsSize);

  while (sets.count() > k) {
    const Edge &e = pq.top();
    sets.merge(e.from, e.to);
    pq.pop();
  }

  DoubleVal minDistance;
  while (!pq.empty()) {
    const Edge &e = pq.top();
    if (!sets.same(e.from, e.to)) {
      const auto distance = getDistance(points[e.from], points[e.to]);
      if (minDistance > distance) {
        minDistance = distance;
      }
    }
    pq.pop();
  }

  return minDistance.getValue();
}

int main() {
  size_t n;
  int k;
  std::cin >> n;
  std::vector<Point> points(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> points[i].x >> points[i].y;
  }
  std::cin >> k;
  std::cout << std::fixed << std::setprecision(10) << clustering(points, k) << std::endl;
}
