#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::cin;

struct Query {
  string type;
  string name;
  int number;
};

template < typename K, typename V >
struct HashNode
{
private:
  // key-value pair
  K _key;
  V _value;
  // next bucket with the same key
  HashNode *_next;
  // disallow copy and assignment

public:
  HashNode(const K &key, const V &value) : _key(key), _value(value), _next(NULL) {}
  HashNode(const HashNode &) = delete;
  HashNode & operator = (const HashNode &) = delete;

  constexpr K key() const { return _key; }

  constexpr V value() const { return _value; }

  void value(V value) { _value = value; }

  HashNode* next() const { return _next; }

  void next(HashNode* next) { _next = next; }
};

template < typename K, typename V, size_t tableSize = 128 >
struct HashMap
{
  typedef HashNode<K, V>* HashNodePtr;

private:
  // Hash table
  vector< HashNodePtr > table;

  constexpr unsigned int hash(const K &key) const
  {
    return static_cast<unsigned int>(key) % tableSize;
  }

  HashNodePtr getEntry( const K &key ) const {
    return table[ hash( key ) ];
  }

  HashNodePtr getValue( const K &key, HashNodePtr entry ) const {
    while ( entry ) {
      if ( entry->key() == key ) {
        return entry;
      }

      entry = entry->next();
    }

    return NULL;
  }

  HashNodePtr getValue( const K &key ) const {
    return getValue( key, getEntry( key ) );
  }

public:
  HashMap() : table( tableSize ) {}
  HashMap( const HashMap & other ) = delete;
  const HashMap & operator = ( const HashMap & other ) = delete;

  ~HashMap() {
    for ( unsigned int i = 0; i < tableSize; ++i ) {
      HashNodePtr entry = table[i];
      while ( entry != NULL ) {
        HashNodePtr prev = entry;
        entry = entry->next();
        delete prev;
      }

      table[i] = NULL;
    }
  }

  bool get( const K& key, V& value ) const {
    HashNodePtr entry = getValue( key );

    if ( entry == NULL ) {
      return false;
    }

    value = entry->value();
    return true;
  }

  void put( const K& key, const V& value ) {
    unsigned int hashKey = hash( key );
    HashNodePtr entry = table[ hashKey ];
    HashNodePtr data = getValue( key, entry );

    // If data is not found, add the entry as beginning to the table
    if ( !data ) {
      HashNodePtr newNode = new HashNode<K, V>( key, value );
      newNode->next( entry );
      table[ hashKey ] = newNode;
    } else {
      data->value( value );
    }
  }

  void remove( const K& key ) {
    unsigned int hashKey = hash( key );
    HashNodePtr entry = table[ hashKey ];
    HashNodePtr prev = NULL;

    while ( entry && entry->key() != key ) {
      prev = entry;
      entry = entry->next();
    }

    // Not found
    if ( !entry ) {
      return;
    }

    // Found at the first
    if ( !prev ) {
      table[ hashKey ] = entry->next();
    } else {
      prev->next( entry->next() );
    }

    delete entry;
  }
};

void process_queries(const vector<Query>& queries, vector<string>& results) {
  const string notFound = "not found";
  HashMap< int, string > hashMap;
  for ( const auto& query: queries ) {
    if (query.type == "add") {
      hashMap.put( query.number, query.name );
    } else if (query.type == "del") {
      hashMap.remove( query.number );
    } else if (query.type == "find") {
      string result;
      results.push_back( hashMap.get( query.number, result ) ? result : notFound );
    } else {
      results.push_back( notFound );
    }
  }
}

int main() {
  // Read queries
  int n;
  cin >> n;
  vector<Query> queries(n);
  for (int i = 0; i < n; ++i) {
    Query& query = queries[i];
    cin >> query.type;
    cin >> query.number;
    if (query.type == "add")
      cin >> query.name;
  }

  vector<string> results;
  process_queries( queries, results );

  // Write responses
  for (const auto result : results) {
      std::cout << result << std::endl;
  }

  return 0;
}