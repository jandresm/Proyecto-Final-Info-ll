#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <iostream>

#include "dialog.h"
#include "cuentas.h"
#include "personaje.h"
#include "piedras.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void cargarJuego(bool writeRead, Cuentas *c1,Cuentas *c2);
    bool getEmpezar() const;
    void setEmpezar(bool value);
    void serialInit();
    void serialRead();
    void read(QString _file);

    void write(QString _file);
private slots:
    void contador();        //Cuenta el tiempo
    void turno();           //Otorga los turnos
    void on_pushButton_clicked();       // Selecciona la bomba

    void on_pushButton_2_clicked();     // Selecciona el rocket

    void on_pushButton_3_clicked();     // Selecciona la bala

    void on_actionGuardar_triggered();

private:
    Ui::MainWindow *ui;
    Cuentas *jug1;                      //Cuentas de usuario
    Cuentas *jug2;
    QGraphicsScene *scene;
    QTimer *timerTiempo;                    //Cuenta tiempo
    QTimer *timerTurno;                     //Cuenta turnos
    int minutos=0,segundos=0,turnoint=0,posicion=0;
    int espaciador=35;
    int numPersonajes;
    int piedras=13;
    QList<Personaje *> personajes;
    QList<Personaje *> personajes2;
    bool turnob=true;
    QSerialPort serial;
    char dir;
    Personaje *personaje;
    QString contenido;
    QList<QString> datos;


};

#endif // MAINWINDOW_H
