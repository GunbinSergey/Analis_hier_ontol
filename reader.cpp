#include "reader.h"



Reader::Reader(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* lay_main =new QVBoxLayout(this);
    QGridLayout* lay = new QGridLayout;

    QString info = "<font size= '5'> Внимание для считывания онтологии с .txt файла необходима следующее оформление файла: <br>"
                   "'0[Разделитель]Главный термин<br>"
                   " 1[Разделитель]Термин<br>"
                   " 1.1[Разделитель]Термин<br>"
                   " ...<br>"
                   " 2[Разделитель]Термин' </font>";

    QLabel* lab_info = new QLabel(info);
    lay_main->addWidget(lab_info);
    lay_main->addLayout(lay);



    separ = new QLineEdit;
    QLabel* lab_sepr = new QLabel("Укажите разделитель (без [])");

    lay->addWidget(lab_sepr,1,0);
    lay->addWidget(separ, 1,1);

    file_path = new QLineEdit;
    file_path->setReadOnly(true);

    QPushButton* find_path = new QPushButton("Указать путь");

    lay->addWidget(file_path, 2, 0);
    lay->addWidget(find_path, 2, 1);

    QPushButton* open_file = new QPushButton("Открыть файл");
    lay_main->addWidget(open_file);

    model = new QStandardItemModel(0,2);

    QTableView* view_mod = new QTableView();
    QStringList headers;
    headers << "Код" << "Термин";
    view_mod->setColumnWidth(0, 200);
    view_mod->setColumnWidth(1, 600);

    view_mod->setModel(model);

    lay_main->addWidget(view_mod);

    lay_main->setStretch(0,40);
    lay_main->setStretch(1,10);
    lay_main->setStretch(2,50);

    connect(find_path, SIGNAL(clicked()), this, SLOT(chose_file()));

    connect(open_file, SIGNAL(clicked()), this, SLOT(open_file()));

}

void Reader::chose_file()
{
    QFileDialog* fd = new QFileDialog();
    fd->setNameFilter("*.txt");
     QString fileName = fd->getOpenFileName();
     file_path->setText(fileName);
}

void Reader::open_file()
{
    QString path = file_path->text();
    QList<QString>* data = data_file(path);
    QList<QString>::iterator it = data->begin();
    int size = data->length();

    model->insertRows(0, size);
    QString split_str = separ->text();

    for (int i = 0; it != data->end(); ++i)
    {
        QList<QString> temp = (it->split(split_str));

        try {
            model->setData(model->index(i,0), temp[0]);
            model->setData(model->index(i,1), temp[1]);
        } catch (...) {

        }

        ++it;
    }
    model->sort(0);
}

QList<QString>* Reader::data_file(QString path)
{
    QList<QString>* list = new QList<QString>;
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
      QTextStream out(&file);
      out.setCodec("UTF-8");
      while (!out.atEnd())
      {
        QString temp = out.readLine();
        temp = temp.replace("—", "-");
        list->push_back(temp);
      }
    }
    else
    {

    }
    return list;
}
