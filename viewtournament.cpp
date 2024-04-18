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

void viewTournament::on_pushButton_clicked() {
    ofstream csv(tournamentName + ".csv");
    if (!csv.is_open()) {
        cout << "Could not open file" << endl;
        return;
    }
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            csv << ui->tableWidget->item(i, j)->text().toStdString() << ",";
        }
        csv << endl;
    }
    csv.close();
}

