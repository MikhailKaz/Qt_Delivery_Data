#include "smartqueries.h"
#include "ui_smartqueries.h"

SmartQueries::SmartQueries(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SmartQueries)
{
    ui->setupUi(this);

    db = DataBase::get_db();

    ui->label->setAlignment(Qt::AlignCenter);

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Back_clicked()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Next_clicked()));

    table_name[0] = "Table spent time";
    table_name[1] = "Speed transport";
    table_name[2] = "More >1000";
    table_name[3] = "Cash / Non-cash";
    table_name[4] = "Average time";
    table_name[5] = "Time to addres and price";
    table_name[6] = "Statistics";
    table_name[7] = "General information";

}

SmartQueries::~SmartQueries()
{
    delete ui;
}

void SmartQueries::execut(){

    QSqlQueryModel *model;

    switch(columnNum){
    case 0:
        ui->label->setText("Table spent time");
        model = db->smartOne();
        break;
    case 1:
        ui->label->setText("Speed transport");
        model = db->smartSecond();
        break;
    case 2:
        ui->label->setText("More >1000");
        model = db->smartThird();
        break;
    case 3:
        ui->label->setText("Cash / Non-cash");
        model = db->smartFourth();
        break;
    case 4:
        ui->label->setText("Average time");
        model = db->smartFifth();
        break;
    case 5:
        ui->label->setText("Time to addres and price");
        model = db->smartSixth();
        break;
    case 6:
        ui->label->setText("Statistics");
        model = db->smartSeventh();
        break;
    case 7:
        ui->label->setText("General information");
        model = db->smartEighth();
        break;
    }

    ui->tableView->setModel(model);
    for(int i = 0; i < model->columnCount(); i++){
        ui->tableView->setColumnWidth(i,200);
    }
}

void SmartQueries::Back_clicked(){
    if(columnNum > 0){
        columnNum--;
        execut();
    }
}

void SmartQueries::Next_clicked(){
    if(columnNum < 7){
        columnNum++;
        execut();
    }
}

