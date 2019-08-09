#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

// #define _DEBUG
// #define _EXTRA_COMPARE

using std::string;

struct Answer {
	unsigned int i, j, len;
};

class LCS {
public:
  LCS() : size( 1 ) {
    power1.resize( 1 );
    power2.resize( 1 );

    power1[ 0 ] = 1;
    power2[ 0 ] = 1;

    resizePowers( 16 );
  }

  Answer solve( const string& s, const string& t ) {
    int sSize = s.size();
    int tSize = t.size();

    resizePowers( std::max( sSize, tSize ) + 1 );

    int left = 0;
    int right = std::min( sSize, tSize );

    Answer ans = { 0, 0, 0 };
    while ( left <= right && ( left || right ) ) {
      int mid = left + ( right - left ) / 2;

      Answer solved = solveHash( s, t, mid ? mid : mid + 1 );

      if ( solved.len != 0 ) {
        ans = solved;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }

    return ans;
  }

private:
  unsigned int size;

  const long long prime1 = 1000000007;
  const long long prime2 = 1000000009;
  const long long mult1 = 31; // The mult should be selected randomly but I don't think it matters here
  const long long mult2 = 127; // The mult should be selected randomly but I don't think it matters here

  std::vector< long long > power1;
  std::vector< long long > power2;

  void resizePower( std::vector< long long >& power, long long prime, long long mult ) {
    unsigned int powerSize = power.size();
    power.resize( size );
    for ( unsigned int i = powerSize; i < size; ++i ) {
      power[ i ] = ( power[ i - 1 ] * mult ) % prime;
    }
  }

  void resizePowers( const unsigned int length ) {
    if ( size >= length ) {
      return;
    }

    size = length;
    resizePower( power1, prime1, mult1 );
    resizePower( power2, prime2, mult2 );
  }

  Answer solveHash( const string& s, const string& t, const unsigned int mid ) const {
    const unsigned int sSize = s.size();
    const unsigned int tSize = t.size();

    std::map< long long, unsigned int > hashMap1;
    std::map< long long, unsigned int > hashMap2;

    const auto fixMod = []( long long hash, long long prime ) -> long long {
      return ( ( hash % prime ) + prime ) % prime;
    };

    #ifdef _DEBUG
    std::cout << "mid is " << mid << std::endl;
    #endif

    long long hash1 = 0;
    long long hash2 = 0;
    for ( unsigned int i = sSize; i > sSize - mid; --i ) {
      hash1 = fixMod( ( hash1 * mult1 ) + s[ i - 1 ], prime1 );
      hash2 = fixMod( ( hash2 * mult2 ) + s[ i - 1 ], prime2 );
    }
    hashMap1[ hash1 ] = sSize - mid;
    hashMap2[ hash2 ] = sSize - mid;

    #ifdef _DEBUG
    std::cout << "s str " << s.substr(sSize - mid, mid) << " hash1 " << hash1 << " hash2 " << hash2 << std::endl;
    #endif

    for ( unsigned int i = sSize - mid; i > 0; --i ) {
      hash1 = fixMod( ( mult1 * hash1 ) + s[ i - 1 ] - ( power1[ mid ] * s[ i + mid - 1 ] ), prime1 );
      hash2 = fixMod( ( mult2 * hash2 ) + s[ i - 1 ] - ( power2[ mid ] * s[ i + mid - 1 ] ), prime2 );
      hashMap1[ hash1 ] = i - 1;
      hashMap2[ hash2 ] = i - 1;

      #ifdef _DEBUG
      std::cout << i << "s str " << s.substr(i - 1, mid) << " hash1 " << hash1 << " hash2 " << hash2 << std::endl;
      #endif
    }

    hash1 = 0;
    hash2 = 0;
    for ( unsigned int i = tSize; i > tSize - mid; --i ) {
      hash1 = fixMod( ( hash1 * mult1 ) + t[ i - 1 ], prime1 );
      hash2 = fixMod( ( hash2 * mult2 ) + t[ i - 1 ], prime2 );
    }

    #ifdef _DEBUG
    std::cout << "t str " << t.substr(tSize - mid, mid) << " hash1 " << hash1 << " hash2 " << hash2 << std::endl;
    #endif

    if ( hashMap1.find( hash1 ) != hashMap1.end() && hashMap2.find( hash2 ) != hashMap2.end() ) {
      #ifdef _EXTRA_COMPARE
      if ( !s.compare( hashMap1[ hash1 ], mid, t, tSize - mid, mid ) )
      #endif

      return { hashMap1[ hash1 ], tSize - mid, mid };
    }

    for ( unsigned int i = tSize - mid; i > 0; --i ) {
      hash1 = fixMod( ( mult1 * hash1 ) + t[ i - 1 ] - ( power1[ mid ] * t[ i + mid - 1 ] ), prime1 );
      hash2 = fixMod( ( mult2 * hash2 ) + t[ i - 1 ] - ( power2[ mid ] * t[ i + mid - 1 ] ), prime2 );

      #ifdef _DEBUG
      std::cout << i << "t str " << t.substr(i - 1, mid) << " hash1 " << hash1 << " hash2 " << hash2 << std::endl;
      #endif

      if ( hashMap1.find( hash1 ) != hashMap1.end() && hashMap2.find( hash2 ) != hashMap2.end() ) {

        #ifdef _EXTRA_COMPARE
        if ( !s.compare( hashMap1[ hash1 ], mid, t, i - 1, mid ) )
        #endif

        return { hashMap1[ hash1 ], i - 1, mid };
      }
    }

    return { 0, 0, 0 };
  }
};

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(0);
	string s, t;

  LCS lcs;

	while (std::cin >> s >> t) {
    auto ans = lcs.solve( s, t );
		std::cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
