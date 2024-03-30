#ifndef ADDPLAYERDIALOG_H
#define ADDPLAYERDIALOG_H

#include "ui_addplayerdialog.h"
#include <QDialog>

namespace Ui {
class addPlayerDialog;
}

class addPlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addPlayerDialog(QWidget *parent = nullptr);
    QString getName() const;
    QString getRating() const;
    ~addPlayerDialog();


private:
    Ui::addPlayerDialog *ui;
};

#endif // ADDPLAYERDIALOG_H
