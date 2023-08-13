#ifndef ALL_INFO_H
#define ALL_INFO_H

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
#include <QMessageBox>
#include "mainwindow.h"

#include <cmath>
#include <QStandardItemModel>
#include <QMessageBox>
#include "w_ier.h"
#include "sesevi.h"
#include "wid_cherel.h"
#include "repriz.h"

class All_info: public QWidget
{
public:
    All_info(QString table, QWidget *parent = 0);
    Q_OBJECT


    QVector<QRadioButton*> fil_buts;
private:
    void Repeat(QString table, W_ier* ier_sys);
    QList<QString>* colls;
    QTabWidget* tabWid;
    QLineEdit* pqle;

    QSqlTableModel* serch_model;

    Repriz *rep;

    QWidget* w_sql(QString table, W_ier* ier_sys);

    QSqlTableModel* model;
    void reset_filter();
    QString ChatGPt_about_term(QString hcod);
    Wid_CheRel* cheRel;

    QString table2;
    //void con_cherel_te

private slots:
    void set_filter();
    //void hier_set();
    void add_cog();
    //void save_graf();
    void redact_ontl();
    void c1_change(QModelIndex index = QModelIndex());
    void term_info(QModelIndex index = QModelIndex());
    void term1_conect(QModelIndex index = QModelIndex());
    void term2_connect(QModelIndex index = QModelIndex());
};

#endif // ALL_INFO_H
