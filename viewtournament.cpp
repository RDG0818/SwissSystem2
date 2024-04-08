#include "viewtournament.h"
#include "ui_viewtournament.h"

viewTournament::viewTournament(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::viewTournament)
{
    ui->setupUi(this);
}

viewTournament::~viewTournament()
{
    delete ui;
}
