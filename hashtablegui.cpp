#include "hashtablegui.h"
#include <cmath>
#include <QStringListModel>

HashTableGUI::HashTableGUI(int B, int C, HashFunction f)
    : HashTable(B, C, f), filename(""), isChanged(false)
{

}

void HashTableGUI::show(QListView *source)
{
    QStringList list = getWords();
    QStringListModel *model = new QStringListModel();
    model->setStringList(list);
    source->setModel(model);
}

void HashTableGUI::add(const std::string &word)
{
    if (HashTable::add(word))
        isChanged = true;
}

void HashTableGUI::clear()
{
    if (!HashTable::isEmpty()){
      isChanged = true;
      HashTable::clear();
    }
}

bool HashTableGUI::getIsChanged() const
{
    return isChanged;
}

std::string HashTableGUI::getFilename() const
{
    return filename;
}

void HashTableGUI::loadFromFile(const std::string &filename)
{
    this->filename = filename;
    HashTable::loadFromFile(filename);
    isChanged = false;
}

void HashTableGUI::saveToFile(const std::string &filename)
{
    this->filename = filename;
    HashTable::saveToFile(filename);
    isChanged = false;
}

double HashTableGUI::getCoefficient()
{
    double count = getCount();
    double c = count / N;

    double sum = 0;
    int *collisionsCount = getCollisionCount();

    for (int i = 0; i < N; i++) {
        double q = collisionsCount[i] - c;
        sum += q * q;
    }

    double result = sqrt(sum);
    return result;
}
