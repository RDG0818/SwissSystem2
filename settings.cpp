#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::settings)
{
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

QString settings::getTournamentName() const {
    return ui->lineEdit->text();
};
QString settings::getOrganizer() const {
    return ui->lineEdit_2->text();
};
QString settings::getTimeControl() const {
    return ui->lineEdit_3->text();
};
QString settings::getLocation() const {
    return ui->lineEdit_4->text();
};
QString settings::getRounds() const {
    return ui->lineEdit_5->text();
};
QString settings::getDate() const {
    return ui->lineEdit_6->text();
};
