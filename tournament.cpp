#include "tournament.h"
#include "ui_tournament.h"

tournament::tournament(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tournament)
{
    ui->setupUi(this);
}

tournament::~tournament()
{
    delete ui;
}

void tournament::setTableInfo(const std::vector<QString> &info) {
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(info[2 * i]);
        QTableWidgetItem *item2 = new QTableWidgetItem(info[2 * i + 1]);
        ui->tableWidget->setItem(i, 2, item);
        ui->tableWidget->setItem(i, 5, item2);
    }
}

void tournament::setTableRow(int num) {
    ui->tableWidget->setRowCount(num);
}
