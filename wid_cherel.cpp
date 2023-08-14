#include "wid_cherel.h"


Wid_CheRel::Wid_CheRel(Repriz *rep, QWidget *parent)
{
    saver = rep;

    QVBoxLayout *layV = new QVBoxLayout(this);
    QHBoxLayout *layH = new QHBoxLayout();
    QHBoxLayout *layH0 = new QHBoxLayout();


    QLabel* title = new QLabel("<font size = 12><CENTER>Поиск когнетивных маршрутов </CENTER> </font>");
    layV->addWidget(title);

    layV->addLayout(layH0);
    layV->addLayout(layH);

    hcod_1 = new QLineEdit;
    hcod_1->setText("Код");
    hcod_1->setReadOnly(true);

    hcod_2 = new QLineEdit;
    hcod_2->setText("Код");
    hcod_2->setReadOnly(true);

    layH0->addWidget(hcod_1);
    layH0->addSpacing(50);
    layH0->addWidget(hcod_2);

    term_1 = new QLineEdit;
    term_1->setText("Причина");
    term_1->setReadOnly(true);

    term_2 = new QLineEdit;
    term_2->setText("Следствие");
    term_2->setReadOnly(true);

    layH->addWidget(term_1);
    layH->addSpacing(50);
    layH->addWidget(term_2);
    QPushButton* but = new QPushButton("Проверить связь");
    layV->addWidget(but);
    connect(but, SIGNAL(clicked()), this, SLOT(Check_real()));
}

QString Wid_CheRel::ChatGpt_about_real(QString hcod1, QString hcod2)
{
    QString descr = "";
    if (hcod1 == "3.4.1" && hcod2 == "3.2")
    {
        descr = "<font size = 4>Да, Между оперативностью выявления инфекции области хирургического вмешательства и качеством жизни пациента существует причинно-следственная связь. Оперативность выявления инфекции и своевременное назначение лечения предотвращает ее дальнейшее распространение на соседние ткани и органы, а также сокращает период лечения и реабилитации, благодаря чему пациент менее подвержен различным осложнениям."
                "<br>Подобно тому, медленное выявление инфекции и несвоевременное назначение лечения, с другой стороны, также может привести к различным осложнениям, ухудшению состояния пациента и увеличению периода восстановления, что, в свою очередь, может негативно сказаться на качестве его жизни."
                "<br>Поэтому причинно-следственная связь между оперативностью выявления инфекции после хирургического вмешательства и качеством жизни пациента предполагает, что чем раньше инфекция будет выявлена и лечена, тем меньше вероятность осложнений, быстрее пациент восстановится, и его качество жизни будет выше."
                "</font>";

    }
    descr += "<br ><H1>Вы подтверждаете связь?</H1>";
    return descr;
}

void Wid_CheRel::Check_real()
{
    //Вывод результата проверки
    QString hcod1 = hcod_1->text();
    QString hcod2 = hcod_2->text();

    QString keyword1 = term_1->text();
    QString keyword2 = term_2->text();

    QString title = "Информации о связях между: " + keyword1 + " и " + keyword2;
    QString descr = check_real_gpt(keyword1, keyword2);
    QMessageBox mes;
    mes.setWindowTitle("Мнение ChatGPT");
    mes.setText(title);
    mes.setInformativeText(descr);
    mes.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int res = mes.exec();
    if (res == QMessageBox::Yes)
    {
        QList<QString> temp = {keyword1, keyword2};
        saver->rep_AddRow(temp);
    }

}

QString Wid_CheRel::check_real_gpt(QString term1, QString term2)
{
    QProcess *proc = new QProcess;
    QStringList params;

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    params << "-ts";
    params << term1;
    params << term2;
    proc->start("GPT_help.exe",params);
    qDebug() << proc->state();
    proc->waitForFinished();
    QByteArray result = proc->readAllStandardOutput();
    QString answer = codec->toUnicode(result);
    qDebug() << proc->readAllStandardError();
    qDebug() << answer;
    return answer;
}

QString Wid_CheRel::about_term(QString term)
{
    QProcess *proc = new QProcess;
    QStringList params;

    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");

    params << "-ts";
    params << term;
    proc->start("GPT_help.exe",params);
    qDebug() << proc->state();
    proc->waitForFinished();
    QByteArray result = proc->readAllStandardOutput();
    QString answer = codec->toUnicode(result);
    qDebug() << proc->readAllStandardError();
    qDebug() << answer;
    return answer;
}
