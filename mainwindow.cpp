#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addplayerdialog.h"
#include "settings.h"
#include "tournament.h"
#include "person.h"

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
    if (window.accept){
        QString name = window.getName();
        QString rating = window.getRating();
        ui->listWidget->addItem(name);
        ui->listWidget_2->addItem(rating);
        string stdname = name.toStdString();
        int stdrating = rating.toInt();
        Person person(stdname, stdrating);
        person.setMatchHistory(rounds.toInt());
        people.push_back(person);
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    tournament tournament;
    tournament.setPeople(people);
    if(people.size() % 2 == 0) {
        tournament.setRows(people.size() / 2);
    }
    else {
        Person byePerson = Person("BYE", 0);
        byePerson.setMatchHistory(rounds.toInt());
        people.push_back(byePerson);
        tournament.setRows(people.size() / 2);
    }
    // Sorting Algo
    for(int i = 0; i < people.size() - 1; i++)
    {
        for(int j = 0; j < people.size() - i - 1; j++)
        {
            if(people.at(j).getRating() < people.at(j+1).getRating())
            {
                Person temp = people[j];

                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }

    // Make first round pairings
    for (int i = 0; i < people.size(); i++) {
        tournament.setCell(i, 1, people[i].getName());
        tournament.setCell(i, 3, people[people.size() - 1 - i].getName());
    }

    tournament.setTotalRound(rounds.toInt());
    //Tournament info
    tournament.setTournamentInfo(tournamentName.toStdString(), organizer.toStdString(), timeControl.toStdString(), location.toStdString(), rounds.toStdString(), date.toStdString());
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

