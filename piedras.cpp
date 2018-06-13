#include "piedras.h"

Piedras::Piedras(float x, float y): px(x),py(y)
{
    setPos(px,py);
    imagen=QPixmap(":/imagenes/Roca.png");
}

QRectF Piedras::boundingRect() const
{
    return QRectF(x(),y(),80,40);
}

void Piedras::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),imagen,imagen.rect());
}

