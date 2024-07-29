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

QSqlQueryModel* DataBase::smartOne(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ord.\"Order_time\", his.\"Delivery_time\", his.\"Order_status\", (his.\"Delivery_time\" - ord.\"Order_time\") as \"Spent_time\" "
"FROM \"Order\" ord "
"JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
"WHERE his.\"Order_status\" = 'Доставлен'");

    return model;
}

QSqlQueryModel* DataBase::smartSecond(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT cou.\"Transport\", (his.\"Delivery_time\" - ord.\"Order_time\") as \"Spent_time\" "
    "FROM \"Order\" ord "
    "JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
    "JOIN \"Courier\" cou ON cou.\"ID\" = ord.\"id_courier\"");

    return model;
}

QSqlQueryModel* DataBase::smartThird(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ord.\"Price\", res.\"Name\", com.\"Number_dish\", com.\"Quantity\" "
    "FROM \"Order\" ord "
    "JOIN \"Restaurants\" res ON res.\"ID\" = ord.\"id_restaurants\" "
    "JOIN \"Order_list\" com ON com.\"ID\" = ord.\"id_order_list\" "
    "WHERE ord.\"Price\" > 1000");

    return model;
}

QSqlQueryModel* DataBase::smartFourth(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT his.\"Type_payment\", SUM (ord.\"Price\") AS total_summ "
    "FROM \"Order\" ord "
    "JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
    "GROUP BY his.\"Type_payment\"");

    return model;
}

QSqlQueryModel* DataBase::smartFifth(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ord.\"Order_date\", AVG (his.\"Delivery_time\" - ord.\"Order_time\") AS average_val "
    "FROM \"Order\" ord "
    "JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
    "GROUP BY ord.\"Order_date\"");

    return model;
}

QSqlQueryModel* DataBase::smartSixth(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT (his.\"Delivery_time\" - ord.\"Order_time\") AS \"Spent_time\",ord.\"Price\",cli.\"Address\" "
    "FROM \"Order\" ord "
    "JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
    "JOIN \"Client\" cli ON cli.\"ID\" = ord.\"id_client\" "
    "ORDER BY his.\"Delivery_time\" - ord.\"Order_time\" DESC");

    return model;
}

QSqlQueryModel* DataBase::smartSeventh(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ord.\"Order_date\", ord.\"Price\", his.\"Type_payment\", his.\"Order_status\", (his.\"Delivery_time\" - ord.\"Order_time\") AS \"Spent_time\" "
    "FROM \"Order\" ord "
    "JOIN \"Delivery_history\" his ON ord.\"ID\" = his.\"id_order\" "
    "ORDER BY ord.\"Price\" DESC");

    return model;
}

QSqlQueryModel* DataBase::smartEighth(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT ord.\"Order_date\", cli.\"Address\", cli.\"Phone_number\", cou.\"Full_name\", cou.\"Phone_number\", res.\"Name\", res.\"Address\",res.\"Phone_number\" "
    "FROM \"Order\" ord "
    "JOIN \"Courier\" cou ON cou.\"ID\" = ord.\"id_courier\" "
    "JOIN \"Client\" cli ON cli.\"ID\" = ord.\"id_client\" "
    "JOIN \"Restaurants\" res ON res.\"ID\" = ord.\"id_restaurants\"");

    return model;
}
// quer_y = "...";
// query.exec(quer_y);
// query.exec("DELETE FROM \"Client\" WHERE \"ID\" = 6");
// query.exec("INSERT INTO \"Client\" (\"ID\",\"Phone_number\", \"Address\") VALUES (8,999, 'Name')");
