#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include "bonus.h"
#include "QSqlDatabase"

#include <Hero.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotRefreshLvl(int lvl);
    void slotRefreshXp(int xp);
    void slotRefreshHp(int hp);
    void slotDeleteBonus(QGraphicsItem *item);
    void slotCreateBonus();
    void slotEndGame();
    void slotEndSpeedup();

    void on_resButton_clicked();

    void on_okButton_clicked();

signals:
    void signalHPChanged(int hp);
    void signalXPChanged(int xp);
    void signalNickChanged(QString nick);

private:
    Ui::MainWindow  *ui;
    QGraphicsScene  *scene;
    Hero            *hero;
    QTimer          *timer2;
    QTimer          *timer;     /* Объявляем игровой таймер, благодаря которому
                                 * будет производиться изменения положения объекта на сцене
                                 * При воздействии на него клавишами клавиатуры
                                 * */
    QTimer          *timerCreateBonus;  // Таймер для периодического создания бонусов в игре
    QSqlDatabase db;

    QList<Bonus *> bonuses;  // Список со всеми бонусами, присутствующими в игре
};

#endif // MAINWINDOW_H
