#ifndef WID_CHEREL_H
#define WID_CHEREL_H
//Виджет проверки связкй через chatgpt
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
#include <QMessageBox>
#include <QLabel>
#include "repriz.h"

class Wid_CheRel : public QWidget
{
    Q_OBJECT
public:
    explicit Wid_CheRel(Repriz* rep, QWidget *parent = nullptr);
    QString ChatGpt_about_real(QString hcod1, QString hcod2);

    QLineEdit* hcod_1;
    QLineEdit* hcod_2;

    QLineEdit* term_1;
    QLineEdit* term_2;

    QSqlTableModel* term1_model;
    QSqlTableModel* term2_model;

    Repriz* saver;

    QString check_real_gpt();

private slots:
    void Check_real();


};

#endif // WID_CHEREL_H
