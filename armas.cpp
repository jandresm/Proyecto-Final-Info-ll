#include "armas.h"

Armas::Armas(int tipo, float x, float y, bool direccion) :tipoo(tipo), xo(x)
{
    setPos(x,y);                                                //Da la posicion inicial del arma
    if(tipo==0){movimiento = new Movimiento(0,direccion);imagen=QPixmap(":/imagenes/bombaa(1).png");}         // SE DECLARA
    else if(tipo ==1){movimiento = new Movimiento(1,direccion);imagen=QPixmap(":/imagenes/rocket(1).png");}   //LA IMAGEN DESEADA
    else{movimiento = new Movimiento(2,direccion);imagen=QPixmap(":/imagenes/misil(1).png");}
    movimiento->setPosicion(x,y);                       //Da la posicion a la clase encargada del movimiento
    QTimer *timer= new QTimer();                        //SE MUEVE EL ARMA
    connect(timer,SIGNAL(timeout()),this,SLOT(moverArma()));
    timer->start(30);
}


QRectF Armas::boundingRect() const
{
    return QRectF(x(),y(),25,25);                  // Retorna un cuadrado con estas medidas
}

void Armas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),imagen,imagen.rect());       //Dibuja el arma con la imagen seleccionada
}



void Armas::moverArma()
{
    doCollision();
    movimiento->actualizar(DT);
    setPos(movimiento->getPosicion()->x(),movimiento->getPosicion()->y());
}
void Armas::doCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0;i<colliding_items.size();i++){
        if(typeid(*(colliding_items[i]))==typeid(Piedras)){
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
        }
        if(typeid(*(colliding_items[i]))==typeid(Personaje)){        //SE ELIMINA
            if(tipoo!=1){
                colliding_items.at(i)->advance(0);
            }
            else{
                colliding_items.at(i)->advance(1);
            }
            scene()->removeItem(this);
        }
        //if(movimiento->getPosicion()->x()>scene()->width()){scene()->removeItem(this);}
        //if(movimiento->getPosicion()->y()>scene()->height()){scene()->removeItem(this);}
    }

}
