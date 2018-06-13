#ifndef PERSONAJE_H
#define PERSONAJE_H

#define DT 0.02

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QObject>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QMessageBox>
#include <QGraphicsSceneMouseEvent>
#include <iostream>

#include "armas.h"
#include "movimiento.h"
#include "piedras.h"

using namespace std;

class Personaje :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Personaje();
    Personaje(float personaje,float _x, float _y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void keyPressEvent(QKeyEvent *event);
    void doColision();
    void setTrueTurno();
    void setFalseTurno();
    void setVida(int value);
    int getVida();
    bool getVivo();
    bool getFlagTurno();
    int getRef() const;
    void setRef(int value);

    int getTipo() const;
    void setTipo(int value);
    void serialEvent(char dir);

public slots:
    void salto();
    void advance(int phase);

private:
    QPixmap imagen;
    Movimiento *movimiento;
    Movimiento *movimiento_Gravedad;
    QTimer *timer;
    QTimer *timer_gravedad;
    int vida=100, ref, tipo=0 ;
    bool leftRight, personajes;
    bool flagTurno=false;
    bool vivo=true;
};

#endif // PERSONAJE_H
