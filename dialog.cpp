#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    usuario1=new Cuentas();
    usuario2=new Cuentas();
}

Dialog::~Dialog()
{
    delete ui;
}

Cuentas *Dialog::getJug1()
{
    return usuario1;
}

Cuentas *Dialog::getJug2()
{
    return usuario2;
}

void Dialog::on_pushButton_clicked()
{
    if(!ui->lineEdit->text().isEmpty()){usuario1->setName(ui->lineEdit->text());}
    else{QMessageBox::information(this,"ADVERTENCIA","El juego se creara sin un usuario.");}
    if(!ui->lineEdit_2->text().isEmpty()){usuario2->setName(ui->lineEdit_2->text());}
    else{QMessageBox::information(this,"ADVERTENCIA","El juego se creara sin un usuario.");}
    //Nuevo Juego
    usuario1->setCargarGuardar(true);
    close();

}

void Dialog::on_pushButton_2_clicked()
{
    if(!ui->lineEdit->text().isEmpty()){usuario1->setName(ui->lineEdit->text());}
    else{
        QMessageBox::information(this,"ADVERTENCIA","El juego se creara sin un usuario.");
        usuario1->setName("Anonimo");
    }
    if(!ui->lineEdit_2->text().isEmpty()){usuario2->setName(ui->lineEdit_2->text());}
    else{
        QMessageBox::information(this,"ADVERTENCIA","El juego se creara sin un usuario.");
        usuario2->setName("Anonimo");
    }
    //Cargar Juego
    usuario1->setCargarGuardar(false);

    close();
}



void Dialog::on_pushButton_3_clicked()
{
    usuario1->setNumPersonajes(1);
    usuario2->setNumPersonajes(1);
}

void Dialog::on_pushButton_4_clicked()
{
    usuario1->setNumPersonajes(2);
    usuario2->setNumPersonajes(2);
}

void Dialog::on_pushButton_5_clicked()
{
    usuario1->setNumPersonajes(3);
    usuario2->setNumPersonajes(3);
}


