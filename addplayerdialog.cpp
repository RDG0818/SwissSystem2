#include "addplayerdialog.h"
#include "ui_addplayerdialog.h"

addPlayerDialog::addPlayerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addPlayerDialog)
{
    ui->setupUi(this);
}

addPlayerDialog::~addPlayerDialog()
{
    delete ui;
}

QString addPlayerDialog::getName() const {
    QString name = ui->lineEdit->text();
    return name;
}

QString addPlayerDialog::getRating() const {
    QString rating = ui->lineEdit_2->text();
    return rating;
}

void addPlayerDialog::on_buttonBox_accepted()
{
    accept = true;
}


void addPlayerDialog::on_buttonBox_rejected()
{
    accept = false;
}

