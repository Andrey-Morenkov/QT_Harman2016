#include "statistics.h"
#include "ui_statistics.h"

#include "QSqlDatabase"
#include <QSqlQuery>
#include <QDebug>

Statistics::Statistics(QWidget *parent) : QWidget(parent), ui(new Ui::Statistics)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("\results.db");
    ui->setupUi(this);

    if (!db.isOpen())
    {
        db.open();
    }
    QSqlQuery *query = new QSqlQuery(QString("SELECT * FROM results"), db);

    QString text = "";


    while (query->next())
    {


        //nick = query->value(rec.indexOf("nick")).toInt();


        //text = query->value(rec.indexOf("QString")).toString();

    }
    db.close();


    delete query;
}

Statistics::~Statistics()
{
    delete ui;
}
