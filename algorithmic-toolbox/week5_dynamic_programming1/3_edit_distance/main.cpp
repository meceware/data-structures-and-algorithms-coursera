#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::min;

int edit_distance(const string &str1, const string &str2) {
  if ( str1 == str2 ) {
    return 0;
  }

  const int str1Size = str1.size();
  const int str2Size = str2.size();
  int d[ str1Size + 1 ][ str2Size + 1 ] = { 0 };

  for ( int i = 0; i <= str1Size; i++ ) {
    d[ i ][ 0 ] = i;
  }

  for ( int i = 0; i <= str2Size; i++ ) {
    d[ 0 ][ i ] = i;
  }

  for ( int j = 1; j <= str2Size; j++ ) {
    for ( int i = 1; i <= str1Size; i++ ) {
      int insertion = d[ i ][ j - 1 ] + 1;
      int deletion = d[ i - 1 ][ j ] + 1;
      int minID = min( insertion, deletion );
      d[ i ][ j ] = ( str1[ i - 1 ] == str2[ j - 1 ] ) ? min( minID, d[ i - 1 ][ j - 1 ] ) : ( min( minID, d[ i - 1 ][ j - 1 ] + 1 ) );
    }
  }

  return d[ str1Size ][ str2Size ];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
