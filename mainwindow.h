#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <map>

//
#include <QTableView>
#include <QStandardItemModel>
//

/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include "database.h"

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

private:
    Ui::MainWindow  *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    DataBase        *db;
    QSqlTableModel  *model;
    QStandardItemModel *modelInput;

private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(QString tableName);
    void createUI();

private: // ну а дальше бага нет, есть только мой гавнокод
    int counter = 0; // счётчик для выбора таблицы

};
#endif // MAINWINDOW_H
