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
    // Assuming tableWidget is the name of your QTableWidget object

    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &tournament::updateButtonState);

}

tournament::~tournament()
{
    delete ui;
}

void tournament::updateButtonState() {
    // Count the number of non-empty cells
    int filledCount = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j += 2) {
            if (ui->tableWidget->item(i, j) && !ui->tableWidget->item(i, j)->text().isEmpty()) {
                filledCount++;
            }
        }
    }

    // Enable/disable the button based on the filled cell count
    if (filledCount >= ui->tableWidget->rowCount() * 2) { // Change 'threshold' to the desired number of filled cells
        ui->pushButton_3->setEnabled(true);
    } else {
        ui->pushButton_3->setEnabled(false);
    }
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
    if (pair.size() != 2) {
        return true;
    }

    if (currRound > 2) {
        vector<vector<bool>> pairSameColor;
        vector<vector<string>> playersHistory;

        // gets the history for each person into the player's history vector.
        for(int i = 0; i < pair.size(); i++) {
            playersHistory.push_back(pair.at(i).getMatchHistory());
        }
        for (int i = 0; i < playersHistory.size(); i++) {
            vector<bool> sameColor;
            sameColor.push_back(false);
            sameColor.push_back(false);
            if((playersHistory.at(i).at(currRound -2) == "BYE") || (playersHistory.at(i).at(currRound -3) == "BYE")){
                pairSameColor.push_back(sameColor);
                continue;
            }
            char prevColor = playersHistory.at(i).at(currRound -2).at(5);
            char prevPrevColor = playersHistory.at(i).at(currRound -3).at(5);


            if(prevColor == prevPrevColor) {
                if (prevColor == 'W') {
                    sameColor.at(0) = true;
                }
                else if (prevColor == 'B') {
                    sameColor.at(1) = true;
                }
            }
            pairSameColor.push_back(sameColor);
        }
        for (int i = 0; i < pairSameColor.size(); i++) {
            if ((pairSameColor.at(0).at(i)) && (pairSameColor.at(1).at(i))) {
                return true;
            }
        }

        //Write the code for swapping the two colors
        for (int i = 0; i < pairSameColor.size(); i++) {
            if (pairSameColor.at(i).at(i)) {
                reverse(pair.begin(), pair.end());
            }
        }
    }
    // same player

    for (int i = 0; i < currRound - 1; i++ ) {
        string playerOneMatch = pair.at(0).getMatchHistory().at(i);
        string playerTwoMatch = pair.at(1).getMatchHistory().at(i);
        if(playerOneMatch.at(2) == 'E') {
            break;
        }
        \
            if (playerOneMatch.at(2) == playerTwoMatch.at(2)) {
            return true;
        }
    }
    return false;
}






vector<vector<Person>> tournament::createPairings(vector<Person> &people, int currRound) {
    //sorting algorithm for the people vector
    vector<vector<Person>> scores;
    vector<vector<Person>> tempScores;
    vector<vector<Person>> matches;
    vector<vector<vector<Person>>> scoresHistory;
    int prevShift = 0;
    int count =0;

    scores = pigeonHoleSort(currRound + 2, people);
    reverse(scores.begin(),scores.end());
    tempScores = scores;

    //Round one with no conditions are being broken

    int temps = people.size()/2;
    while(matches.size() != temps) {
        int firstShift = 0;


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
            if ((firstShift == (tempScores.at(i).size()-1)) && (i != tempScores.size()-1)) {
                Person player = tempScores.at(i).at(tempScores.at(i).size()-1);
                tempScores.at(i+1).push_back(player);
                tempScores.at(i).erase(tempScores.at(i).begin()+tempScores.at(i).size()-1);
                firstShift = 0;
                i-=2;
                continue;
            }

            for(int j = 0; j < repeats; j++) {

                vector<Person> pairs;
                Person player;
                int index = 0;
                bool noPairsExist = false;

                if ((tempScores.at(i).size() == 1) || ((i == tempScores.size()-1) && (tempScores.at(i).size() % 2 == 1))) {
                    if (i == tempScores.size()-1) {


                        player = tempScores.at(tempScores.size()-1).at(0);
                        for (int k = 0; k < people.size(); k++) {
                            if (player.getName() == people.at(k).getName()) {
                                index = k;
                            }
                        }
                        giveBye(people.at(index), currRound);

                        tempScores.at(i).erase(tempScores.at(i).begin());
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
                while(conditions(pairs,currRound,people)) {
                    shift = 0;
                    pairs.clear();
                    pairs.push_back(tempScores.at(i).at(0));
                    pairs.push_back(tempScores.at(i).at((tempScores.at(i).size())-1 -firstShift));
                    while (conditions(pairs,currRound,people)){
                        pairs.clear();
                        shift++;
                        pairs.push_back(tempScores.at(i).at(0));
                        pairs.push_back(tempScores.at(i).at(tempScores.at(i).size()-shift-firstShift));
                        if (!conditions(pairs,currRound,people)) {
                            break;
                        }
                        if (shift == (tempScores.at(i).size() -1) || (shift + firstShift == (tempScores.at(i).size()-1))){

                            if (prevShift >= tempScores.at(i).size()) {
                                Person player = tempScores.at(i).at(tempScores.at(i).size()-1);
                                tempScores.at(i+1).push_back(player);
                                tempScores.at(i).erase(tempScores.at(i).begin()+tempScores.at(i).size()-1);
                                player = tempScores.at(i).at(tempScores.at(i).size()-1);
                                tempScores.at(i+1).push_back(player);
                                tempScores.at(i).erase(tempScores.at(i).begin()+tempScores.at(i).size()-1);
                                repeats--;
                                noPairsExist = true;
                                break;
                            }
                            if (scoresHistory.size() != 0) {
                                tempScores = scoresHistory.at(scoresHistory.size()-1);
                                scoresHistory.pop_back();
                                matches.pop_back();
                            }
                            noPairsExist = true;
                            firstShift +=1;
                            i =0;
                            break;
                        }

                    }

                    if (noPairsExist) {
                        break;
                    }

                }

                if ((prevShift > 0)&& (noPairsExist)) {
                    continue;
                }
                if (noPairsExist){
                    break;
                }


                scoresHistory.push_back(tempScores);
                tempScores.at(i).erase(tempScores.at(i).begin());
                prevShift = shift + firstShift;
                if (shift > 0)shift--;
                tempScores.at(i).erase(tempScores.at(i).begin()+tempScores.at(i).size()-shift-1-firstShift);
                matches.push_back(pairs);
                if (firstShift > 0) {
                    firstShift = 0;
                }
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
    view.setColumns(3 + totalRound);
    vector<vector<Person>> vectoredPeople = pigeonHoleSort(currentRound + 1, people);

    for (int i = 0; i < people.size(); i++) {
        view.setCell(i, 0, people[i].getName());
        view.setCell(i, 1, to_string(people[i].getRating()));
        // Truncating decimal
        string temp = to_string(people[i].getScore());
        view.setCell(i, 2, temp.substr(0, 3));
        for (int j = 3; j < totalRound + 3; j++) {
            view.setCell(i, j, people[i].getMatchHistory()[j - 3]);
        }
    }
    view.setTournamentInfo(tournamentName, organizer, timeControl, location, rounds, date);
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
                double result = stod(ui->tableWidget->item(i, 0)->text().toStdString());
                ui->tableWidget->setItem(i, 0, nullptr);
                string strresult = "";
                if (result == 1) {
                    strresult = "W";
                }
                else if (result == 0.5) {
                    strresult = "D";
                }
                else {
                    strresult = "L";
                }
                people[j].updateMatchHistory(currentRound, strresult, i + 1, "WH");
            }
            // Check for black player
            if (people[j].getName() == ui->tableWidget->item(i, 3)->text().toStdString()) {
                double result = stod(ui->tableWidget->item(i, 2)->text().toStdString());
                ui->tableWidget->setItem(i, 2, nullptr);
                string strresult = "";
                if (result == 1) {
                    strresult = "W";
                }
                else if (result == 0.5) {
                    strresult = "D";
                }
                else {
                    strresult = "L";
                }
                people[j].updateMatchHistory(currentRound, strresult, i + 1, "BL");
            }
        }
    }
    // Create the next round pairings and display

    currentRound++;
    vector<vector<Person>> vectoredPeople;
    if (createNewPairings) {
        vectoredPeople = createPairings(people, currentRound);
    }

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
        createNewPairings = false;
    }
    else {
        ui->pushButton_3->setEnabled(false);
        for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        ui->tableWidget->clear();
        }
    }
}

