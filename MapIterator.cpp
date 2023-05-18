#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    first();
}

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

bool MapIterator::valid() const
{
    return 0 <= currentBucketIndex && currentBucketIndex < 2 * map.capacity;
}
