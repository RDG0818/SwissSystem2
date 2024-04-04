#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();
    QString getTournamentName() const;
    QString getOrganizer() const;
    QString getTimeControl() const;
    QString getRounds() const;
    QString getLocation() const;
    QString getDate() const;

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
