#include "hashtable.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int hash1(const std::string& word) {
    return word.length();
}

int main(int argc, char *argv[])
{
    HashTable map(2, 3, hash1);
    map.loadFromFile("/home/diadlo/Solution/VSU/Delphi/HashTable/test.txt");
    std::cout << map.getCount();
    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
