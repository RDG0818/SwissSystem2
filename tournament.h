#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <QDialog>

namespace Ui {
class tournament;
}

class tournament : public QDialog
{
    Q_OBJECT

public:
    explicit tournament(QWidget *parent = nullptr);
    void setTableRow(int num);
    void setTableInfo(const std::vector<QString> &info);
    ~tournament();

private:
    Ui::tournament *ui;
};

#endif // TOURNAMENT_H
