#ifndef READER_H
#define READER_H
//Блок считывания онтологии

#include <QObject>
#include <QWidget>

#include <QLabel>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
//#include <QRadioButton>
#include <QRadioButton>
#include <QPushButton>
#include <QStandardItemModel>
#include <QMainWindow>
#include "redactor.h"
#include <QFile>
#include <QGridLayout>
#include <QFileDialog>


class Reader : public QWidget
{
    Q_OBJECT

     QLineEdit* separ;
     QLineEdit* file_path;


     QList<QString>* data_file(QString path);

public:
    QStandardItemModel* model;
    explicit Reader(QWidget *parent = nullptr);

private slots:
     void chose_file();
     void open_file();

};

#endif // READER_H
