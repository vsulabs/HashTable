#ifndef HASHTABLEGUI_H
#define HASHTABLEGUI_H

#include "hashtable.h"
#include <string>
#include <QListView>

class HashTableGUI : public HashTable
{
public:
    HashTableGUI(int B, int C, HashFunction f);

    void show(QListView *source);

    void add(const std::string &word);
    void clear();
    bool getIsChanged() const;

    std::string getFilename() const;
    void loadFromFile(const std::string &filename);
    void saveToFile(const std::string &filename);

    double getCoefficient();
private:
    bool isChanged;
    std::string filename;
};

#endif // HASHTABLEGUI_H
