#include "viewtournament.h"
#include "ui_viewtournament.h"
#include <iostream>
#include <fstream>
using namespace std;

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

void viewTournament::on_pushButton_clicked()
{
    ofstream csv(tournamentName + ".csv");
}

