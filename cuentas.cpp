#include "cuentas.h"


Cuentas::Cuentas(): name(""), numPersonajes(1)
{

}

Cuentas::Cuentas(QString _name, int _per) : name(_name),numPersonajes(_per)
{
    sangre=100;
}

QString Cuentas::getName() const
{
    return name;
}

void Cuentas::setName(const QString &value)
{
    name = value;
}

int Cuentas::getSangre() const
{
    return sangre;
}

void Cuentas::setSangre(const int &value)
{
    sangre = value;
}


int Cuentas::getNumPersonajes() const
{
    return numPersonajes;
}

void Cuentas::setNumPersonajes(int value)
{
    numPersonajes = value;
}

bool Cuentas::getCargarGuardar() const
{
    return cargarGuardar;
}

void Cuentas::setCargarGuardar(bool value)
{
    cargarGuardar = value;
}



