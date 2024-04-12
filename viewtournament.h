#ifndef VIEWTOURNAMENT_H
#define VIEWTOURNAMENT_H

#include "person.h"
#include "ui_viewtournament.h"
#include <QDialog>

namespace Ui {
class viewTournament;
}

class viewTournament : public QDialog
{
    Q_OBJECT

public:
    explicit viewTournament(QWidget *parent = nullptr);
    std::vector<Person> people;
    void setPeople(std::vector<Person> &v) {
        people = v;
    };
    void setRows(int num) {
        ui->tableWidget->setRowCount(num);
    }
    void setColumns(int num) {
        ui->tableWidget->setColumnCount(num);
    }
    void setCell(int row, int column, string data) {
        QString qdata = QString::fromStdString(data);
         QTableWidgetItem *item = new QTableWidgetItem(qdata);
        ui->tableWidget->setItem(row, column, item);
    }
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

    ~viewTournament();

private slots:
    void on_pushButton_clicked();

private:
    Ui::viewTournament *ui;
};

#endif // VIEWTOURNAMENT_H
