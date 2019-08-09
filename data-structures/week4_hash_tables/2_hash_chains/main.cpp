#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::string;
using std::vector;
using std::list;

struct Query {
  string type;
  string s;
  size_t ind;
};

class QueryProcessor {
  typedef list<string> ChainList;

  int bucket_count;

  // store all strings in one vector
  vector< ChainList > chains;

  size_t hash_func( const string& s ) const {
    const size_t multiplier = 263;
    const size_t prime = 1000000007;
    unsigned long long hash = 0;

    for (int i = static_cast<int>( s.size() ) - 1; i >= 0; --i) {
      hash = (hash * multiplier + s[i]) % prime;
    }

    return hash % bucket_count;
  }

public:
  explicit QueryProcessor( int bucket_count ): bucket_count( bucket_count ), chains( bucket_count ) {}

  Query readQuery() const {
    string type;
    std::cin >> type;
    if (type != "check") {
      string s;
      std::cin >> s;
      return { type, s, 0 };
    }

    size_t ind;
    std::cin >> ind;
    return { type, "", ind };
  }

  void writeSearchResult( bool was_found ) const {
    std::cout << ( was_found ? "yes" : "no" ) << std::endl;
  }

  void processQuery( const Query& query ) {
    if (query.type == "check") {
      ChainList& chainList = chains[ query.ind ];
      for ( const auto& chain : chainList ) {
        std:: cout << chain << " ";
      }
      std::cout << std::endl;
    } else {
      ChainList& chainList = chains[ hash_func( query.s ) ];
      ChainList::iterator it = std::find( chainList.begin(), chainList.end(), query.s );
      if (query.type == "find") {
        writeSearchResult( it != chainList.end() );
      } else if (query.type == "add") {
        if ( it == chainList.end() ) {
          chainList.push_front( query.s );
        }
      } else if (query.type == "del") {
        if ( it != chainList.end() ) {
          chainList.erase( it );
        }
      }
    }
  }

  void processQueries() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
      processQuery( readQuery() );
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  int bucket_count;
  std::cin >> bucket_count;
  QueryProcessor proc( bucket_count );
  proc.processQueries();
  return 0;
}
