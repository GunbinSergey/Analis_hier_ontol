#ifndef REPRIZ_H
#define REPRIZ_H
//Хранилище найденных связей

#include <QWidget>
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
#include <QTableView>
#include <QStandardItemModel>

class Repriz : public QWidget
{
    Q_OBJECT
    QTableView* view;
    QStandardItemModel* data;
public:
    explicit Repriz(QStringList headers, QWidget *parent = nullptr);
    void rep_AddRow(QList<QString>);
signals:

};

#endif // REPRIZ_H
