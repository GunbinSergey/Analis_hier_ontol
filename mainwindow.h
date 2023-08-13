#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
//#include "redactor.h"
#include <QFile>
#include <QTextStream>
#include <QTreeView>



#include "all_info.h"
#include "redactor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void m_redact(QString table);
    void open_ontl(QString table);

private:
    Ui::MainWindow *ui;
    QVector<QRadioButton*> fil_buts;
    QStandardItemModel* qlm ;
    QList<QString> l_ontl();
    QList<QString>* colls;
    QTabWidget* tabWid;
    QLineEdit* pqle;
    QSqlTableModel* model;

    void del_ont(QString);

    void Create_Menu();
    bool CheckConnection();
    QWidget* last_files();
    QWidget* show_inform(QString table_name);
    //void Repeat(QString table, W_ier* ier_sys);
    //QWidget* w_sql(QString table, W_ier* ier_sys);
    void reset_filter();
private slots:
    void open_ont(QModelIndex index = QModelIndex());
    void m_create();
    void m_open();
    void m_save();
    //void set_filter();
    //void add_cog();
    //void redact_ontl();
    //void c1_change(QModelIndex index = QModelIndex());
};
#endif // MAINWINDOW_H
