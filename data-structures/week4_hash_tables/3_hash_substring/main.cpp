#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
  string pattern;
  string text;
};

unsigned long long getHash( const string& s, const unsigned long long prime, const unsigned long long mult ) {
  unsigned long long hash = 0;
  unsigned int sSize = s.size();

  for (unsigned int i = sSize; i > 0; --i) {
    hash = (hash * mult + s[i - 1]) % prime;
  }

  return hash;
}

unsigned long long getHash( const string& s, unsigned int start, unsigned int end, const unsigned long long prime, const unsigned long long mult ) {
  unsigned long long hash = 0;

  for (unsigned int i = end; i > start; --i) {
    hash = (hash * mult + s[i - 1]) % prime;
  }

  return hash;
}

void get_occurrences(const Data& input, std::vector<int>& ans) {
  const unsigned long long prime = 1000000007;
  const unsigned long long mult = 31; // x should be random but chosen as 31 as in java

  const string& pattern = input.pattern;
  const string& text = input.text;

  const unsigned int patternSize = pattern.size();
  const unsigned int textSize = text.size();

  const unsigned long long patternHash = getHash( pattern, prime, mult );

  // Precompute hash
  std::vector< unsigned long long > computedHash( textSize - patternSize + 1 );
  computedHash[ textSize - patternSize ] = getHash( text, textSize - patternSize, textSize, prime, mult );

  unsigned long long y = 1;
  for ( unsigned int i = 0; i < patternSize; ++i ) {
    y = ( y * mult ) % prime;
  }

  for ( int i = textSize - patternSize - 1; i >= 0; --i ) {
    long long hash = ( long long )( ( mult * computedHash[ i + 1 ] ) + text[ i ] ) - ( long long )( y * text[ i + patternSize ] );
    while ( hash < 0 ) {
      hash += prime;
    }
    computedHash[ i ] = hash % prime;
  }

  // Check occurance
  for ( unsigned int i = 0; i < textSize - patternSize + 1; ++i ) {
    if ( computedHash[ i ] == patternHash ) {
      // Hash found,check the substring
      // Even though substring is not supposed to be used, there should be less conflicts so it can be used here i think
      if ( text.substr( i, patternSize ) == pattern ) {
        ans.push_back( i );
      }
    }
  }
}


int main() {
  std::ios_base::sync_with_stdio( false );
  Data data;
  std::cin >> data.pattern >> data.text;

  std::vector<int> ans;
  get_occurrences( data, ans );

  for ( const auto i : ans ) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
