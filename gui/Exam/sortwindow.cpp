#include "sortwindow.h"
#include "ui_sortwindow.h"

SortWindow::SortWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SortWindow)
{
    {
        ui->setupUi(this);
        ui->insertElement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        fillTable(0);
        this->elementType = elementServer;
    }
}



    void SortWindow::fillTable(int index){
        int n;
        std::vector <QString> names;
        if(index == 0){
            names = {
                QString::fromStdString("Сервер"),
                QString::fromStdString("Датацентр"),
                QString::fromStdString("Rack"),
                QString::fromStdString("Компанія")
            };
        }
        else{
            names = {
                QString::fromStdString("Рік"),
                QString::fromStdString("Місяць"),
                QString::fromStdString("День"),
                QString::fromStdString("Година"),
                QString::fromStdString("Хвилина"),
                QString::fromStdString("Секунда")
            };
        }
        n = names.size();
        int i = ui->insertElement->rowCount();
        while(i < n){
            ui->insertElement->insertRow(i);
            i++;
        }
        while(i >= n){
            ui->insertElement->removeRow(i);
            i--;
        }
        QTableWidgetItem* it;
        for(int j = 0; j < n; j++){
            it = new QTableWidgetItem(names[j]);
            it->setFlags(Qt::ItemIsEnabled);
            ui->insertElement->setItem(j,0,it);
        }
    }

SortWindow::~SortWindow()
{
    delete ui;
}

void SortWindow::on_listButton_clicked()
{

}

void SortWindow::on_tableButton_clicked()
{

}

QString getValue(QTableWidgetItem* it){
    if(!it)
        return "";
    return it->text();
}

void SortWindow::fillElement(Server& s){
    auto table = ui->insertElement;
    ip::address aps(1,2,3,4);
    s.IP = aps;
    s.data_center = getValue(table->item(1,1)).toStdString();
    s.rack = getValue(table->item(2,1)).toStdString();
    s.company = getValue(table->item(3,1)).toStdString();
}

void SortWindow::fillElement(date_time::DateTime& dt){
    auto table = ui->insertElement;
    int names[6];
    for(int i  =0; i < 6; i++){
        names[i] = getValue(table->item(i,1)).toInt();
        //check correct
    }
    date_time::DateTime newdt(names[0]-1, date_time::Month(names[1]-1), names[2]-1, names[3]-1, names[4]-1, names[5]-1);
    dt = newdt;
}

void SortWindow::on_insertButton_clicked()
{
    if(elementType == elementServer){
        auto element = Server();
        fillElement(element);
        insertServerInTable(element);
    } else {
        auto element = date_time::DateTime();
        fillElement(element);
        insertDateTimeInTable(element);
    }
}

void SortWindow::on_backButton_clicked()
{
    this->close();
    emit mainWindowShow();
}

void SortWindow::on_backButton_2_clicked()
{
    this->close();
    emit mainWindowShow();
}


void SortWindow::insertServerInTable(Server s){
    int n = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(n);
    QString id = QString::fromStdString(std::to_string(n + 1));
    QTableWidgetItem* it = new QTableWidgetItem(id);
    ui->tableWidget->setItem(n,0, it);
    it = new QTableWidgetItem(QString::fromStdString(s.IP.toString()));
    ui->tableWidget->setItem(n,1, it);
    it = new QTableWidgetItem(QString::fromStdString(s.data_center));
    ui->tableWidget->setItem(n,2, it);
    it = new QTableWidgetItem(QString::fromStdString(s.rack));
    ui->tableWidget->setItem(n,3, it);
    it = new QTableWidgetItem(QString::fromStdString(s.company));
    ui->tableWidget->setItem(n,4, it);
}

void SortWindow::insertDateTimeInTable(date_time::DateTime dt){
    int n = ui->tableWidget->rowCount();
    int m = ui->tableWidget->columnCount();
    std::vector<int> date_time_vector = dt.to_vector();
    ui->tableWidget->insertRow(n);
    QTableWidgetItem* it = new QTableWidgetItem(n);
    ui->tableWidget->setItem(n,0, it);
    for(int j = 0; j < m-1; j++){
        it = new QTableWidgetItem(date_time_vector[j]);
        ui->tableWidget->setItem(n, j+1, it);
    }
}

void SortWindow::on_ipRadio_clicked()
{

}

void SortWindow::on_DataCenterRadio_clicked()
{

}

void SortWindow::on_RackRadio_clicked()
{

}

void SortWindow::on_CompanyRadio_clicked()
{

}

void SortWindow::on_contentBox_activated(int index)
{

}

void SortWindow::on_contentBox_activated(const QString &arg1)
{
    ui->tableWidget->clear();
    QTableWidget* table = ui->tableWidget;
    int n;



    if(arg1 == "Сервери"){
       // ui->sortingParamether->clear();
        ui->sortingParamether->setItemText(0,"Hello");

        elementType = elementServer;
        n = 5;
   }else {
        n = 7;
        ui->sortingParamether->setItemText(0,"DateTime");
        elementType = elementDateTime;
    }
    table->setColumnCount(n);

    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //else{

//    }
    std::vector<QString> serverHeaders = {"id", "IP", "Data center", "Rack", "Company"};
    std::vector<QString> dateTimeHeaders = {"id", "year", "month", "day", "hour", "minute", "second"};
    if(arg1 == "Сервери"){
        for (int col = 0; col < serverHeaders.size(); ++col) {
                auto hitem = new QTableWidgetItem;
                hitem->setText(serverHeaders[col]);
                table->setHorizontalHeaderItem(col, hitem);
                table->model()->setHeaderData(col, Qt::Horizontal, serverHeaders[col], Qt::DisplayRole);
        }
        ui->sortingParamether->setItemText(0,"Серверок");
    }else if(arg1 == "Дата і час"){
        for (int col = 0; col < dateTimeHeaders.size(); ++col) {
                auto hitem = new QTableWidgetItem;
                hitem->setText(dateTimeHeaders[col]);
                table->setHorizontalHeaderItem(col, hitem);
                table->model()->setHeaderData(col, Qt::Horizontal, dateTimeHeaders[col], Qt::DisplayRole);
        }
        ui->sortingParamether->setItemText(0,"DateTime");
    }
        else{
            std::cout << arg1.toStdString();
        }
}
