#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "hashtablegui.h"

#include <QLabel>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();
    void on_actionAdd_triggered();
    void on_actionFind_triggered();
    void on_actionClear_triggered();
    void on_actionInfo_triggered();
    void on_actionClose_triggered();

    void on_cbHashFunc1_activated(int index);
    void on_cbHashFunc2_activated(int index);

private:
    void calcCoefficient(HashFunction f, QLabel *label);
    void updateStatus();
    bool canClose();

    const static int B = 2;
    const static int C = 2;

    const QString resultText = "Среднее квадратичное\nотклонение: ";

    static int length(const Key &key);
    static int sum(const Key &key);
    static int average(const Key &key);
    static int lengthSqr(const Key &key);
    static int averageSqr(const Key &key);

    const static int N = 5;
    HashFunction hashFunctions[N] = {length, sum, average, lengthSqr, averageSqr};
    QString hashName[N] = {
        "Длина слова", "Сумма кодов символов", "Среднее арифемтическое кодов",
        "a*x^2 + b*x от длины", "a*x^2 + b*x от среднего" };

    bool isOpened;
    HashTableGUI *hashTable;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
