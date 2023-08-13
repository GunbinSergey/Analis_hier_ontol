#ifndef W_ier_H
#define W_ier_H
//Виджет проверки иерархической связи
#include <QObject>
#include <QWidget>
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
#include <QMessageBox>
#include <QPushButton>

class W_ier : public QWidget
{
    Q_OBJECT

    char hier_rel_check(QString mother, QString child);
    void reset_filter();

public:
    QLabel* le_status;
    QSqlTableModel* model;
    explicit W_ier(QWidget *parent = nullptr);
    bool is_hier_checked(QString table);
    void connectBut(QPushButton *but);

public slots:
    void hier_set();

};

#endif // W_ier_H
