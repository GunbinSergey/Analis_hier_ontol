#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CheckConnection();

    this->setWindowTitle("СИСТЕМА ПО ИССЛЕДОВАНИЮ ОНТОЛОГИИ С ПОМОЩЬЮ СТОРОННЕЙ ИНТЕЛЕКУТАЛЬНОЙ СИСТЕМЫ");

    QWidget* wid2 = last_files();
    wid2->setWindowTitle("Wid2");
    this->setCentralWidget(wid2);

    Create_Menu();
}

bool MainWindow::CheckConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Laba");
    db.setHostName("localhost");
    db.setUserName("monika");
    db.setPassword("pasword");
    if (!db.open())
    {
        qDebug() << "Ошибка чтения";
        return false;
    }
    return true;
}

void MainWindow::Create_Menu()
{
    //this->createPopupMenu();
    QMenuBar* menuBar = this->menuBar();
    QMenu* pmenu_f = new QMenu("Файл");
    pmenu_f->addAction("Создать", this, SLOT(m_create()));
    pmenu_f->addAction("Открыть", this, SLOT(m_open()));
    //pmenu_f->addAction("Сохранить", this, SLOT(m_save()));

    QMenu* pmenu_a = new QMenu("Справка");
    pmenu_a->addAction("О программе");

    menuBar->addMenu(pmenu_f);
    menuBar->addMenu(pmenu_a);

}

void MainWindow::m_redact(QString table)
{
    Redactor* wid = new Redactor(table);
    //wid->show();
    this->setCentralWidget(wid);
}

QWidget *MainWindow::last_files()
{
    QWidget* wlast_files = new QWidget;
    QVBoxLayout* lay = new QVBoxLayout(wlast_files);
    QLabel* title = new QLabel("<font size = 30> <CENTER> СИСТЕМА ПО ИССЛЕДОВАНИЮ ОНТОЛОГИИ С ПОМОЩЬЮ СТОРОННЕЙ <br> ИНТЕЛЛЕКТУАЛЬНОЙ СИСТЕМЫ </CENTER> </font>");
    lay->addSpacing(150);
    lay->addWidget(title);
    QLabel* plastf = new QLabel("<CENTER> <H1> Список онтологий </H1> </CENTER>");
    lay->addWidget(plastf);

    //lay->setStretch(1, 5);
   // lay->setStretch(2, 600);

    QList<QString> l_fl(l_ontl());
    qlm = new QStandardItemModel(l_fl.size(),2);
    QStringList hed_list;
    hed_list << "Имя онтологии" << "      ";// << "Дата последнего обращения";
    //hed_list.sort();
    qlm->setHorizontalHeaderLabels(hed_list);


    QList<QString>::iterator it = l_fl.begin();
    for (int i = 0; it != l_fl.end() ;++i) {
         qlm->setData(qlm->index(i,0), *it);
         qlm->setData(qlm->index(i,1), "Удалить");
        it++;
    }




    QTableView* lview = new QTableView;
    lview->setModel(qlm);
    lay->addWidget(lview);
    lview->setColumnWidth(0, 150);
    lview->setColumnWidth(1, 400);
    lview->setColumnWidth(2, 150);


     //open_ont
    connect(lview, SIGNAL(clicked(QModelIndex)),SLOT(open_ont(QModelIndex)));

    QPushButton* but_create = new QPushButton("Добавить новую");
    connect(but_create, SIGNAL(clicked()), this, SLOT(m_create()));
    lay->addWidget(but_create);

    QSpacerItem* qspc = new QSpacerItem(150, 150);
    lay->addSpacerItem(qspc);

    //connect(lview, SIGNAL(clicked(QModelIndex)), this, SLOT(open_ont(ModelIndex)));
    return wlast_files;
}


QList<QString> MainWindow::l_ontl()
{
    QList<QString> list;
    QFile file("ontls.txt");

    if (file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        QTextStream in(&file);
        for (;!in.atEnd();) {
            QString temp = in.readLine();
            list.push_back(temp);
        }
    }
    return list;
}

void MainWindow::open_ontl(QString table)
{
    All_info* wid = new All_info(table);


    //QWidget* all_info = show_inform(table);
    //all_info->resize(750,300);
    this->setCentralWidget(wid);
}

void MainWindow::open_ont(QModelIndex index)
{
    qDebug() << "It's just work";
    int row = index.row();
    int col = index.column();

    QString str = qlm->data(qlm->index(row, 0)).toString();
    if (col == 0)
    {

       All_info* wid = new All_info(str);
       this->setCentralWidget(wid);
    }
    else
    {
        QString table_name = str;
        qlm->removeRow(row);
        del_ont(table_name);
    }



}
void MainWindow::m_create()
{
     Redactor* wid = new Redactor;
     //wid->show();
     this->setCentralWidget(wid);
}

void MainWindow::m_open()
{
    QWidget* wid2 = last_files();
    wid2->setWindowTitle("Wid2");
    this->setCentralWidget(wid2);
}

void MainWindow::m_save()
{

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::del_ont(QString ont_name)
{

    QFile file("ontls.txt");
    QTextStream fileData(&file);
    //fileData.setCodec()
    file.open(QIODevice::Text | QIODevice::ReadWrite); // open for read and write
    //fileData = file.readAll(); // read all the data into the byte array
    QString text = fileData.readAll(); // add to text string for easy string replace
    file.close();

    QFile file2("ontls.txt");
    QTextStream out(&file2);
    file2.open(QIODevice::Text | QIODevice::WriteOnly);
    text = text.replace(QString(ont_name + "\n"), QString("")); // replace text in string
    //file.seek(0); // go to the beginning of the file
    out << text;
    file2.close();

    QSqlQuery qur;
    ont_name = ont_name.replace(" ", "");
    qur.exec("DROP TABLE " + ont_name);
}

