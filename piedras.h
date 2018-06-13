#ifndef PIEDRAS_H
#define PIEDRAS_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>

class Piedras :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Piedras(float x, float y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap imagen;
    float px,py;
};


#endif // PIEDRAS_H
