#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setFixedSize(1350,650);
    scene->setSceneRect(-200,-200,600,400);

    jug1=new Cuentas();
    jug2=new Cuentas();


    serialInit();

    Dialog inicio;
    inicio.setModal(true);
    inicio.exec();

    if(inicio.close()){
        jug1=inicio.getJug1();
        jug2=inicio.getJug2();
        cargarJuego(jug1->getCargarGuardar(),jug1,jug2);
    }

    ui->label->setText(jug1->getName());
    ui->label_2->setText(jug2->getName());


    for(int i=0;i<piedras;i++){
        Piedras *piso=new Piedras(-200+(espaciador*i),90);
        scene->addItem(piso);
    }
    for(int i=0;i<3;i++){
        Piedras *piso=new Piedras(-300+(espaciador*i),0);
        scene->addItem(piso);
    }

    for(int i=0;i<3;i++){
        Piedras *piso=new Piedras(300+(espaciador*i),50);
        scene->addItem(piso);
    }

    timerTiempo=new QTimer();
    connect(timerTiempo,SIGNAL(timeout()),this,SLOT(contador()));
    if(inicio.close()){timerTiempo->start(1000);}


    timerTurno=new QTimer();
    connect(timerTurno,SIGNAL(timeout()),this,SLOT(turno()));
    if(inicio.close()){timerTurno->start(20);}




}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::serialInit()
{
    serial.setPortName("/dev/ttyACM0"); //Poner el nombre del puerto, probablemente no sea COM3

    cout<<"Serial init"<<"++++++++++++++++++++"<<endl;

    if(serial.open(QIODevice::ReadWrite)){
        //Ahora el puerto seria está abierto
        if(!serial.setBaudRate(QSerialPort::Baud9600)) //Configurar la tasa de baudios
            qDebug()<<serial.errorString();

        if(!serial.setDataBits(QSerialPort::Data8))
            qDebug()<<serial.errorString();

        if(!serial.setParity(QSerialPort::NoParity))
            qDebug()<<serial.errorString();

        if(!serial.setStopBits(QSerialPort::OneStop))
            qDebug()<<serial.errorString();

        if(!serial.setFlowControl(QSerialPort::NoFlowControl))
            qDebug()<<serial.errorString();

        qDebug()<<"Serial ok"<<endl;
    }else{
        qDebug()<<"Serial ttyACM0 not opened. Error: "<<serial.errorString();
    }
}

void MainWindow::serialRead(){


    serial.read(&dir,1); //Leer toda la línea que envía arduino
    /*if(dir!=0){

        cout<<dir<<"************+"<<endl;

    }*/
}

void MainWindow::cargarJuego(bool writeRead, Cuentas *c1, Cuentas *c2)
{
    ui->progressBar->setValue(c1->getSangre());
    ui->progressBar->setValue(c2->getSangre());

    //Nuevo juego
    if(writeRead){
        for(int i=0;i<c1->getNumPersonajes();i++){
            if(i==2){personaje=new Personaje(1,-150*(i+1),20);}
            else{personaje=new Personaje(1,-150*(i),50);}
            personajes.append(personaje);

            scene->addItem(personaje);

        }
        for(int i=0;i<c1->getNumPersonajes();i++){     //Dibujar rocas para colcarlos en niveles
            if(i==2){personaje=new Personaje(2,100*(i+1),20);}
            else{personaje=new Personaje(2,100*(i+1),50);}

            personajes2.append(personaje);

            scene->addItem(personaje);

        }
    }
    //Carga Juego
    else{
        QString aux;
        QString nombreArchivo;
        nombreArchivo.append(jug1->getName());
        nombreArchivo.append(jug1->getName());
        read(nombreArchivo);
        for(int i=0;i<contenido.size();i++){
            if(contenido.at(i)=='/n'){
                datos.append(aux);
                aux="";
            }
            else{
                aux.append(contenido.at(i));
            }
        }

    }
}
void MainWindow::read(QString _file)
{
    QFile myFile(_file);

    if(!myFile.open(QFile::ReadOnly | QFile::Text)){
        //QMessageBox::information(this,"ADVERTENCIA","Este es un juego nuevo, no se puede cargar.");
        exit(1);
    }
    QTextStream in(&myFile);
    contenido.append(in.readAll());
    myFile.close();
}
void MainWindow::write(QString _file)
{
    QFile myFile(_file);

    if(!myFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug () << "No se pudo abrir el archivo.";

        return;
    }
    QTextStream out(&myFile);
    out << jug1->getName() <<'\n'<<QString::number(jug1->getNumPersonajes())<<'\n'<< QString::number(jug1->getSangre())<<'\n'<<jug2->getName()<<'\n'<<QString::number(jug1->getNumPersonajes())<<'\n'<<QString::number(jug1->getSangre());

    myFile.flush();
    myFile.close();
}
void MainWindow::contador()
{
    segundos++;
    turnoint++;
    if(segundos>59){minutos++;}
    ui->lcdNumber->display(2-minutos);
    ui->lcdNumber_2->display(59-segundos);
    ui->lcdNumber_3->display(20-turnoint);
    ui->progressBar->setValue(personajes.at(posicion)->getVida());
    ui->progressBar_2->setValue(personajes2.at(posicion)->getVida());
    serialRead();
}

void MainWindow::turno()
{
    if(minutos< 3){
        if(turnob){
            if(dir!=0)
                personajes.at(posicion)->serialEvent(dir);

            dir = 0;
            personajes.at(posicion)->setFlag(QGraphicsItem::ItemIsFocusable);  //Cuentas y boleanos
            personajes.at(posicion)->setFocus();
            if(turnoint>30){
                turnob=false;
                turnoint=0;
                if(posicion<personajes.size()-1){++posicion;}
                else{posicion=0;}
                personajes.at(posicion)->clearFocus();
            }

        }
        else{
            if(dir!=0)
                personajes2.at(posicion)->serialEvent(dir);

            personajes2.at(posicion)->setFlag(QGraphicsItem::ItemIsFocusable);  //Cuentas y boleanos
            personajes2.at(posicion)->setFocus();
            if(turnoint>20){
                turnob=false;
                turnoint=0;
                if(posicion<personajes.size()-1){++posicion;}
                else{posicion=0;}
                personajes2.at(posicion)->clearFocus();
            }
        }
    }
    else{
        timerTiempo->stop();
        timerTurno->stop();
        QMessageBox::information(this,"GAME OVER",  "El juego se ha acabado");
    }
}


void MainWindow::on_pushButton_clicked()
{
    // Lanzar una bomba
    personajes.at(posicion)->setTipo(0);
    personajes2.at(posicion)->setTipo(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    //Lanzar un misil con movimiento parabolico
    personajes.at(posicion)->setTipo(1);
    personajes2.at(posicion)->setTipo(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    //Lanzar una esfera con mov rectilineo uniforme
    personajes.at(posicion)->setTipo(2);
    personajes2.at(posicion)->setTipo(2);
}


void MainWindow::on_actionGuardar_triggered()
{
    QString aux;
    aux.append(jug1->getName());
    aux.append(jug2->getName());
    write(aux);
}
