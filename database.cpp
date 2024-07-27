#include "database.h"

// Методы закрытия базы данных

void DataBase::closeDataBase()
{
    db.close();
}

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    table_name[0] = "Client"; // запись названия колонок
    table_name[1] = "Courier";
    table_name[2] = "Delivery_history";
    table_name[3] = "Order";
    table_name[4] = "Order_list";
    table_name[5] = "Restaurants"; 

}

DataBase::~DataBase()
{

}

// Методы для подключения к базе данных

void DataBase::connectToDataBase() // public
{
    if(openDataBase()){
        qDebug() << "Success connection with data base";
    }
    else {
        qDebug() << "Failure connection with data base";
    }
}

// Метод для открытия базы данных
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Delivery_data");
    db.setUserName("postgres");
    db.setPassword("");
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DataBase::insert(int counter, QVector <QString> name_culumn, QVector <QString> inp) { // counter - номер текущей таблицы

    QString quer_y;
    QSqlQuery query;
    quer_y = "INSERT INTO \"" + table_name[counter] + "\" (";

    for (int i = 0; i < name_culumn.size(); i++){

        if(i != 0){
            quer_y += ", ";
        }

        quer_y +=  "\"" + name_culumn[i] + "\"";

    }
    quer_y += ") VALUES (";

    for(int i = 0; i < inp.size(); i++){

        if(i != 0){
            quer_y += ", ";
        }
        quer_y += "?";
    }
    quer_y += ")";

    query.prepare(quer_y);

    for(int i = 0; i < inp.size(); i++){
        query.addBindValue(inp[i]);
    }

    query.exec();

}

void DataBase::delet_e(int num, QString nameColumn){

    QSqlQuery query;
    QString quer_y;
    quer_y = "DELETE FROM \"" + nameColumn + "\"";
    quer_y += " WHERE \"ID\" = " + QString::number(num);
    query.exec(quer_y);

}

void DataBase::smartOne(){

    QSqlQuery query;
    QString quer_y = "SELECT COUNT(*) FROM \"" + table_name[2] + "\"";
    qDebug() << quer_y;
    qDebug() << query.exec(quer_y);
    query.next();
    qDebug() << query.value(0).toInt();

}

// quer_y = "...";
// query.exec(quer_y);
// query.exec("DELETE FROM \"Client\" WHERE \"ID\" = 6");
// query.exec("INSERT INTO \"Client\" (\"ID\",\"Phone_number\", \"Address\") VALUES (8,999, 'Name')");
