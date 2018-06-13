#include "personaje.h"

Personaje::Personaje(float personaje, float _x, float _y)
{
    setPos(_x,_y);
    timer=new QTimer();
    if(personaje==1){
        imagen=QPixmap(":/imagenes/Personaje1.png");
        leftRight=false;
        personajes=true;
    }
    else{
        imagen=QPixmap(":/imagenes/Personaje2.png");
        leftRight=true;
        personajes=false;
    }
}

QRectF Personaje::boundingRect() const
{
    return QRectF(x(),y(),80,80);
}

void Personaje::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(personajes){
        if(leftRight==false){imagen=QPixmap(":/imagenes/Personaje1.png");}
        else{imagen=QPixmap(":/imagenes/Personaje1(1).png");}
    }
    else{
        if(leftRight){imagen=QPixmap(":/imagenes/Personaje2.png");}
        else{imagen=QPixmap(":/imagenes/Personaje2(1).png");}
    }
    painter->drawPixmap(boundingRect(),imagen,imagen.rect());

}
void Personaje::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Left){
        //docollision?
        ref=x()-10;
        setPos(ref,y());
        leftRight=true;

    }
    else if(event->key() == Qt::Key_Right){
        //docollision?
        ref=x()+10;
        setPos(ref,y());
        leftRight=false;
    }
    else if(event->key() == Qt::Key_Up){
        movimiento=new Movimiento(1,leftRight);
        if(leftRight){movimiento->setVelocidad(-8,-22);}
        else{movimiento->setVelocidad(8,-22);}
        movimiento->setPosicion(x(),y());
        connect(timer,SIGNAL(timeout()),this,SLOT(salto()));
        timer->start(20);
        doColision();
    }
    else if(event->key() == Qt::Key_Space /*&& armaFlag*/){
        setFalseTurno();
        if(tipo==0){
            Armas *bullet= new Armas(tipo,x(),-200,leftRight);scene()->addItem(bullet);
        }
        else if(tipo==1){
            if(leftRight){
                Armas *bullet= new Armas(tipo,x()-15,y(),leftRight);scene()->addItem(bullet);
            }
            else{
                Armas *bullet= new Armas(tipo,x()+40,y(),leftRight);scene()->addItem(bullet);
            }
        }
        else if(tipo==2){
            if(leftRight){
                Armas *bullet= new Armas(tipo,x()-15,y(),leftRight);scene()->addItem(bullet);
            }
            else{
                Armas *bullet= new Armas(tipo,x()+40,y(),leftRight);scene()->addItem(bullet);
            }
        }

    }
}


void Personaje::serialEvent(char dir)
{
    cout<<dir<<endl;
    if(dir == 'I'){
        //docollision?
        ref=x()-10;
        setPos(ref,y());
        leftRight=true;

    }
    else if(dir == 'D'){
        //docollision?
        ref=x()+10;
        setPos(ref,y());
        leftRight=false;
    }
    else if(dir == 'W'){
        movimiento=new Movimiento(1,leftRight);
        if(leftRight){movimiento->setVelocidad(-8,-22);}
        else{movimiento->setVelocidad(8,-22);}
        movimiento->setPosicion(x(),y());
        connect(timer,SIGNAL(timeout()),this,SLOT(salto()));
        timer->start(20);
        doColision();
    }
    else if(dir == 'S'){
        setFalseTurno();
        if(tipo==0){
            Armas *bullet= new Armas(tipo,x(),-200,leftRight);scene()->addItem(bullet);
        }
        else if(tipo==1){
            if(leftRight){
                Armas *bullet= new Armas(tipo,x()-15,y(),leftRight);scene()->addItem(bullet);
            }
            else{
                Armas *bullet= new Armas(tipo,x()+40,y(),leftRight);scene()->addItem(bullet);
            }
        }
        else if(tipo==2){
            if(leftRight){
                Armas *bullet= new Armas(tipo,x()-15,y(),leftRight);scene()->addItem(bullet);
            }
            else{
                Armas *bullet= new Armas(tipo,x()+40,y(),leftRight);scene()->addItem(bullet);
            }
        }

    }

}


void Personaje::doColision()
{
    QList<QGraphicsItem *> colliding_items= collidingItems();
    for(int i=0;i<colliding_items.size();i++){
        if(typeid(*(colliding_items[i]))==typeid(Piedras)){
            movimiento->setVelocidad(0,-1);
        }
        if(typeid(*(colliding_items[i]))==typeid(Armas)){
            vida-=20;
        }
    }
    if(movimiento->getPosicion()->y()>scene()->height()-40){
        vivo=false;
    }
    if(vida<=0){
        vivo=false;
    }
}

void Personaje::setTrueTurno()
{
    flagTurno=true;
}

void Personaje::setFalseTurno()
{
    flagTurno=false;
}

void Personaje::setVida(int value)
{
    vida=value;
}

int Personaje::getVida()
{
    return vida;
}

bool Personaje::getVivo()
{
    return vivo;
}

bool Personaje::getFlagTurno()
{
    return flagTurno;
}
void Personaje::salto()
{
    doColision();
    movimiento->actualizar(DT);
    if(movimiento->getPosicion()->y()>400){timer->stop();}
    if(x()== movimiento->getPosicion()->x()+10 || x()== movimiento->getPosicion()->x()-10){movimiento->setPosicion(ref,movimiento->getPosicion()->y());}
    setPos(movimiento->getPosicion()->x(),movimiento->getPosicion()->y());

}


void Personaje::advance(int phase)
{
    if(phase==0){
        vida-=10;
    }
    else{
        vida-=20;
    }
}

int Personaje::getTipo() const
{
    return tipo;
}

void Personaje::setTipo(int value)
{
    tipo = value;
}

int Personaje::getRef() const
{
    return ref;
}

void Personaje::setRef(int value)
{
    ref = value;
}
