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

class DataBase : public QObject
{
    Q_OBJECT
public:

    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    static DataBase *get_db(){ // singleton
        static DataBase *db;
        if(!db){
            db = new DataBase();
        }
        return db;
    }

    void connectToDataBase();
    void insert(int counter, QVector <QString> name_culumn, QVector <QString> inp);
    void delet_e(int num, QString nameColumn);

private:
    DataBase(QObject *parent = 0); // singleton
    ~DataBase();
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

    std::map <int, QString> table_name; // Названия выываемых таблиц (vector)

};

#endif // DATABASE_H
