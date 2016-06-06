#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "info.h"

#include <QStringList>

using _HashFunction = int(const Key& key);
using HashFunction = _HashFunction*;

class HashTable
{
public:
    static const int N = 199;
    enum CellState { FREE, FULL, DEL };

    struct Cell
    {
        Key info;
        CellState state;
    };

    HashTable(int C, int D, HashFunction hashFunc);
    ~HashTable();

    int getCount() const;
    int* getCollisionCount();
    QStringList getWords() const;

    bool isEmpty() const;
    bool find(const Key& key) const;
    //bool del(const Key& key);
    bool add(const Key& key);
    void clear();

    void saveToFile(const std::string& fileName) const;
    bool loadFromFile(const std::string& fileName);
protected:
    int getHash(const Key& key) const;
    int nextCell(int a0, int& i) const;
    int indexOf(const Key& key) const;
private:
    HashFunction hashFunc;
    int collisionCount[N];
    Cell table[N];
    int count;

    // Коэффициенты
    int C, D;
};

#endif // HASHTABLE_H
