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
    db = new DataBase();
    db->connectToDataBase();

    setupModel(db->table_name[counter]); // передаём в функцию имя столбца для обработки
    createUI();

    connect(ui->Next,SIGNAL(clicked()),this,SLOT(Next_clicked()));
    connect(ui->Back,SIGNAL(clicked()),this,SLOT(Back_clicked()));
    connect(ui->Insert,SIGNAL(clicked()),this,SLOT(Insert_clicked()));
    connect(ui->Delete,SIGNAL(clicked()),this,SLOT(Delete_clicked()));

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

    ui->tableView->setModel(model); // Устанавливаем модель на TableView
    ui->tableView->setColumnHidden(0, true);// Скрываем колонку с id записей
    ui->Table_name->setText(db->table_name[counter]);

    /*QModelIndex index = model->index(1,1);
    QString text = index.data().toString();*/

    qDebug()<<model->select();
    qDebug()<<model->columnCount()<< " " << model->rowCount();
    qDebug()<<index.isValid()<<text;

    for(int i = 0; i < 6; i++){
        ui->tableView->setColumnWidth(i,200);
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
    QString tmp = "", string = ui->Input->text();
    std::vector <QString> inp, name_culumn;

    for(int i = 0; i < model->columnCount(); i++){
        name_culumn.push_back("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString()+ "\"");
    }

    for(int j = 0; j < string.size(); j++){ // обработка ввода

        if(string[j] != ','){
            tmp += string[j];
        }
        else{
            inp.push_back(tmp);
            tmp = "";
        }
        if(j+1 == string.size()){
            inp.push_back(tmp);
        }
    }

    db->insert(counter, name_culumn, inp); // номер таблицы, ввод

    setupModel(db->table_name[counter]);
    createUI();
}

void MainWindow::Delete_clicked()
{
    db->delet_e(ui->Input_2->text().toInt(), counter);
    setupModel(db->table_name[counter]);
    createUI();
}
