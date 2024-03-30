#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addplayerdialog.h"

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
    ui->listWidget->addItem(name + " : " + rating);
}

