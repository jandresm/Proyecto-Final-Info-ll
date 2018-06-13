#include "movimiento.h"

Movimiento::Movimiento(float m, bool direccion)
{
    srand(time(NULL));
    if(m==0){
        setAceleracion(0,10);      //Caida Libre
        setVelocidad(0,5);
    }
    else if(m==1){                  // Movimiento Parabolico
        if(direccion){
            setAceleracion(0,10);
            setVelocidad(-(30+rand()%40),-(30+rand()%40));
        }
        else{
            setAceleracion(0,10);
            setVelocidad(30+rand()%40,-(30+rand()%40));
        }
    }
    else if(m==2){                      // Movimiento Rectilineo uniforme
        if(direccion){
            setAceleracion(-20,0);
            setVelocidad(-50,0);
        }
        else{
            setAceleracion(20,0);
            setVelocidad(50,0);
        }
    }
}

Movimiento::Movimiento()
{
    ax = ay = 0;
    vx = vy = 0;
}

void Movimiento::setPosicion(float _x, float _y)
{
    x=_x; y=_y;
}

void Movimiento::setVelocidad(float _x, float _y)
{
    vx=_x; vy=_y;
}

void Movimiento::setAceleracion(float _x, float _y)
{
    ax=_x; ay=_y;
}

QPoint* Movimiento::getPosicion()
{
    QPoint *point=new QPoint(x,y);
    return point;
}

QPoint *Movimiento::getVelocidad()
{
    QPoint *point=new QPoint(vx,vy);
    return point;
}

QPoint *Movimiento::getAceleracion()
{
    QPoint *point=new QPoint(ax,ay);
    return point;
}

void Movimiento::calculaPosicion(float dt)
{
    x = x + vx*dt + (1/2)*ax*pow(dt,2);
    y = y + vy*dt + (1/2)*ay*pow(dt,2);
}

void Movimiento::calculaVelocidad(float dt)
{
    vx = vx + ax*dt;
    vy = vy + ay*dt;
}

void Movimiento::calculaAngulo()
{
    angulo=atan(vy/vx);
}

void Movimiento::actualizar(float dt)
{
    calculaVelocidad(dt);
    calculaAngulo();
    calculaPosicion(dt);
}



