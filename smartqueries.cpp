#include "smartqueries.h"
#include "ui_smartqueries.h"

SmartQueries::SmartQueries(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SmartQueries)
{
    ui->setupUi(this);

    DataBase *db = new DataBase; // хуйня сделать singletone
    db->connectToDataBase();

    QSqlQuery query;
    QString quer_y;
    quer_y = "INSERT INTO \"Client\" (\"ID\",\"Phone_number\", \"Address\") VALUES (6,999, 'Name')";
    query.exec(quer_y);

}

SmartQueries::~SmartQueries()
{
    delete ui;
}
