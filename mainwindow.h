#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>

#include "database.h"
#include "smartqueries.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Switch();

private slots:

    void Next_clicked();

    void Back_clicked();

    void Insert_clicked();

    void Delete_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow  *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    QSqlTableModel  *model;
    QStandardItemModel *modelInput;
    SmartQueries windSmartQuer;
    DataBase *db;

private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(QString tableName);
    void createUI();

private:
    int counter = 0; // счётчик для выбора таблицы

};
#endif // MAINWINDOW_H
