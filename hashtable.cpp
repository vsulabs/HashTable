#include <fstream>
#include "hashtable.h"
#include "info.h"

HashTable::HashTable(int C, int D, HashFunction f)
{
    this->C = C;
    this->D = D;
    this->hashFunc = f;
    Clear();
}

void HashTable::Clear()
{
    this->count = 0;
    for (int i = 0; i < N; i++) {
        table[i].state = FREE;
    }
}

HashTable::~HashTable()
{
    Clear();
}

int HashTable::getCount() const
{
    return count;
}

int *HashTable::getCollisionCount() const
{
    return collisionCount;
}

valueType *HashTable::toArray() const
{
    valueType *result = new valueType[N];
    for (int i = 0; i < N; i++) {
        result[i] = table[i].info;
    }

    return result;
}

bool HashTable::find(const valueType& key) const
{
    int a = indexOf(key);
    return a >= 0;
}

bool HashTable::del(const valueType& key)
{
    int a = indexOf(key);
    if (a < 0) {
        return false;
    }

    table[a].state = DEL;
    count--;
    return true;
}

bool HashTable::add(const valueType& key)
{
    int a0 = getHash(key);
    collisionCount[a0]++;

    int a = a0;
    int i = 0;
    int d = -1;
    bool stop = false;

    while (!stop && i < N) {
        switch(table[a].state) {
        case FULL:
            if (isKeysEquals(key, table[a].info)) {
                return false;
            }
            a = nextCell(a0, i);
            break;
        case DEL:
            if (d == -1) {
                d = a;
            }
            a = nextCell(a0, i);
            break;
        case FREE:
            stop = true;
            break;
        }
    }

    // Eсли таблица полная
    if (!stop && d == -1) {
        return false;
    }

    // Если нашли место, где удалена запись
    if (d != -1) {
        a = d;
    }

    table[a].info = key;
    table[a].state = FULL;
    count++;

    return true;
}

void HashTable::saveToFile(const std::string& fileName) const
{
    std::ofstream f(fileName);
    for (int i = 0; i < N; i++) {
        if (table[i].state == CellState::FULL) {
            f << table[i].info;
        }
    }
}

bool HashTable::loadFromFile(const std::string& fileName)
{
    std::ifstream f(fileName);
    if (!f.is_open())
        return false;

    valueType info;

    while (f >> info) {
        bool added = this->add(info);
        if (!added)
            return false;
    }

    return true;
}

int HashTable::getHash(const valueType& info) const
{
    return hashFunc(info) % N;
}

int HashTable::nextCell(int a0, int &i) const
{
    i++;
    return (a0 + C*i + D*i*i) % N;
}

int HashTable::indexOf(const valueType& info) const
{
    int a0 = getHash(info);
    int a = a0;
    int result = -1;
    for (int i = 0; i < N; i++) {
        switch(table[a].state) {
        case FREE:
            return -1;
        case FULL:
            if (isKeysEquals(info, table[a].info))
                return a;
        case DEL:
            a = nextCell(a0, i);
            break;
        }
    }

    return result;
}
