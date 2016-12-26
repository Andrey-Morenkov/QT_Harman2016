#ifndef BONUS_H
#define BONUS_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class Bonus : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Bonus(QObject *parent = 0);

    ~Bonus();

signals:

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int type;
    const QString sType;

public:
    const QString getsType();
    int getType();
    void setType(int _type);
};

#endif // BONUS_H
