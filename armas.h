#ifndef ARMAS_H
#define ARMAS_H

#define DT 0.02

#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <movimiento.h>
#include <QTimer>
#include <QObject>
#include <QPoint>
#include <QDebug>
#include "personaje.h"

class Armas : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Armas(int tipo,float x,float y,bool direccion);   //Contruye un arma de tipo especificado con sus respectivas posiciones y en direccion del lanzamiento
    QRectF boundingRect() const;                //espacio que ocupa el arma en la escena
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);// dibuja el arma con su respectiva imagen

public slots:
    void moverArma();       //Respuesta al timer que le da el movimiento al arma
    void doCollision();        // Respuesta especifica cuando el arma colisiona con otro objeto
private:
    int tipoo;     // tipo de arma
    Movimiento *movimiento;    //movimiento del arma
    QPixmap imagen;             // Clase encargada de dar la imagen respectiva
    int xo;                     //
};

#endif // ARMAS_H
