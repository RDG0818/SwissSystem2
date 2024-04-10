#include "tournament.h"
#include "ui_tournament.h"
#include "viewtournament.h"
#include <string>
using namespace std;

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

// ------------------------------------Kevin's stuff--------------------------------------

void tournament::sortRatings(vector<Person> &people) {
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

vector<vector<Person>> tournament::pigeonHoleSort(int currRound, vector<Person> &people) {

    vector<vector<Person>> scores;
    string vectorName = "";
    for (int i = 0; i < (2 * (currRound-1) ) + 1; i++) {
        vector<Person> scoreAmount;
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

void tournament::giveBye(Person &player, int currRound){
    string result = "BYE";
    player.updateMatchHistory(currRound, result,0,"");
}


int tournament::findRank(vector<Person> people, Person player){
    int rank = 0;
    for (int i = 0; i < people.size(); i++) {
        if (player.getName() == people.at(i).getName()) {
            rank = i;
            break;
        }
    }
    return rank + 1 ;
}


bool tournament::conditions(vector<Person> &pair, int currRound, vector<Person> people) {
    // Same color poggers just swap the players in the pair list

    return false;
}






vector<vector<Person>> tournament::createPairings(vector<Person> &people, int currRound) {
    //sorting algorithm for the people vector
    vector<Person> tempPeople;
    vector<vector<Person>> scores;
    vector<vector<Person>> tempScores;
    vector<vector<Person>> tempTempScores;
    vector<vector<Person>> matches;

    tempPeople = people;
    scores = pigeonHoleSort(currRound + 1, people);
    reverse(scores.begin(),scores.end());
    tempScores = scores;

    //tempScores.at(tempScores.size()-1).size() != 0

    int temps = people.size()/2;
    while(matches.size() != temps) {
        // iterates through the scores with their respective score starting from the top
        for (int i = 0; i < tempScores.size(); i++) {
            //If the score is empty go to the next list of scores
            if (tempScores.at(i).size() == 0) {
                continue;
            }

            int repeats = tempScores.at(i).size()/2;
            if (tempScores.at(i).size() % 2 == 1) {
                repeats++;
            }
            //iterates throught the players within the list and makes a pair for each person
            for(int j = 0; j < repeats; j++) {
                int firstShift = 0;
                vector<Person> pairs;
                Person player;
                int index = 0;

                if ((tempScores.at(i).size() == 1) || ((i == tempScores.size()-1) && (tempScores.at(i).size() % 2 == 1))) {

                    if (i == tempScores.size()-1) {
                        player = scores.at(scores.size()-1).at(0);
                        for (int k = 0; k < people.size(); k++) {
                            if (player.getName() == people.at(k).getName()) {
                                index = k;
                            }
                        }
                        giveBye(people.at(index), currRound);
                        tempScores.at(i).erase(tempScores.at(i).begin());
                        repeats--;
                        continue;
                    }
                    else {
                        player = tempScores.at(i).at(0);

                        tempScores.at(i+1).push_back(player);
                        tempScores.at(i).erase(tempScores.at(i).begin());

                        continue;
                    }
                }

            int shift;
                shift = 0;
                pairs.clear();
                pairs.push_back(tempScores.at(i).at(0));
                pairs.push_back(tempScores.at(i).at((tempScores.at(i).size())-1 -firstShift));
                while (conditions(pairs,currRound,people)){
                    pairs.clear();
                    shift++;
                    if (shift == (tempScores.at(i).size() -1)) {
                        firstShift +=1;
                        j--;
                        break;
                    }

                    pairs.push_back(tempScores.at(i).at(0));
                    pairs.push_back(tempScores.at(i).at(tempScores.at(i).size()-shift));


                }

                tempScores.at(i).erase(tempScores.at(i).begin());
                tempScores.at(i).erase(tempScores.at(i).begin()+tempScores.at(i).size()-shift-1-firstShift);
                matches.push_back(pairs);
            }
        }
    }
    return matches;
}

// ------------------------------------Kevin's stuff--------------------------------------

void tournament::on_pushButton_2_clicked()
{
    viewTournament view;
    view.setPeople(people);
    view.setRows(people.size());
    vector<vector<Person>> vectoredPeople = pigeonHoleSort(currentRound + 1, people);

    for (int i = 0; i < people.size(); i++) {
        view.setCell(i, 0, people[i].getName());
        view.setCell(i, 1, to_string(people[i].getRating()));
        // Truncating decimal
        string temp = to_string(people[i].getScore());
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
                int result = stoi(ui->tableWidget->item(i, 0)->text().toStdString());
                ui->tableWidget->setItem(i, 0, nullptr);
                string strresult = "";
                if (result == 1) {
                    strresult = "W";
                }
                else if (result == 0.5) {
                    strresult = "D";
                }
                people[j].updateMatchHistory(currentRound, strresult, i, "WH");
            }
            // Check for black player
            if (people[j].getName() == ui->tableWidget->item(i, 3)->text().toStdString()) {
                int result = stoi(ui->tableWidget->item(i, 2)->text().toStdString());
                ui->tableWidget->setItem(i, 2, nullptr);
                string strresult = "";
                if (result == 1) {
                    strresult = "W";
                }
                else if (result == 0.5) {
                    strresult = "D";
                }
                people[j].updateMatchHistory(currentRound, strresult, i, "BL");
            }
        }
    }
    // Create the next round pairings and display

    currentRound++;
    vector<vector<Person>> vectoredPeople = createPairings(people, currentRound);

    for (int i = 0; i < vectoredPeople.size(); i++) {
        if (currentRound % 2 == 1) {
            setCell(i, 3, vectoredPeople[i][1].getName());
            setCell(i, 1, vectoredPeople[i][0].getName());
        }
        else {
            setCell(i, 3, vectoredPeople[i][0].getName());
            setCell(i, 1, vectoredPeople[i][1].getName());
        }
    }
    if (currentRound < totalRound) {
        QString display = "Current Round: " + QString::number(currentRound);
        ui->label->setText(display);
    }
    else if (currentRound == totalRound){
        QString display = "Final Round";
        QString buttonText = "Enter Final Scores";
        ui->label->setText(display);
        ui->pushButton_3->setText(buttonText);
    }
    else {
        ui->pushButton_3->setEnabled(false);
    }
}

