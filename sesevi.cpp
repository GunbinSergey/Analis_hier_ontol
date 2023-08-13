#include "sesevi.h"

SeSeVi::SeSeVi(QString table, QString term, QWidget *parent) : QWidget(parent)
{
    //QWidget* wid = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(this);

    QHBoxLayout* lay_filtr = new QHBoxLayout;
    lay->addLayout(lay_filtr);

     pqle = new QLineEdit;
     lay_filtr->addWidget(pqle);
     pqle->setText(term);

    QPushButton* fil_but = new QPushButton("Отфильтровать");

    connect(fil_but, SIGNAL(clicked()), SLOT(set_filter()));
    lay_filtr->addWidget(fil_but);

    QHBoxLayout* lay_radB = new QHBoxLayout;

    fil_buts.push_back(new QRadioButton("Код"));
    fil_buts.push_back(new QRadioButton("Уровень"));
    fil_buts.push_back(new QRadioButton("Термин"));
    fil_buts.push_back(new QRadioButton("Мат. термин"));
    fil_buts.push_back(new QRadioButton("Кольц. вершина"));
    //fil_buts.push_back(new QRadioButton("Иер-ая связь"));
    //fil_buts.push_back(new QRadioButton("Уст-ить ког карту"));


    colls = new QList<QString>;
    lay->addLayout(lay_radB);
    for (int i = 0; i < fil_buts.size(); ++i)
    {
       //colls->push_back(model->headerData(i,Qt::Horizontal).toString());
       lay_radB->addWidget(fil_buts[i]);
    }

    //lay_radB->addWidget(new QRadioButton("Уровень"));
    //lay_radB->addWidget(new QRadioButton("Термин"));
    //lay_radB->addWidget(new QRadioButton("Мат. термин"));
    //lay_radB->addWidget(new QRadioButton("Кольц. вершина"));
    //lay_radB->addWidget(new QRadioButton("Иер-ая связь"));
    //lay_radB->addWidget(new QRadioButton("Уст-ить ког карту"));

    QPushButton* but = new QPushButton("Редактировать");


    model = new QSqlTableModel();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable(table);

    for (int i = 0; i < model->columnCount(); ++i)
    {
       colls->push_back(model->headerData(i,Qt::Horizontal).toString());
    }
    view = new QTableView();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
     connect(view, SIGNAL(clicked(const QModelIndex&)), SLOT(c1_change(const QModelIndex&)));

    view->setModel(model);

    QStringList list;
    list << "Иерарх. код" << "Уровень" << "Термин" << "Материнский термин" << "КВ*" << "ДИС**" << "ИвКК***";
    for (int i = 0; i < list.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, list[i]);
    }

    view->setColumnWidth(0, 125);
    view->setColumnWidth(1, 100);
    view->setColumnWidth(2, 350);
    view->setColumnWidth(3, 350);
    view->setColumnWidth(4, 50);
    view->setColumnWidth(5, 50);
    view->setColumnWidth(6, 50);


    model->select();
    lay->addWidget(view);
    QLabel* dop_info = new QLabel;
    dop_info->setText("* - конечная вершина \n");
//                     "** - достоверность иерахической связи, \n"
//                     "*** - использовать в когнетивной карте");

    lay->addWidget(dop_info);
    QHBoxLayout *lay_buts = new QHBoxLayout;
    lay->addLayout(lay_buts);
    //QPushButton* but_update = new QPushButton("Редактировать");
    //QPushButton* but_hier = new QPushButton("Проверка иерар-их связей");
    //QPushButton* but_cog = new QPushButton("Проверить ког-ые связи");

    //connect(but_cog, SIGNAL(clicked()), this, SLOT(add_cog()));

    //ier_sys->model = model;
    //ier_sys->connectBut(but_hier);

   // connect(but_update, SIGNAL(clicked()), this, SLOT(redact_ontl()));


    //lay_buts->addWidget(but_update);
    //lay_buts->addWidget(but_hier);
    //lay_buts->addWidget(but_cog);

}

void SeSeVi::reset_filter()
{
    model->setFilter("");
    model->select();
}

void SeSeVi::set_filter()
{
    //Фильтрация онтологии
    reset_filter();

    //QString filtr_col;

    int act_header = -1;
    int size = model->columnCount();
    for (int i = 0; i < size; ++i)
    {
        //qDebug() << fil_buts[i]->isChecked();
       if( fil_buts[i]->isChecked())
       {
            act_header = i;
            break;
       }
    }
    if (act_header == -1)
    {
        reset_filter();
        return;
    }

    QString colum_name = (*colls)[act_header];

    QString value = pqle->text();
    QString filter = colum_name + " LIKE '%" + value +  "%'";
    model->setFilter(filter);
    model->select();

}

