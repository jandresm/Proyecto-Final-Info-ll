#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"
#include "cuentas.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    Cuentas * getJug1();
    Cuentas * getJug2();
    void write();
    void read();

private slots:
    void on_pushButton_clicked();           //Nuevo Juego

    void on_pushButton_2_clicked();         //Cargar Juego

    void on_pushButton_3_clicked();         //Nivel 1

    void on_pushButton_4_clicked();         //Nivel 2

    void on_pushButton_5_clicked();         //Nivel 3


private:
    Ui::Dialog *ui;
    QString *nombre1;                   //Datos de los usuario
    QString *nombre2;
    Cuentas *usuario1;
    Cuentas *usuario2;
    bool nuevoCargar;               //Cargar / Guardar

};

#endif // DIALOG_H
