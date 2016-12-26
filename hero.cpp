#include "Hero.h"
#include "Windows.h"
#include <math.h>
#include <QTimer>
#include "bonus.h"
#include "mainwindow.h"

Hero::Hero(QObject *parent) : QObject(parent),QGraphicsItem()
{
    angle = 0;
    health = 100;
    lvl = 1;
    xp = 0;
    setRotation(angle);
}



Hero::~Hero()
{

}

QRectF Hero::boundingRect() const
{
    return QRectF(-25,-40,50,80); // область, в которой лежит Hero
}

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
            // Помещаем координаты точек в полигональную модель
    polygon << QPoint(0,-40) << QPoint(25,40) << QPoint(-25,40);
    painter->setBrush(Qt::red);     // Устанавливаем кисть, которой будем отрисовывать объект
    painter->drawPolygon(polygon);  // Рисуем треугольник по полигональной модели
}

int Hero::getHealth()
{
    return health;
}
int Hero::getLvl()
{
    return lvl;
}

int Hero::getXp()
{
    return xp;
}

void Hero::slotNickChanged(QString nick)
{
    this->nick = nick;
}

void Hero:: slotHPChanged(int hp)
{
    health = hp;
    emit signalRefreshHp(health);
    if (health == 0)
    {
        emit signalEndGame();
    }
    if(health > 100)
    {
        health = 100;
    }
}

void Hero::slotXPChanged(int _xp)
{
    int maxXp = this->lvl * 100;
    if (_xp >= maxXp)
    {
        lvl++;
        _xp -= maxXp;
        emit signalRefreshLvl(lvl);

        //if (!db.isOpen())
        //{//DB reopen
        //    db.open();
        //}
        //QSqlQuery *getGuery = new QSqlQuery("SELECT nick FROM results", db);
        //while (getGuery->next())
        //{
        //    nick = getGuery->value(0).toInt();
        //}

        //QSqlQuery *query = new QSqlQuery(QString("INSERT INTO results (nick, lvl) VALUES(") +


        //nick + QString(",'") + lvl + QString("');"), db);


        //db.close();


        //delete getGuery;


        //delete query;
    }
    this->xp = _xp;
    emit signalRefreshXp(xp);
}

void Hero::slotGameTimer()
{
    /* Поочерёдно выполняем проверку на нажатие клавиш
     * с помощью функции асинхронного получения состояния клавиш,
     * которая предоставляется WinAPI
     * */
    if(GetAsyncKeyState(VK_LEFT))
    {
        angle-=1;
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_RIGHT))
    {
        angle+=1;
        setRotation(angle); // Поворачиваем объект
    }
    if(GetAsyncKeyState(VK_UP))
    {
        setPos(mapToParent(0, -4));
    }
    if(GetAsyncKeyState(VK_DOWN))
    {
        setPos(mapToParent(0, 4));
    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 10 < -400)
    {
        this->setX(-390);       // слева
    }
    if(this->x() + 10 > 400)
    {
        this->setX(390);        // справа
    }

    if(this->y() - 10 < -300)
    {
        this->setY(-290);       // сверху
    }
    if(this->y() + 10 > 300)
    {
        this->setY(290);        // снизу
    }
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF() << mapToScene(0, 0) << mapToScene(-20, -20) << mapToScene(20, -20));

        foreach (QGraphicsItem *item, foundItems)
        {
            if (item == this)
            {
                continue;
            }
            emit signalCheckItem(item);
        }
}

