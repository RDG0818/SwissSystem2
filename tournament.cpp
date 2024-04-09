#include "tournament.h"
#include "ui_tournament.h"
#include "viewtournament.h"
#include <string>

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

void tournament::sortRatings(std::vector<Person> &people) {
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
}

std::vector<std::vector<Person>> tournament::pigeonHoleSort(int currRound, std::vector<Person> &people) {

    std::vector<std::vector<Person>> scores;
    string vectorName = "";
    for (int i = 0; i < (2 * (currRound-1) ) + 1; i++) {
        std::vector<Person> scoreAmount;
        scores.push_back(scoreAmount);
    }
    for(int i = 0; i < people.size(); i++) {
        //hardest line of code to write tbh but this seperates each player into their respective score group

        scores.at((people.at(i).getScore() / 0.5)).push_back(people.at(i));
    }

    for (int i = 0; i < scores.size(); i++) {
        if (scores.at(i).size() == 0) {
            continue;
        }
        sortRatings(scores.at(i));
    }


    people.clear();
    for (int i = (scores.size()-1); i >= 0; i--) {
        people.insert(people.end(), scores.at(i).begin(), scores.at(i).end());
    }


    return scores;

}

void tournament::on_pushButton_2_clicked()
{
    viewTournament view;
    view.setPeople(people);
    view.setRows(people.size());
    std::vector<std::vector<Person>> vectoredPeople = pigeonHoleSort(currentRound + 1, people);

    for (int i = 0; i < people.size(); i++) {
        view.setCell(i, 0, people[i].getName());
        view.setCell(i, 1, std::to_string(people[i].getRating()));
        // Truncating decimal
        string temp = std::to_string(people[i].getScore());
        view.setCell(i, 2, temp.substr(0, 3));
    }
    view.exec();
}



void tournament::on_pushButton_3_clicked() {
    int loopSize = people.size() / 2;
    if (people.size() % 2 == 1) {
        loopSize++;
    }
    // Remove scores and add them to the players
    for (int i = 0; i < loopSize; i++) {
        for (int j = 0; j < people.size(); j++) {
            // Check for white player
            if (people[j].getName() == ui->tableWidget->item(i, 1)->text().toStdString()) {
                people[j].setScore(people[j].getScore() + std::stoi(ui->tableWidget->item(i, 0)->text().toStdString()));
                ui->tableWidget->setItem(i, 0, nullptr);
            }
            // Check for black player
            if (people[j].getName() == ui->tableWidget->item(i, 3)->text().toStdString()) {
                people[j].setScore(people[j].getScore() + std::stoi(ui->tableWidget->item(i, 2)->text().toStdString()));
                ui->tableWidget->setItem(i, 2, nullptr);
            }
        }
    }
    // Create the next round pairings and display

    if (currentRound < totalRound) {
    currentRound++;
    QString display = "Current Round: " + QString::number(currentRound);
    ui->label->setText(display);
    }
    else if (currentRound == totalRound){
    QString display = "Final Round";
    ui->label->setText(display);
    }
}

