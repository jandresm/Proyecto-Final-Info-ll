#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <QPoint>
#include <math.h>
#include <time.h>
#include <stdlib.h>

class Movimiento
{
public:
    Movimiento(float m,bool direccion);
    Movimiento();
    void setPosicion(float _x, float _y);
    void setVelocidad(float _x, float _y);
    void setAceleracion(float _x, float _y);

    QPoint *getPosicion();
    QPoint *getVelocidad();
    QPoint *getAceleracion();

    void calculaPosicion(float dt);
    void calculaVelocidad(float dt);
    void calculaAngulo();

    void actualizar(float dt);

private:
    float h,w;       //alto y ancho
    float x;
    float y;
    float vx;
    float vy;               //Atributos Fisicos del movimiento
    float ax;
    float ay;
    float angulo;
};


#endif // MOVIMIENTO_H
