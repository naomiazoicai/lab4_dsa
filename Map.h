#pragma once
#include <utility>
#include <cstdlib>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)
//#define NULL_TKEY -111111
class MapIterator;

class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;

	private:
    static const int MAX_REHASHES = 10;
    //a bucket in the hash table
    struct Bucket {
        TElem element = NULL_TELEM;
    };

    Bucket* table1;
    Bucket* table2;
    int capacity;
    int tableSize;

    int hashFunction1( TKey& key) const {
        return abs(key) % capacity;
    }

    int hashFunction2( TKey& key) const {
        return (abs(key) * 13 ) % capacity;
    }

    void resize();

	public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

};



