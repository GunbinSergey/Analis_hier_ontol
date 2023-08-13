#ifndef REDACTOR_H
#define REDACTOR_H
//Модуль ввода онтологии
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QTreeView>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QTableView>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QTabBar>
#include <QSqlTableModel>
#include <QTableView>
#include <QMessageBox>
#include "mainwindow.h"
#include <QDateTime>

#include<QTabWidget>

//Виджет считывания онтологии из txt файла
#include "reader.h"


enum cols
{
    add_but,
    del_but,
    ugl_but,
    hcod,
    keyword,
    len
};



class Redactor : public QWidget
{
    Q_OBJECT
private:
    QWidget* create_button(QString label) const;
    QStandardItemModel* model;
    QTreeView* qtv;
    QString new_hcod(QString father, int row_now, bool Inside);
    QLineEdit* ple;
    QStandardItemModel* data_file;
    QTabWidget* tab_wid;

    void Reset();
    void SQL_To_Redact(QString table_name);
    void SQL_Redact(int father_row, QSqlTableModel* mod, QString fath_name, QString fath_cod = "",  QModelIndex parent = QModelIndex());
    void Add_buttons(QModelIndex index, int num_row, QString par_code, bool inside);
    void forEach(QModelIndex parent = QModelIndex());
    void CreateTable(QString tab_name);
    void SMI_to_SQL (QString tab_name, QModelIndex parent = QModelIndex());
    void Update_Hcod(QModelIndex parent = QModelIndex(), QString fath_name = "");
    void S_ontl_name(QString name);
    void Dop_info(QString table);
    void reset_filter(QSqlTableModel* model);
    void file_to_SQL(QString table);
    QWidget* wind_redactor();
    QWidget* wind_from_file();


public:
    explicit Redactor(QWidget *parent = nullptr);
    explicit Redactor(QString table_name, QWidget *parent = nullptr);

private slots:
     void in_insert_row();
     void insert_row();
     void Save_inSQL();
     void remove_row();
     void open_ontl();

};

#endif // REDACTOR_H
