#include "Bonus.h"

Bonus::Bonus(QObject *parent) : QObject(parent), QGraphicsItem()
{
    type = 1 + qrand() % 4;
}

Bonus::~Bonus()
{

}

QRectF Bonus::boundingRect() const
{
    return QRectF(-10,-10,20,20);
}

const QString Bonus::getsType()
{
    return sType;
}

int Bonus::getType()
{
    return type;
}

void Bonus::setType(int _type)
{
    type = _type;
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;   // Используем класс полигона, чтобы отрисовать треугольник
            // Помещаем координаты точек в полигональную модель
    polygon << QPoint(-10,-10) << QPoint(10,-10) << QPoint(10,10) << QPoint(-10,10);
    switch (type)
    {
    case 1:
        painter->setBrush(Qt::red);
        sType == "bomb";
        break;
    case 2:
        painter->setBrush(Qt::green);
        sType == "heal";
        break;
    case 3:
        painter->setBrush(Qt::yellow);
        sType == "xp";
        break;
    case 4:
        painter->setBrush(Qt::blue);
        sType == "speedup";
        break;
    }
    painter->drawPolygon(polygon);
}
