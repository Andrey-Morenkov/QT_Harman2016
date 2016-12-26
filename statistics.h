#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui
{
    class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT

public:
    explicit Statistics(QWidget *parent = 0);
    ~Statistics();

private:
    Ui::Statistics *ui;
    QSqlDatabase db;
};

#endif // STATISTICS_H
