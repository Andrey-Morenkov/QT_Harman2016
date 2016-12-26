#ifndef HERO_H
#define HERO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

#include "Windows.h"

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Hero(QObject *parent = 0);
    ~Hero();

signals:
    void signalCheckItem(QGraphicsItem *item);
    void signalRefreshXp(int xp);
    void signalRefreshLvl(int lvl);
    void signalRefreshHp(int hp);
    void signalEndGame();

public slots:
    void slotGameTimer(); // обработка перемещения по таймеру
    void slotHPChanged(int hp);
    void slotXPChanged(int xp);
    void slotNickChanged(QString nick);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int health;
    int xp;
    int lvl;
    QString nick;
    qreal angle;

public:
    int getHealth();
    int getLvl();
    int getXp();
};

#endif // HERO_H
