#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QString>
#include <vector>

/* Директивы имен таблицы, полей таблицы и базы данных */

#define TABLE                   "Client"
#define TABLE_ID                "ID"
#define TABLE_NUMBER            "Phone_number"
#define TABLE_ADDRESS           "Address"

#define TABLE_DATE              "Date"
#define TABLE_TIME              "Time"
#define TABLE_MESSAGE           "Message"
#define TABLE_RANDOM            "Random"

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    ~DataBase();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    void insert(int counter, std::vector <QString> name_culumn, std::vector <QString> inp);
    void delet_e(int num, int counter);

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();

public:

    std::map <int, QString> table_name; // Названия вызываемых таблиц, мб их можно как-то считать с db но мне лень разбираться:/

};

#endif // DATABASE_H
