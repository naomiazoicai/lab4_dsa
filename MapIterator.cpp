#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;
///complexity: total: O(n), worst case Θ(n), average case Θ(n) n-size of the dynamic array, best case: Θ(1)
///complexity: Θ(1) worst, average and best

MapIterator::MapIterator(const Map& d) : map(d)
{
    first();
}

///returns the first not-NULL_TELEM element
///complexity: total: O(n), worst case Θ(n), average case Θ(n), best case: Θ(1)
void MapIterator::first()
{
    currentBucketIndex = 0;
    while (currentBucketIndex < 2 * map.capacity)
    {
        if (currentBucketIndex < map.capacity)
        {
            if (map.table1[currentBucketIndex].element == NULL_TELEM)
            {
                currentBucketIndex++;
            }
            else
            {
                return;
            }
        }
        else
        {
            if (map.table2[currentBucketIndex % map.capacity].element == NULL_TELEM)
            {
                currentBucketIndex++;
            }
            else
            {
                return;
            }
        }
    }
}

///returns the next not-NULL_TELEM element
///complexity: total: O(n), worst case Θ(n), average case Θ(n), best case: Θ(1)
void MapIterator::next()
{
    if (!valid())
    {
        throw exception();
    }
    currentBucketIndex++;
    while (currentBucketIndex < 2 * map.capacity)
    {
        if (currentBucketIndex < map.capacity)
        {
            if (map.table1[currentBucketIndex].element == NULL_TELEM)
            {
                currentBucketIndex++;
            }
            else
            {
                return;
            }
        }
        else
        {
            if (map.table2[currentBucketIndex % map.capacity].element == NULL_TELEM)
            {
                currentBucketIndex++;
            }
            else
            {
                return;
            }
        }
    }
}

///returns the current element
///complexity: Θ(1) worst, average and best
TElem MapIterator::getCurrent()
{
    if (!valid())
    {
        throw exception();
    }

    if (currentBucketIndex < map.capacity)
    {
        return map.table1[currentBucketIndex].element;
    }
    else
    {
        return map.table2[currentBucketIndex % map.capacity].element;
    }
}

///checks if a position is valid
///complexity: Θ(1) worst, average and best
bool MapIterator::valid() const
{
    return 0 <= currentBucketIndex && currentBucketIndex < 2 * map.capacity;
}
