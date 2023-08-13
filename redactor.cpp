#include "redactor.h"

void Redactor::Reset()
{
    QVBoxLayout* lay_main = new QVBoxLayout;
    this->setLayout(lay_main);
    tab_wid = new QTabWidget;
    lay_main->addWidget(tab_wid);
    tab_wid->addTab(wind_redactor(), "Графический редактор");

    Reader* red = new Reader();
    tab_wid->addTab(red, "Чтение из файла");
    data_file = red->model;

    QLabel* lab = new QLabel("Название онтологии");
    lay_main->addWidget(lab);

    ple = new QLineEdit();
    lay_main->addWidget(ple);

    QPushButton* but = new QPushButton("Сохранить");
    lay_main->addWidget(but);

    connect(but, SIGNAL(clicked()), this, SLOT(Save_inSQL()));



}


QWidget* Redactor::wind_from_file()
{
    QWidget* wid = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout;
    wid->setLayout(lay);

   QLabel* lab_desc = new QLabel("Выберите поиск файла");


    return wid;
}

 QWidget* Redactor::wind_redactor()
 {
     QWidget* wid = new QWidget;
     QVBoxLayout* lay = new QVBoxLayout;
     wid->setLayout(lay);
     QLabel* title = new QLabel("<Center> Редактор</Center>");
     model = new QStandardItemModel(1,len);

     QStringList header;
     header << " " << " " << " " << "Код вершины" << "Термин";
     model->setHorizontalHeaderLabels(header);

     qtv = new QTreeView;
     qtv->setModel(model);

     lay->addWidget(title);
     lay->addWidget(qtv);



      QModelIndex index = model->index(0,hcod);
      model->setData(index, "0");
      index = model->index(0,add_but);
      //qtv->setIndexWidget(index, create_button("+"));
      index = model->index(0,del_but);
      qtv->setIndexWidget(index, create_button("V"));
      index = model->index(0,ugl_but);
     // qtv->setIndexWidget(index, create_button("-"));



     //insert_row();
      //insert_row();
      //insert_row();
      return wid;
 }


void Redactor::SQL_To_Redact(QString table_name)
{
    QString Hcod;

    QSqlTableModel* sql_model = new QSqlTableModel;
    sql_model->setTable(table_name);


    SQL_Redact(0, sql_model, "test","0");


}

void Redactor::SQL_Redact(int father_row, QSqlTableModel* mod,QString fath_name, QString fath_cod, QModelIndex parent)
{


    QString filter = "(Hcod LIKE '"+ fath_cod +"._')";
    if (fath_cod == "0")
    {
      filter = "((Hcod LIKE '_') AND (Hcod != 0))";
      mod->setFilter("");
      mod->select();
      QString f_keyword = mod->data(mod->index(0,2)).toString();
       model->setData(model->index(0, keyword), f_keyword);
    }
    mod->setFilter(filter);
    mod->select();


    int size = mod->rowCount();
    for (int i = 0; i < size; ++i)
    {
        QString c_hcod = mod->data(mod->index(i,0 )).toString();
        QString c_keyword = mod->data(mod->index(i,2)).toString();

        QModelIndex index = model->index(father_row, 0, parent); //++


        //index = model->index(row_now, 0, index.parent());
        model->insertRows(i, 1, index);


         if (i == 0)
         {
           model->insertColumns(0, len, index);
         }


         Add_buttons(index, i, fath_cod, true);

       int id = index.row();
       model->setData(model->index(i,keyword, index), c_keyword);

       //model->setData(mod->index(0, keyword, parent), c_keyword);
       //model->setData(model->index(num_row, hcod, index), hcod2);


         QString filter = "(Hcod LIKE '"+ c_hcod +"._')";
         mod->setFilter(filter);
         mod->select();
         int size_c = mod->rowCount();

        if( size_c != 0) {
             //index = model->index(father_row, 0, index);
             SQL_Redact(i, mod, c_keyword, c_hcod, index);
        }
        filter = "(Hcod LIKE '"+ fath_cod +"._')";
        if (fath_cod == "0")
        {
          filter = "((Hcod LIKE '_') AND (Hcod != 0))";
        }
        mod->setFilter(filter);
        mod->select();
        //Add_buttons(model->index(i,0), i, )
    }
}

void Redactor::Add_buttons(QModelIndex index, int num_row, QString par_code, bool inside)
{
    qtv->setIndexWidget(model->index(num_row,add_but, index), create_button("+"));
    qtv->setIndexWidget(model->index(num_row,del_but, index), create_button("V"));
    qtv->setIndexWidget(model->index(num_row,ugl_but, index), create_button("-"));


    QString hcod2 = new_hcod(par_code,  num_row,  inside);

    //index = model->index(num_row, hcod, index.parent());
    //QString hcod_parent = model->data(index).toString();



    model->setData(model->index(num_row, hcod, index), hcod2);
}

QWidget *Redactor::create_button(QString label) const
{
    QWidget* wgt = new QWidget;
    QBoxLayout* l = new QHBoxLayout;
    QPushButton* btn = new QPushButton( label );
    if (label == "+")
    {
      connect( btn, SIGNAL(clicked( bool )), SLOT( insert_row() ) );
    }
    if (label == "V")  {
       connect(btn, SIGNAL(clicked()), this, SLOT(in_insert_row()));
    }
    if (label == "-")
    {       
        connect(btn, SIGNAL(clicked()), this, SLOT(remove_row()));
    }



    l->setMargin( 0 );
    l->addWidget( btn );
    l->addStretch();
    wgt->setLayout( l );

    return wgt;
}

void Redactor::in_insert_row()
{

    QModelIndex index;
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) )
    {
             index = qtv->indexAt( btn->parentWidget()->pos() );

             int row_now = index.row();
              QString par_cod = model->data(model->index(row_now, hcod, index.parent())).toString();

             index = model->index(row_now, 0, index.parent());



             int row_next = model->rowCount(index);

               model->insertRows(row_next, 1, index);


              if (row_next == 0)
              {
                model->insertColumns(0, len, index);
              }
              Add_buttons(index, row_next, par_cod, true);



             // QModelIndex index_sec = model->insertRows();
    }



}

void Redactor::insert_row()
{
    QModelIndex index;
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) )
    {
             index = qtv->indexAt( btn->parentWidget()->pos() );
             int row_now = index.row();
              QString par_cod = model->data(model->index(row_now, hcod, index.parent())).toString();

             index = model->index(row_now, 0, index.parent());


             int row_next = model->rowCount(index.parent());
             model->insertRows(row_next, 1, index.parent());

             Add_buttons(index.parent(), row_next, par_cod, false);

             // QModelIndex index_sec = model->insertRows();
    }


    //model->insertColumns(0, 2);

}

void Redactor::Save_inSQL()
{

    QMessageBox mes;
    mes.setWindowTitle("ОШИБКА!");
    mes.setText("Невозможно сохранить онтологию с таким именем");
    mes.setStandardButtons(QMessageBox::Ok);
    QString tab_name = ple->text();
    tab_name.replace(" ", "");
    if (tab_name == "")
    {
        mes.exec();
        return;
    }
    char firs_let = (tab_name.toUtf8())[0];

    if ( '0' < firs_let and '9' > firs_let)
    {
        mes.exec();
        return;
    }

    CreateTable(tab_name);
    if (tab_wid->currentIndex() == 0)
    {

     SMI_to_SQL(tab_name);

    }
    else { //Считывание с файла
        //data_file
       file_to_SQL(tab_name);
    }

    Dop_info(tab_name);
    S_ontl_name(tab_name);


    //SMI_to_SQL();
    QWidget* wid = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(wid);
    QSqlTableModel* model = new QSqlTableModel;
    model->setTable(tab_name);
    model->select();
    QTableView* view = new QTableView();
    lay->addWidget(view);
    view->setModel(model);
    wid->resize(750, 300);
    //wid->show();

    open_ontl();

}

void Redactor::remove_row()
{
    if( QPushButton* btn = qobject_cast< QPushButton* >( sender() ) )
    {
        QModelIndex index = qtv->indexAt( btn->parentWidget()->pos() );
        int row_now = index.row();
        index = model->index(row_now, 0, index.parent());
        //int row_count = model->rowCount(index.parent());
        model->removeRows(row_now,1, index.parent());
        Update_Hcod();
        //row_count = model->rowCount(index.parent());
        //row_count = model->rowCount(index);
    }
}

void Redactor::open_ontl()
{
    QMessageBox mes;
    mes.setWindowTitle("Открыть созданую онтологию?");
    mes.setText("Хотите продолжить работу с созданной онтологией");
    mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int res = mes.exec();

    if (res == QMessageBox::No)
    {
        return;
    }


    QWidget* wid = this->parentWidget();
    MainWindow* qmw = static_cast<MainWindow*>(wid);
    QString table = ple->text();
    qmw->open_ontl(table);
}

void Redactor::CreateTable(QString tab_name)
{
    QSqlQuery query;

    QString str_f;

    str_f = "DROP Table " + tab_name + "";

    if (!query.exec(str_f))
    {
        qDebug() << "Unable to remove table";
    }

    str_f = "CREATE Table " + tab_name + " ("
    "Hcod Char(16) PRIMARY KEY,"
    "Lev INT,"
    "Keyword Char(75) NOT NULL,"
    "Mother Char(75),"
    "Pr Char(1))";
    //"C0 Char(2),"
    //"C1 Char(2)"
    //")";

    if (!query.exec(str_f))
    {
        qDebug() << "Unable to create table";
    }


}

void Redactor::file_to_SQL(QString table)
{
    int size = data_file->rowCount();

    QSqlQuery query;
    QString str_f = "INSERT INTO " + table + "(Hcod, Keyword)"
            "VALUES ('%1', '%2')";
    for(int i = 0; i < size; ++i) {
        QString cod = data_file->data(data_file->index(i,0)).toString();
        QString word = data_file->data(data_file->index(i,1)).toString();
        QString str_in = str_f.arg(cod,word);

        if (!query.exec(str_in))
        {
            qDebug() << "Unable to create table" << cod << "//" << word;
        }

       }


}



void Redactor::SMI_to_SQL (QString tab_name, QModelIndex parent) {
    QSqlQuery query;
    QString str_f = "INSERT INTO " + tab_name + "(Hcod, Keyword)"
            "VALUES ('%1', '%2')";
    for(int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);

        QVariant name = model->data(index);


        QString cod = model->data(model->index(r,hcod,index.parent())).toString();
        QString word = model->data(model->index(r,keyword,index.parent())).toString();
        QString str_in = str_f.arg(cod,word);

        if (!query.exec(str_in))
        {
            qDebug() << "Unable to create table" << cod << "//" << word;
        }


         //qDebug() << cod;

        if( model->hasChildren(index) ) {
            SMI_to_SQL(tab_name, index);
        }
    }
}

void Redactor::Update_Hcod(QModelIndex parent, QString father_cod)
{
    for(int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);



          QString hcod_now = new_hcod(father_cod, r, true);
          model->setData(model->index(r,hcod,index.parent()), hcod_now);
          QString cod = model->data(model->index(r,hcod,index.parent())).toString();

         //qDebug() << cod;

        if( model->hasChildren(index) ) {
            Update_Hcod(index , cod);
        }
    }
}

QString Redactor::new_hcod(QString father, int row_now, bool inside)
{
    QString hcod2;
    if (inside)
    {
        hcod2 = father + "." + QString::number(row_now);
        if (father == "0")
        {
            //int temp = num_row + 1;
            hcod2 = QString::number(row_now + 1);
        }
        else if (father == "")
        {
            hcod2 = "0";
        }
    }
    else
    {
        hcod2 = father;
        int len = hcod2.size();
        if (len < 2)
        {
        hcod2 = QString::number(row_now+1);
        }
        else
        {
        hcod2.replace(len-2, 2, "");
        hcod2 = hcod2 + "." + QString::number(row_now);
        }
    }
    return hcod2;
}

void Redactor::S_ontl_name(QString name)
{
    QString all_file;
    QFile file("ontls.txt");

    if (file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        all_file = in.readAll();
        file.close();
    }

    name.replace(" ", "");
    if (file.open(QIODevice::Text | QIODevice::Append))
    {

        if (!all_file.contains(" " + name + " "))
        {
            QTextStream out(&file);
            //QDateTime now_moment = QDateTime::currentDateTime();
            //QString date_str = now_moment.toString();
            out << " " + name + " \n";
        }

        file.close();
    }
}



void Redactor::Dop_info(QString table)
{
     QSqlTableModel* model = new QSqlTableModel;
     model->setTable(table);
     model->setEditStrategy(QSqlTableModel::OnFieldChange);
     QString str_search_f = "Hcod LIKE '%1.%'";

      reset_filter(model);
     int size =model->rowCount();

     QString null_name = model->data(model->index(0, 2)).toString();
     //model->setData(model->index(0, 2), 0);

    for (int i = 0; i < size; ++i) {
        reset_filter(model);
        QString f_hcod = model->data(model->index(i, 0)).toString();

        int lev = (model->data(model->index(i, 0)).toString()).count(".") + 1;
        model->setData(model->index(i, 1), lev);
        //model->setData(model->index(i, 5), " ");

        QString f_name = model->data(model->index(i, 2)).toString();
        QString search = str_search_f.arg(f_hcod);

        int j = 0;
        if (f_hcod == "0")
        {
            search = "Hcod LIKE '_'";
            j = 1;
        }

        model->setFilter(search);
        model->select();
        int c_size = model->rowCount();


        for ( j; j < c_size; ++j)
        {

            model->setData(model->index(j, 3), f_name);
        }

        reset_filter(model);

        if (c_size == 0)
        {
            model->setData(model->index(i,4), "*");
        }
    }
        reset_filter(model);
        model->setData(model->index(0, 1), 0);
    }


void Redactor::reset_filter(QSqlTableModel* model)
{
    model->setFilter("");
    model->select();
}


Redactor::Redactor(QWidget *parent) : QWidget(parent)
{
    Reset();
}

Redactor::Redactor(QString table_name, QWidget *parent)
{
    Reset();
    ple->setText(table_name);
    SQL_To_Redact(table_name);

}
