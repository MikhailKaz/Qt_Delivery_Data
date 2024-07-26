#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    //db = new DataBase();

    db = DataBase::get_db();

    db->connectToDataBase();

    setupModel(db->table_name[counter]); // передаём в функцию имя столбца для обработки
    createUI();

    connect(ui->Next,SIGNAL(clicked()),this,SLOT(Next_clicked()));
    connect(ui->Back,SIGNAL(clicked()),this,SLOT(Back_clicked()));
    connect(ui->Insert,SIGNAL(clicked()),this,SLOT(Insert_clicked()));
    connect(ui->Delete,SIGNAL(clicked()),this,SLOT(Delete_clicked()));

    ui->lineEdit->setAlignment(Qt::AlignCenter);

}

/* Метод для инициализации модели представления данных
 * */
void MainWindow::setupModel(QString tableName)
{

    model = new QSqlTableModel(this);
    model->setTable(tableName); // устанавливаем таблицу db с которой работает модель

    model->setSort(0,Qt::AscendingOrder); // Устанавливаем сортировку по возрастанию данных по нулевой колонке

}

void MainWindow::createUI()
{
    modelInput = new QStandardItemModel(1, model->columnCount()-1);

    ui->tableView->setModel(model); // Устанавливаем модель на TableView
    ui->tableView_2->setModel(modelInput);

    ui->tableView->setColumnHidden(0, true);// Скрываем колонку с id записей
    ui->Table_name->setText(db->table_name[counter]);

    for(int i = 1; i < model->columnCount(); i++){ // ввод названия в 0 строку
        modelInput->setHorizontalHeaderItem(i-1, new QStandardItem(model->headerData(i,Qt::Horizontal).toString()));
    }

    for(int i = 0; i < 6; i++){
        ui->tableView->setColumnWidth(i,200);
        ui->tableView_2->setColumnWidth(i,200);
    }

    model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::Next_clicked()
{
    if (counter < 5){
        counter++;
    }

    setupModel(db->table_name[counter]);
    createUI();
}

void MainWindow::Back_clicked()
{
    if (counter > 0){
        counter--;
    }
    setupModel(db->table_name[counter]);
    createUI();
}

void MainWindow::Insert_clicked()
{
    // надо передать 2 вектора 1) с именами колонок 2) с параметрами
    QVector <QString> nameColumn, argInsert;

    for(int i = 0; i < model->columnCount(); i++){ // i = 1 потому что 1 колонка ID
        nameColumn.push_back(model->headerData(i,Qt::Horizontal).toString());
        if(i == 0){
            argInsert.push_back(QString::number(model->rowCount()+1)); // добавляем номер строки для INSERT
        }
        else{
            argInsert.push_back(modelInput->data(modelInput->index(0,i-1),Qt::DisplayRole).toString()); // добавляем входные данные с таблицы
        }
    }

    db->insert(counter, nameColumn, argInsert);
    setupModel(db->table_name[counter]);
    createUI();
}

void MainWindow::Delete_clicked()
{
    db->delet_e(ui->lineEdit->text().toInt(), db->table_name[counter]); // передаём номер номер row и имя таблицы для удаления
    setupModel(db->table_name[counter]);
    createUI();
}

void MainWindow::on_pushButton_clicked()
{
    windSmartQuer.setModal(true);
    windSmartQuer.execut();
    windSmartQuer.show();
}

