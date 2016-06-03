#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "info.h"

using _HashFunction = int(const valueType& key);
using HashFunction = _HashFunction*;

class HashTable
{
public:
    static const int N = 19;
    enum CellState { FREE, FULL, DEL };

    struct Cell
    {
        valueType info;
        CellState state;
    };

    HashTable(int C, int D, HashFunction hashFunc);
    void Clear();
    ~HashTable();

    int getCount() const;
    valueType* toArray() const;

    bool find(const valueType& key) const;
    bool del(const valueType& key);
    bool add(const valueType& key);

    void saveToFile(const std::string& fileName) const;
    bool loadFromFile(const std::string& fileName);

protected:
    int getHash(const valueType& key) const;
    int nextCell(int a0, int& i) const;
    int indexOf(const valueType& key) const;
private:
    HashFunction hashFunc;
    Cell table[N];
    int count;

    // Коэффициенты
    int C, D;
};

#endif // HASHTABLE_H
