#ifndef CUENTAS_H
#define CUENTAS_H

#include <QString>
#include <QList>
#include <QMessageBox>
#include <QList>
#include "personaje.h"

class Cuentas
{
public:
    Cuentas();                          //Cuenta con nombre vacio y numero de personajes = 1
    Cuentas(QString _name, int _per);   //Cuenta con nombre _name y numero de personajes _per
    QString getName() const;
    void setName(const QString &value);

    int getSangre() const;
    void setSangre(const int &value);

    void calcularSangre();
    void recolectarDatos();


    int getNumPersonajes() const;
    void setNumPersonajes(int value);

    bool getCargarGuardar() const;
    void setCargarGuardar(bool value);

private:
    QString name;                       //Nombre del usuario
    QString contenido;                  //contenido al leer un archivo
    int sangre;                         //vida del usuario
    int numPersonajes;                  //Numero de personajes
    bool cargarGuardar;

};

#endif // CUENTAS_H
