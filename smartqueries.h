#ifndef SMARTQUERIES_H
#define SMARTQUERIES_H

#include <QDialog>
#include <QSqlQuery>
#include "database.h"

namespace Ui {
class SmartQueries;
}

class SmartQueries : public QDialog
{
    Q_OBJECT

public:
    explicit SmartQueries(QWidget *parent = nullptr);
    ~SmartQueries();
    void execut();

private:
    Ui::SmartQueries *ui;
    DataBase *db;
    std::map <int, QString> table_name;
    qint16 columnNum = 0;

private slots:
    void Next_clicked();
    void Back_clicked();

};

#endif // SMARTQUERIES_H
