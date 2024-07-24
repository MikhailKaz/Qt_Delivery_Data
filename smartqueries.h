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

private:
    Ui::SmartQueries *ui;
};

#endif // SMARTQUERIES_H
