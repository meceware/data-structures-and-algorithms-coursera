#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::pair;

typedef pair<int, int> SegmentPair;

void fast_count_segments_2(vector<SegmentPair> &segments, vector<int> &points, vector<int> &cnt) {
  std::sort( segments.begin(), segments.end(), [](const SegmentPair& a, const SegmentPair& b) {
    return a.first < b.first;
  });

  for ( size_t i = 0; i < points.size(); ++i ) {
    const auto point = points[ i ];

    for ( const auto& segment : segments ) {
      if ( point < segment.first ) {
        break;
      }

      cnt[ i ]++;
    }
  }

  std::sort( segments.begin(), segments.end(), [](const SegmentPair& a, const SegmentPair& b) {
    return a.second < b.second;
  });

  for ( size_t i = 0; i < points.size(); i++ ) {
    const auto point = points[ i ];

    for ( const auto& segment : segments ) {
      if ( point <= segment.second ) {
        break;
      }

      cnt[ i ]--;
    }

    if ( cnt[ i ] < 0 ) {
      std::cout << "cnt is less " << std::endl;
    }
  }
}

void fast_count_segments(vector<SegmentPair> &segments, vector<int> &points, vector<int> &cnt) {
  std::sort( segments.begin(), segments.end(), [](const SegmentPair& a, const SegmentPair& b) {
    return a.first < b.first;
  });

  size_t segmentsSize = segments.size();
  SegmentPair minMax{1e8, -1e8};
  for ( const auto& segment : segments ) {
    if ( segment.first < minMax.first ) {
      minMax.first = segment.first;
    }
    if ( segment.second > minMax.second ) {
      minMax.second = segment.second;
    }
  }

  for ( size_t i = 0; i < points.size(); i++ ) {
    const auto point = points[ i ];

    if ( i > 0 ) {
      if ( point == points[ i - 1 ] ) {
        cnt[ i ] = cnt[ i - 1 ];
        continue;
      }
    }

    if ( point < minMax.first || point > minMax.second ) {
      continue;
    }

    for ( const auto& segment : segments ) {
      if ( point < segment.first ) {
        break;
      }

      if ( point <= segment.second ) {
        cnt[ i ]++;
      }
    }
  }
}

void naive_count_segments(const vector<SegmentPair> &segments, const vector<int> &points, vector<int> &cnt) {
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < segments.size(); j++) {
      cnt[i] += segments[j].first <= points[i] && points[i] <= segments[j].second;
    }
  }
}

int main() {
#if 0
  srand(time(0));
  for ( int s = 1; s <= 500; s++ ) {
    for ( int p = 1; p <= 500; p++ ) {
      std::cout << "s: " << s << " p: " << p << " ";

      const int minVal = -1e8;
      const int maxVal = 1e8;

      vector<SegmentPair> segments( s );
      const int randCoefficient = (maxVal - minVal) / RAND_MAX;
      for ( int i = 0; i < s; i++ ) {
        segments[i].first = rand() * randCoefficient - maxVal;
        segments[i].second = rand() * randCoefficient - maxVal;
      }

      vector<int> points(p);
      for ( int i = 0; i < p; i++ ) {
        points[i] = rand() * randCoefficient - maxVal;
      }

      vector<int> cntNaive(p);
      naive_count_segments( segments, points, cntNaive );
      vector<int> cntFast(p);
      fast_count_segments_2( segments, points, cntFast );

      if ( cntNaive == cntFast ) {
        std::cout << "OK!" << std::endl;
      } else {
        std::cout << "Fail!" << std::endl;
        std::cin.get();
        cntNaive.clear();
        cntFast.clear();
        naive_count_segments( segments, points, cntNaive );
        fast_count_segments_2( segments, points, cntFast );
      }
    }
  }
#endif

  int n, m;
  std::cin >> n >> m;
  vector<SegmentPair> segments(n);
  for (size_t i = 0; i < segments.size(); i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }

  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }

#if 0
  { // TODO
    vector<int> cnt(points.size());
    naive_count_segments( segments, points, cnt );
    for ( const auto i : cnt ) {
      std::cout << i << ' ';
    }
    std::cout << std::endl;
  }
#endif

  //use fast_count_segments
  vector<int> cnt(points.size());
  fast_count_segments_2( segments, points, cnt );
  for ( const auto i : cnt ) {
    std::cout << i << ' ';
  }
}
