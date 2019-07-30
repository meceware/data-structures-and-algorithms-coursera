#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;

typedef pair<int, int> Coordinate;

double distance( const Coordinate& a, const Coordinate& b ) {
  return hypot( a.first - b.first, a.second - b.second);
}

double minimal_distance_recursive( const vector<Coordinate>& coordinates, unsigned int left, unsigned int right ) {
  unsigned int size = ( right - left );
  unsigned int halfSize = size >> 1; // left + size / 2

  if ( halfSize <= 3 ) {
    double result = std::numeric_limits<double>::max();
    for ( unsigned int i = left; i < right; i++ )  {
      const Coordinate& c = coordinates[i];
      for ( unsigned int j = i + 1; j < right; j++ )  {
        result = min( result, distance( c, coordinates[j] ) );
      }
    }

    return result;
  }

  double leftMin = minimal_distance_recursive( coordinates, left, left + halfSize );
  double rightMin = minimal_distance_recursive( coordinates, left + halfSize, right );
  double seperatedMin = min( leftMin, rightMin );

  int line = ( coordinates[ left + halfSize - 1 ].first + coordinates[ left + halfSize ].first ) >> 1;

  vector<Coordinate> hybrid;
  for ( unsigned int i = left; i < right; i++ )  {
    if ( abs( coordinates[i].first - line ) <= seperatedMin ) {
      hybrid.push_back( coordinates[i] );
    }
  }

  std::sort( hybrid.begin(), hybrid.end(), []( Coordinate& a, Coordinate& b ) {
    return a.second < b.second;
  } );

  size = hybrid.size();
  for ( unsigned int i = 0; i < size; i++ )  {
    const Coordinate& c = hybrid[i];
    const unsigned int maxSize = min( i + 8, size ); // should be 7?
    for ( unsigned int j = i + 1; j < maxSize; j++ )  {
      if ( abs( c.second - hybrid[j].second ) <= seperatedMin ) {
        seperatedMin = min( seperatedMin, distance( c, hybrid[j] ) );
      }
    }
  }

  return seperatedMin;
}

double minimal_distance(vector<Coordinate> &coordinates) {
  // Sort the points with x-coordinate
  std::sort( coordinates.begin(), coordinates.end(), []( Coordinate& a, Coordinate& b ) {
    return a.first < b.first;
  } );

  return minimal_distance_recursive( coordinates, 0, coordinates.size() );
}

int main() {
  size_t n;
  std::cin >> n;
  vector<Coordinate> coordinates(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> coordinates[i].first >> coordinates[i].second;
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(coordinates) << "\n";
}
