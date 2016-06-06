#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QStringListModel>
#include <QInputDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList stringList;
    for (QString name : hashName) {
        stringList.append(name);
    }

    ui->cbHashFunc1->addItems(stringList);
    ui->cbHashFunc2->addItems(stringList);

    hashTable = new HashTableGUI(B, C, hashFunctions[0]);
}

void MainWindow::updateStatus() {
  ui->hashTableView->setVisible(isOpened);

  ui->actionAdd->setEnabled(isOpened);
  ui->actionSave->setEnabled(isOpened);
  ui->actionSaveAs->setEnabled(isOpened);
  ui->actionClose->setEnabled(isOpened);

  bool isNotEmpty = isOpened && !hashTable->isEmpty();

  ui->actionClear->setEnabled(isNotEmpty);
  if (isNotEmpty) {
      int index1 = ui->cbHashFunc1->currentIndex();
      HashFunction f1 = hashFunctions[index1];
      calcCoefficient(f1, ui->lResult1);

      int index2 = ui->cbHashFunc2->currentIndex();
      HashFunction f2 = hashFunctions[index2];
      calcCoefficient(f2, ui->lResult2);
  } else {
      ui->lResult1->setText("");
      ui->lResult2->setText("");
  }
}

bool MainWindow::canClose() {
  const QString exitTitle = "Выход";
  const QString exitText = "Дерево было изменено, сохранить перед закрытием?";
  const QMessageBox::StandardButtons buttons =
      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;

  int answer = QMessageBox::No;

  bool isCanClose = true;
  if (hashTable != nullptr && hashTable->getIsChanged()) {
    answer = QMessageBox::question(this, exitTitle, exitText, buttons);
    switch (answer) {
      case QMessageBox::Yes:
        on_actionSave_triggered();
        isCanClose = !hashTable->getIsChanged();
        break;
      case QMessageBox::No:
        break;
      case QMessageBox::Cancel:
        isCanClose = false;
    }
  }
  if (isCanClose) {
    delete hashTable;
    hashTable = nullptr;
    isOpened = false;
  }
  return isCanClose;
}

int MainWindow::length(const Key &key)
{
    return key.length();
}

int MainWindow::sum(const Key &key)
{
    int result;
    for (int i = 0; i < key.length(); i++) {
        unsigned char ch = key[i];
        result += ch;
    }
    return result;
}

int MainWindow::average(const Key &key)
{
    return sum(key) / key.length();
}

int MainWindow::lengthSqr(const Key &key)
{
    int len = length(key);
    return B * len + C * len * len;
}

int MainWindow::averageSqr(const Key &key)
{
    int aver = average(key);
    return B * aver + C * aver * aver;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if (canClose()) {
      hashTable = new HashTableGUI(B, C, hashFunctions[0]);
      hashTable->show(ui->hashTableView);
      isOpened = true;
      updateStatus();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    const QString saveTitile = "Открыть";
    const QString saveFormat = "Текстовый файл (*.txt)";
    QString filename = QFileDialog::getOpenFileName(this, saveTitile, "", saveFormat);

    if (filename != "" && canClose()) {
      hashTable = new HashTableGUI(B, C, hashFunctions[0]);
      isOpened = true;
      hashTable->loadFromFile(filename.toUtf8().constData());
      hashTable->show(ui->hashTableView);
      updateStatus();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (hashTable->getFilename() == "") {
      on_actionSaveAs_triggered();
      return;
    }
    hashTable->saveToFile(hashTable->getFilename());
    updateStatus();
}

void MainWindow::on_actionSaveAs_triggered()
{
    const QString saveTitile = "Сохранить";
    const QString saveFormat = "Текстовый файл (*.txt)";
    QString oldFilename;
    oldFilename.fromStdString(hashTable->getFilename());
    QString filename = QFileDialog::getSaveFileName(this, saveTitile, oldFilename, saveFormat);
    if (filename == "")
      return;
    hashTable->saveToFile(filename.toUtf8().constData());
    updateStatus();
}


void MainWindow::on_actionExit_triggered()
{
    if (canClose()) {
      QCoreApplication::quit();
    }
}

void MainWindow::on_actionAdd_triggered()
{
    bool ok;
    const QString addTitile = "Добавление";
    const QString addText = "Введите слово для добавления в дерево";
    QString text = QInputDialog::getText(this, addTitile, addText, QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
      try {
        hashTable->add(text.toUtf8().constData());
        hashTable->show(ui->hashTableView);
        updateStatus();
      } catch (const std::invalid_argument &e) {
        QMessageBox(QMessageBox::Critical, "Ошибка", e.what()).exec();
      }
    }
}

void MainWindow::on_actionFind_triggered()
{
    const QString findTitile = "Поиск";
    const QString findText = "Введите слово для поиска в дереве";
    bool ok;
    QString text = QInputDialog::getText(this, findTitile, findText, QLineEdit::Normal, "", &ok);
    bool found = hashTable->find(text.toUtf8().constData());
    const QString findResultTitile = "Результат поиска";
    QString findResultText;
    if (found) {
      findResultText = "Слово найдено";
    } else {
      findResultText = "Слово не найдено";
    }
    QMessageBox(QMessageBox::Information, findResultTitile, findResultText).exec();
}

void MainWindow::on_actionClear_triggered()
{
    const QString clearTitile = "Очистка";
    const QString clearText = "Вы точно хотите очистить дерево?";
    int answer = QMessageBox::question(this, clearTitile, clearText, QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        hashTable->clear();
        hashTable->show(ui->hashTableView);
        updateStatus();
    }
}

void MainWindow::on_actionInfo_triggered()
{
    const QString taskTitile = "Условие задачи";
    const QString taskText = "Из hashTable-дерева удалить все слова с четной длинной";
    QMessageBox(QMessageBox::Information, taskTitile, taskText).exec();
}

void MainWindow::on_actionClose_triggered()
{
    if (canClose()) {
        QStringListModel *model = new QStringListModel();
        ui->hashTableView->setModel(model);
        updateStatus();
    }
}

void MainWindow::on_cbHashFunc1_activated(int index)
{
    updateStatus();
}

void MainWindow::on_cbHashFunc2_activated(int index)
{
    updateStatus();
}

void MainWindow::calcCoefficient(HashFunction f, QLabel *label)
{
    HashTableGUI newHashTable(B, C, f);

    QStringList list = hashTable->getWords();
    for (int i = 0; i < hashTable->getCount(); i++) {
        newHashTable.add(list[i].toStdString());
    }

    double c = newHashTable.getCoefficient();
    label->setText(resultText + QString::number(c));
}
