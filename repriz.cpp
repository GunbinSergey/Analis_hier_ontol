#include "repriz.h"



Repriz::Repriz(QStringList headers, QWidget *parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    int colls = headers.size();
    data = new QStandardItemModel(0,colls);
   // QStringList lhed;
    //lhed << "Причина" << "Следствие";
    data->setHorizontalHeaderLabels(headers);
    view = new QTableView();
    lay->addWidget(view);
    view->setModel(data);
}

void Repriz::rep_AddRow(QList<QString> lis)
{
    int row = data->rowCount();
    data->insertRows(row,1);
    //row;
    int size = lis.length();
    for (int i = 0; i < size;++i) {
        data->setData(data->index(row,i),lis[i]);
    }

}
