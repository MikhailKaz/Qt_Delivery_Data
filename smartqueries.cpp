#include "smartqueries.h"
#include "ui_smartqueries.h"

SmartQueries::SmartQueries(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SmartQueries)
{
    ui->setupUi(this);

    db = DataBase::get_db();

}

SmartQueries::~SmartQueries()
{
    delete ui;
}

void SmartQueries::execut(){

    db->smartOne();
    /*QSqlQuery query;
    QString quer_y;
    quer_y = "INSERT INTO \"Client\" (\"ID\",\"Phone_number\", \"Address\") VALUES (6,999, 'Name')";
    query.exec(quer_y);*/
}
