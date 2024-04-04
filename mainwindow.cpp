#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addplayerdialog.h"
#include "settings.h"
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
    std::vector<QString> nameVector;
    for (int i = 0; i < ui->listWidget->count(); i++) {
        nameVector.push_back(ui->listWidget->item(i)->text());
    }
    std::vector<int> rating;
    for (int i = 0; i < ui->listWidget_2->count(); i++) {
        rating.push_back(ui->listWidget_2->item(i)->text().toInt());
    }
    // Sorting Algorithm for the Players
    std::vector<QString> sortedNameVector;
    std::vector<int> sortedRating;
    int iterations = rating.size();
    for (int j = 0; j < iterations; j++) {
        int highest = rating[0];
        int index = 0;
        for (int i = 0; i < rating.size(); i++) {
            if (rating[i] > highest) {
                highest = rating[i];
                index = i;
            }
        }
        sortedRating.push_back(highest);
        rating.erase(rating.begin() + index);
        sortedNameVector.push_back(nameVector[index]);
        nameVector.erase(nameVector.begin() + index);
    }
    tournament.setTableInfo(sortedNameVector);
    tournament.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    settings setting;
    setting.exec();
    tournamentName = setting.getTournamentName();
    organizer = setting.getOrganizer();
    timeControl = setting.getTimeControl();
    location = setting.getLocation();
    rounds = setting.getRounds();
    date = setting.getDate();
}

