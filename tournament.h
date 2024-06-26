#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "person.h"
#include "ui_tournament.h"
#include <QDialog>

namespace Ui {
class tournament;
}

class tournament : public QDialog
{
    Q_OBJECT

public:
    explicit tournament(QWidget *parent = nullptr);
    std::vector<Person> people;
    int currentRound = 1;
    int totalRound;
    bool createNewPairings = true;
    void setTotalRound(int num) {
        totalRound = num;
    }
    void setPeople(std::vector<Person> &v) {
        people = v;
    };
    void setRows(int num) {
        ui->tableWidget->setRowCount(num);
    }
    void setCell(int row, int column, string data) {
        QString qdata = QString::fromStdString(data);
        QTableWidgetItem *item = new QTableWidgetItem(qdata);
        ui->tableWidget->setItem(row, column, item);
    }
    void updateButtonState();

    // Tournament Info
    string tournamentName;
    string organizer;
    string timeControl;
    string location;
    string rounds;
    string date;
    void setTournamentInfo(string tournamentName, string organizer, string timeControl, string location, string rounds, string date) {
        this->tournamentName = tournamentName;
        this->organizer = organizer;
        this->timeControl = timeControl;
        this->location = location;
        this->rounds = rounds;
        this->date = date;
    }


    // Kevin's Stuff
    void giveBye(Person &player, int currRound);
    void sortRatings(std::vector<Person> &people);
    std::vector<std::vector<Person>> pigeonHoleSort(int currRound, std::vector<Person> &people);
    int findRank(std::vector<Person> people, Person player);
    bool conditions(std::vector<Person> &pair, int currRound, std::vector<Person> people);
    std::vector<std::vector<Person>> createPairings(std::vector<Person> &people, int currRound);

    ~tournament();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::tournament *ui;
};

#endif // TOURNAMENT_H
