#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addplayerdialog.h"
#include "tournament.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    addPlayerDialog window;
    window.exec();
    QString name = window.getName();
    QString rating = window.getRating();
    ui->listWidget->addItem(name);
    ui->listWidget_2->addItem(rating);
}


void MainWindow::on_pushButton_2_clicked()
{
    tournament tournament;
    tournament.setTableRow(((ui->listWidget->count()) / 2) + (ui->listWidget->count() % 2));
    std::vector<QString> info;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        info.push_back(ui->listWidget->item(i)->text());
    }
    tournament.setTableInfo(info);
    tournament.exec();
}

