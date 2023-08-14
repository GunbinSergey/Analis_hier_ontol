#include "all_info.h"

All_info::All_info(QString table, QWidget* parent) : QWidget(parent)
{
    QStringList lhed;
    lhed << "Причина" << "Следствие";
    rep = new Repriz(lhed);

    //tabWid->addTab(real_view,"Причинно-следственнные связи");



    W_ier* ier_sys = new W_ier();
    tabWid = new QTabWidget;
    table2 = table.replace(" ", "");
    Repeat(table2, ier_sys);



    tabWid->addTab(rep,"Причинно-следственнные связи");

    //Find_children(table);
    //QString filter = "(Mother == 'Тело') AND (C0 == '')";
    //model->setFilter(filter);

    //model->select();

}

void All_info::Repeat(QString table, W_ier* ier_sys)
{
    QVBoxLayout* lay = new QVBoxLayout(this);

    QLabel* warning_txt = new QLabel;
    if (!ier_sys->is_hier_checked(table))
    {
        //warning_txt->setText(" <Center> <LI> <font color='red'> ВНИМАНИЕ! Иерархические связи не подтверждены! </LI> </>");
    }


    QWidget* wid = new QWidget;
    QVBoxLayout *layV = new QVBoxLayout(wid);
    tabWid->addTab(wid, "Онтология");

     SeSeVi* view = new SeSeVi(table);
     serch_model = view->model;

    QTableView* serch_view = view->view;
    connect(serch_view, SIGNAL(clicked(QModelIndex)),SLOT(term_info(QModelIndex)));
    QLabel* title = new QLabel("<font size = 12><CENTER> Извлечение наполнения вершин из нейроэксперта </front> </Center>");
    layV->addWidget(title);

     layV->addWidget(view);


    //W_emr* graf = new W_emr(model);
   // tabWid->addTab(graf, "Эмерджетность");
    //reset_filter();
    //tabWid->addTab(w_graf(), "Эмерджетность");

    QHBoxLayout* layH = new QHBoxLayout;
    layV->addLayout(layH);

    SeSeVi* vterm_1 = new SeSeVi(table, "операт");
    SeSeVi* vterm_2 = new SeSeVi(table, "качество");
    layH->addWidget(vterm_1);
    cheRel = new Wid_CheRel(rep);
    layH->addWidget(cheRel);
    layH->addWidget(vterm_2);


    QTableView* term1_v = vterm_1->view;
    connect(term1_v, SIGNAL(clicked(QModelIndex)),SLOT(term1_conect(QModelIndex)));

    QTableView* term2_v = vterm_2->view;
    connect(term2_v, SIGNAL(clicked(QModelIndex)),SLOT(term2_connect(QModelIndex)));

    cheRel->term1_model = vterm_1->model;
    cheRel->term2_model = vterm_2->model;

    QPushButton* but_update = new QPushButton("Редактировать");
    connect(but_update, SIGNAL(clicked()), this, SLOT(redact_ontl()));
    layV->addWidget(but_update);

    lay->addWidget(warning_txt);
    lay->addWidget(tabWid);
}

QWidget *All_info::w_sql(QString table, W_ier* ier_sys)
{

    QWidget* wid = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(wid);

    QHBoxLayout* lay_filtr = new QHBoxLayout;
    lay->addLayout(lay_filtr);

     pqle = new QLineEdit;
     lay_filtr->addWidget(pqle);


    QPushButton* fil_but = new QPushButton("Отфильтровать");

    connect(fil_but, SIGNAL(clicked()), SLOT(set_filter()));
    lay_filtr->addWidget(fil_but);

    QHBoxLayout* lay_radB = new QHBoxLayout;

    fil_buts.push_back(new QRadioButton("Код"));
    fil_buts.push_back(new QRadioButton("Уровень"));
    fil_buts.push_back(new QRadioButton("Термин"));
    fil_buts.push_back(new QRadioButton("Мат. термин"));
    fil_buts.push_back(new QRadioButton("Кольц. вершина"));
    fil_buts.push_back(new QRadioButton("Иер-ая связь"));
    fil_buts.push_back(new QRadioButton("Уст-ить ког карту"));


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
    QTableView* view = new QTableView();
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
    dop_info->setText("* - конечная вершина, \n"
                     "** - достоверность иерахической связи, \n"
                     "*** - использовать в когнетивной карте");

    lay->addWidget(dop_info);
    QHBoxLayout *lay_buts = new QHBoxLayout;
    lay->addLayout(lay_buts);
    QPushButton* but_update = new QPushButton("Редактировать");
    QPushButton* but_hier = new QPushButton("Проверка иерар-их связей");
    QPushButton* but_cog = new QPushButton("Проверить ког-ые связи");

    connect(but_cog, SIGNAL(clicked()), this, SLOT(add_cog()));

    ier_sys->model = model;
    ier_sys->connectBut(but_hier);

    connect(but_update, SIGNAL(clicked()), this, SLOT(redact_ontl()));


    lay_buts->addWidget(but_update);
    lay_buts->addWidget(but_hier);
    lay_buts->addWidget(but_cog);

    return wid;
}




void All_info::reset_filter()
{
    model->setFilter("");
    model->select();
}

QString All_info::ChatGPt_about_term(QString hcod)
{
    QString descr = "";
    if (hcod == "0")
    {
        descr = "<font size = 5> Медицинская помощь при риске инфекций области хирургического вмешательства - это комплекс медицинских мер, направленных на предотвращение инфекций после хирургических вмешательств у пациентов, находящихся в риске. Риск инфекции области хирургического вмешательства связан с подверженностью организма пациента стрессу после операции, возможной потерей крови, продолжительным использованием катетеров, противовоспалительных лекарств и других факторов, увеличивающих вероятность развития инфекции."
                "<br> В медицинскую помощь при риске инфекций области хирургического вмешательства входят меры связанные с проведением операции, такие как асептика (методы предотвращения попадания микроорганизмов в рану) и антисептика (методы устранения микроорганизмов в ране), экстренная профилактика антибиотиками, регулярное обследование организма пациента и качественная постоперационная реабилитация. Также в медицинскую помощь при риске инфекций области хирургического вмешательства могут входить рекомендации пациентам по правильному уходу за раной, контролю за состоянием раны, профилактике повторного инфицирования."
                "</font>";
    }
    return  descr;
}


void All_info::set_filter()
{
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
    QString filter = colum_name + " LIKE '%" + value +  "'";
    model->setFilter(filter);
    model->select();

}






void All_info::add_cog()
{
    //int num = tabWid->count() - 1;
    //QWidget* wid = new QWidget;
   // w_cog* cog =new w_cog(model->tableName());
   // tabWid->addTab(cog, "Когнетивные маршрут " + QString::number(num));
}

//void All_info::save_graf()
//{
//    QCv->grab().save(model->tableName() + "_plot.png");
//}


void All_info::redact_ontl()
{
    QWidget* wid = this->parentWidget();
    MainWindow* qmw = static_cast<MainWindow*>(wid);
    qmw->m_redact(table2);
}








void All_info::c1_change(QModelIndex index)
{
    //Переключение значения в с1
    if (index.column() != 6)
    {
        return;
    }

    QString now_value = model->data(index).toString();
    if (now_value == "*")
    {
        model->setData(index, "");
    }
    else
    {
        model->setData(index, "*");
    }
}

void All_info::term_info(QModelIndex index)
{
    //Вывод информации о термине
    QModelIndex in = index;
    int row = in.row();

    QString hcod = serch_model->data(serch_model->index(row,0)).toString();
    QString keyword = serch_model->data(serch_model->index(row,2)).toString();

    QString title = "Информации о термине: " + keyword;
    QString descr = cheRel->about_term(keyword);
    QMessageBox mes;
    mes.setWindowTitle("Мнение ChatGPT");
    mes.setText(title);
    mes.setInformativeText(descr);
    mes.exec();


}

void All_info::term1_conect(QModelIndex index)
{
    //Выбор термина 1
    QModelIndex in = index;
    int row = in.row();

    QSqlTableModel* mod1 = cheRel->term1_model;
    QString hcod1 = mod1->data(mod1->index(row,0)).toString();
    QString keyword1 = mod1->data(mod1->index(row,2)).toString();

    cheRel->term_1->setText(keyword1);
    cheRel->hcod_1->setText(hcod1);
}

void All_info::term2_connect(QModelIndex index)
{
    QModelIndex in = index;
    int row = in.row();

    QSqlTableModel* mod2 = cheRel->term2_model;
    QString hcod2 = mod2->data(mod2->index(row,0)).toString();
    QString keyword2 = mod2->data(mod2->index(row,2)).toString();

    cheRel->term_2->setText(keyword2);
    cheRel->hcod_2->setText(hcod2);

}
