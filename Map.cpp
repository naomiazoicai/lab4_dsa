#include "Map.h"
#include "MapIterator.h"
#include "iostream"

///constructor
///complexity:Θ(n), worst case: Θ(n) , average case: Θ(n), best case: Θ(n)
Map::Map() {
    capacity = 3;
    tableSize = 0;
    table1 = new Bucket[capacity];
    table2 = new Bucket[capacity];
}

///destructor
///complexity: Θ(1) worst, average and best
Map::~Map() {
    delete[] table1;
    delete[] table2;
}

/// adds a pair (key,value) to the map
///if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
///if the key does not exist, a new pair is added and the value null is returned
///complexity: total: O(n), worst case Θ(n), average case Θ(1) amortized, best case: Θ(1)
TValue Map::add(TKey c, TValue v)
{
    //check if the key already exists in the map, update the value and return old value
    if (search(c) != NULL_TVALUE)
    {
        int h1 = hashFunction1(c);
        int h2 = hashFunction2(c);
        TValue old_v;
        if (table1[h1].element.first == c)
        {
            //if the key is found in table1, update its value
            old_v = table1[h1].element.second;
            table1[h1].element.second = v;
        }
        else
        {
            //if the key is found in table2, update its value
            old_v = table2[h2].element.second;
            table2[h2].element.second = v;
        }
        return old_v;
    }

    int rehashesCount = 0;
    int possibleAddress = hashFunction1(c);
    TKey currentKey = c;
    TValue currentValue = v;
    while (rehashesCount < MAX_REHASHES)
    {
        if (rehashesCount % 2 == 0)     //adding in table1
        {
            //if the slot in table1 is empty, add the new element and increment table size
            if (table1[possibleAddress].element == NULL_TELEM)
            {
                table1[possibleAddress].element.first = currentKey;
                table1[possibleAddress].element.second = currentValue;
                tableSize++;
                return NULL_TVALUE;
            }

            TElem oldElem = table1[possibleAddress].element;
            table1[possibleAddress].element.first = currentKey;
            table1[possibleAddress].element.second = currentValue;

            possibleAddress = hashFunction2(oldElem.first);     // for displacement, verifying if slot is available in table2
            currentKey = oldElem.first;
            currentValue = oldElem.second;
        }
        else
            //adding in table2
        {
            //if the slot in table2 is empty, add the new element and increment table size
            if (table2[possibleAddress].element == NULL_TELEM)
            {
                table2[possibleAddress].element.first = currentKey;
                table2[possibleAddress].element.second = currentValue;
                tableSize++;
                return NULL_TVALUE;
            }

            TElem oldElem = table2[possibleAddress].element;
            table2[possibleAddress].element.first = currentKey;
            table2[possibleAddress].element.second = currentValue;

            possibleAddress = hashFunction1(oldElem.first);         // for displacement, verifying if slot is available in table2
            currentKey = oldElem.first;
            currentValue = oldElem.second;
        }

        rehashesCount++;
    }

    if (rehashesCount == MAX_REHASHES)
    {
        resize();
        add(currentKey, currentValue);
    }

}

///resize hashtable method
///complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n)
void Map::resize()
{
    int oldCapacity = capacity;
    capacity *= 2;

    Bucket* oldTable1 = table1;
    Bucket* oldTable2 = table2;

    table1 = new Bucket[capacity];
    table2 = new Bucket[capacity];

    for (int i = 0; i < capacity; i++)
    {
        table1[i].element = NULL_TELEM;
        table2[i].element = NULL_TELEM;
    }

    this->tableSize = 0;

    for (int i = 0; i < oldCapacity; i++)
    {
        if (oldTable1[i].element != NULL_TELEM)
        {
            TKey key = oldTable1[i].element.first;
            TValue value = oldTable1[i].element.second;
            add(key, value);
        }
        if (oldTable2[i].element != NULL_TELEM)
        {
            TKey key = oldTable2[i].element.first;
            TValue value = oldTable2[i].element.second;
            add(key, value);
        }
    }
    delete[] oldTable1;
    delete[] oldTable2;
}

///searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
///complexity: Θ(1) worst, average and best
TValue Map::search(TKey c) const
{
    int hash1 = hashFunction1(c);
    if (table1[hash1].element.first == c)
    {
        return table1[hash1].element.second;
    }

    int hash2 = hashFunction2(c);
    if (table2[hash2].element.first == c)
    {
        return table2[hash2].element.second;
    }

    return NULL_TVALUE;
}

///removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
///complexity: Θ(1) worst, average and best
TValue Map::remove(TKey c)
{
    int hash1 = hashFunction1(c);
    if (table1[hash1].element.first == c)
    {
        TValue value = table1[hash1].element.second;
        table1[hash1].element = NULL_TELEM;
        this->tableSize--;
        return value;
    }

    int hash2 = hashFunction2(c);
    if (table2[hash2].element.first == c)
    {
        TValue value = table2[hash2].element.second;
        table2[hash2].element = NULL_TELEM;
        this->tableSize--;
        return value;
    }

    return NULL_TVALUE;
}


///returns the number of pairs (key,value) from the map
///complexity: Θ(1) worst, average and best
int Map::size() const
{
    return this->tableSize;
}

///checks whether the map is empty or not
///complexity: Θ(1) worst, average and best
bool Map::isEmpty() const
{
    return this-> tableSize == 0;
}

///returns an iterator for the map
///complexity: Θ(1) worst, average and best
MapIterator Map::iterator() const
{
    return MapIterator(*this);
}



/// copy constructor
/// complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n)
Map::Map(const Map& other)
{
    capacity = other.capacity;
    tableSize = other.tableSize;

    table1 = new Bucket[capacity];
    table2 = new Bucket[capacity];


    for (int i = 0; i < capacity; i++)
    {
        table1[i].element = other.table1[i].element;
        table2[i].element = other.table2[i].element;
    }
}

///a method that returns another map where the keys are in a given interval
/// complexity: total: Θ(n), worst case Θ(n), average case Θ(n), best case: Θ(n)
Map Map::getMapInInterval(TKey start, TKey end) const
{
    Map intervalMap(*this); //use the copy constructor to create a new Map object

    MapIterator it = intervalMap.iterator(); //use the iterator of the intervalMap
    while (it.valid())
    {
        TKey currentKey = it.getCurrent().first;
        if (currentKey < start || currentKey > end)
        {
            intervalMap.remove(currentKey); //remove elements not in the interval from intervalMap
        }

        it.next();
    }

    return intervalMap; //return the modified intervalMap
}


//preconditions:
//the Map object on which getMapInInterval is called (*this) should be valid
//the start and end parameters should define a valid interval, start<=end

//postconditions:
//the method returns a new Map object intervalMap that contains only the key-value pairs from the original map in the specified interval
//the original Map object remains unchanged

//subalgorithm getMapInInterval(start, end) is:
//      init Map intervalMap(*this);
//      MapIterator it = intervalMap.iterator();
// while it is valid execute:
//      TKey currentKey = it.getCurrent().first
//      if currentKey<start or currentKey>end
//          intervalMap.remove(currentKey)
//      end-if
//      it->it.next
// end-while
//getMapInInterval<-intervalMap