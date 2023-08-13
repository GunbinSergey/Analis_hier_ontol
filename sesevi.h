#ifndef SESEVI_H
#define SESEVI_H

#include <QObject>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QRadioButton>
#include <QLabel>


class SeSeVi : public QWidget
{
    Q_OBJECT
    QLineEdit* pqle;
    QList<QRadioButton*> fil_buts;
    QList<QString>* colls;

    QLabel* dop_info;
    void reset_filter();
public:
    QTableView* view;
    QSqlTableModel* model;
    explicit SeSeVi(QString table, QString term  = "", QWidget *parent = nullptr);

private slots:
    void set_filter();


};

#endif // SESEVI_H
