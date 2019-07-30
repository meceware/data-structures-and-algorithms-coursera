#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

void optimal_points(vector<Segment> &segments, vector<int> &points) {
  std::sort( segments.begin(), segments.end(), []( const Segment &a, const Segment &b ) {
    return ( a.end < b.end );
  } );

  for ( const auto& segment : segments ) {
    if ( points.size() == 0 ) {
      points.push_back( segment.end );
      continue;
    }

    if ( points[ points.size() - 1 ] < segment.start ) {
      points.push_back( segment.end );
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points;
  optimal_points(segments, points);
  std::cout << points.size() << "\n";
  for (const auto point : points) {
    std::cout << point << " ";
  }
}
