#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QString>
#include <QStandardItemModel>
#include <QSqlTableModel>

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

    QSqlQueryModel *smartOne();
    QSqlQueryModel *smartSecond();
    QSqlQueryModel *smartThird();
    QSqlQueryModel *smartFourth();
    QSqlQueryModel *smartFifth();
    QSqlQueryModel *smartSixth();
    QSqlQueryModel *smartSeventh();
    QSqlQueryModel *smartEighth();

private:
    DataBase(QObject *parent = 0); // singleton
    ~DataBase();
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase db;

private:
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();

public:

    std::map <int, QString> table_name; // Названия вызваемых таблиц

};

#endif // DATABASE_H
