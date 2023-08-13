#include "w_ier.h"

W_ier::W_ier(QWidget *parent) : QWidget(parent)
{

}


void W_ier::hier_set()
{

        reset_filter();
        char c = ' ';
        //model->select();





        //QSqlRecord rec = model->record(i);
        //QString mother = rec.value("Keyword").toString();
        //QString mother = model->data(model->index(i, 2)).toString();
        // QString filter = "((Mother == '" + mother + "'))";
       // if (i == 0)
       // {
           //QString filter = "(Mother == '" + mother + "') AND (C0 != '+')";
       // }


        model->setFilter("");
        int len = model->rowCount();

        for (int i = 1; i < len; ++i)
        {
            //QSqlRecord rec_c = model->record(i2);
            QString mother = model->data(model->index(i, 3)).toString();
            QString child = model->data(model->index(i, 2)).toString();
            //QString child =  rec_c.value("Keyword").toString();
            if (mother != child)
            {
                c = hier_rel_check(mother, child);
            }
            if (c == 'X')
            {
                break;
            }
            model->setData(model->index(i,5), QString(c));
        }



     if (!is_hier_checked(model->tableName()))
     {
         le_status->setText(" <Center> <LI> <font color='red'> ВНИМАНИЕ! Иерархические связи не подтверждены! До проверки иерархических связей рассмотрение не имеет смысла! </LI> </>");
     }
     else
     {
           le_status->setText(" ");
     }

    reset_filter();
}


char W_ier::hier_rel_check(QString mother, QString child)
{
    QMessageBox *box = new QMessageBox;
    box->setWindowTitle("Протоколирование иерархических связей");
    box->setText("Подтвердите наличие связи между теримтнами: <H1>" + mother +
                 " </H2> // " + child + " </H2> ");
    //box->setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Ignore | QMessageBox::Abort);
    //box->addButton("Закрыть", QMessageBox::RejectRole);
    QAbstractButton *bYes = box->addButton("Да", QMessageBox::AcceptRole);
    QAbstractButton *bNo = box->addButton("Нет", QMessageBox::RejectRole);
    QAbstractButton *bAbort = box->addButton("Прервать", QMessageBox::NoRole);
    //QAbstractButton *bSkip = box->addButton("Пропуск", QMessageBox::ApplyRole);

    box->setEscapeButton(bAbort);


   // QAbstractButton *bNo = box->addButton("Нет", QMessageBox::NoRole);
    //box->setEscapeButton(QMessageBox::Abort);
    //box->setDefaultButton(QMessageBox::Abort);
    box->resize(250,250);
    int num = box->exec();

 if (box->clickedButton() == bYes)
 {
     return '+';
 }
 else if (box->clickedButton() == bNo)
 {
     return ' ';

 }
 else if (box->clickedButton() == bAbort)
 {
     return 'X';

 }
 //else if (box->clickedButton() == bSkip)
 //{
 //    return '?';
//
// }

 return 'X';
}

bool W_ier::is_hier_checked(QString table)
{
    QSqlTableModel mod2;
    mod2.setTable(table);
    mod2.select();

    int num = mod2.rowCount();
    qDebug() << num;

    qDebug() << mod2.headerData(5, Qt::Horizontal).toString() << mod2.headerData(1, Qt::Horizontal).toString();
    QString filtr = "(((C0 IS NULL) OR (C0 != '+')) AND  Lev != 0)";
    qDebug() << filtr;
    mod2.setFilter(filtr);
    mod2.select();
    num = mod2.rowCount();
    qDebug() << num;
    mod2.setFilter("");
    mod2.select();
    if (num == 0)
    {
        return true;
    }
    return false;
}

void W_ier::connectBut(QPushButton *but)
{
    connect(but, SIGNAL(clicked()), this, SLOT(hier_set()));
}

void W_ier::reset_filter()
{
    model->setFilter("");
    model->select();
}
