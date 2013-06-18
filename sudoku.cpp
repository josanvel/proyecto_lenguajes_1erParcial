#include "sudoku.h"
#include "ui_sudoku.h"
#include <QApplication>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTime>
#include <time.h>
#include <iostream>

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudoku)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Juvenil");
    ui->comboBox->addItem("Profesional");
    ui->comboBox->addItem("Experto");
    initGui();

}

sudoku::~sudoku()
{
    delete ui;
}

void sudoku::initGui(){

    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 9; j++){
            numbertext[i][j] = new QTextEdit(NULL);
            ui->numberPad->addWidget(numbertext[i][j], i, j);
        }
    }
}

void sudoku::on_Validar_clicked(){

    long sumatoriah = 0;
    long productoh = 1;
    long sumatoriav = 0;
    long productov = 1;
    long sumatoriacuad = 0;
    long productocuad = 1;
    int despx=0,despy=0;
    int banderavalida=1;

    //Validacion numeros del 1 al 9 en las filas

    for(int i = 0;i < 9; i++){
        sumatoriah=0;
        productoh=1;
        for(int j = 0; j < 9; j++){
            sumatoriah+=getDisplayValue(i,j);
            productoh*=getDisplayValue(i,j);
        }
        if ((sumatoriah==45) && (productoh==362880))
            banderavalida=1;
        else
            banderavalida=0,i=10;//linea que rompe el ciclo en caso de no cumplir condicion
    }

     //Validacion numeros del 1 al 9 en las columnas
    for(int j = 0;j < 9; j++){
        sumatoriav=0;
        productov=1;
        for(int i = 0; i < 9; i++){
            sumatoriav+=getDisplayValue(i,j);
            productov*=getDisplayValue(i,j);
        }
        if ((sumatoriav==45) && (productov==362880) )
            banderavalida=1;
        else
            banderavalida=0,j=10;//linea que rompe el ciclo en caso de no cumplir condicion
    }

    for(int x = 0;x < 9; x++){
        sumatoriacuad=0;
        productocuad=1;
        despy=(x/3) *3;
        despx=(x%3) *3;
        for(int i = 0;i < 3; i++){
            for(int j = 0; j < 3; j++){
                sumatoriacuad+=getDisplayValue(i+despy,j+despx);
                productocuad*=getDisplayValue(i+despy,j+despx);
            }
        }
        if ((sumatoriacuad==45) && (productocuad==362880) )
            banderavalida=1;
        else
            banderavalida=0,x=10;//linea que rompe el ciclo en caso de no cumplir condicion
    }

    //comprobacion de validacion en general
    if (banderavalida==1){
        QMessageBox::information(this, "Respuesta", "La solucion es valida");
    }else{
        QMessageBox::information(this, "Respuesta", "La solucion no es valida");
    }

}
void sudoku::setDisplayValue(int i,int j,long v){
    numbertext[i][j]->setText( QString("%1").arg(v) );
    numbertext[i][j]->setAlignment(Qt::AlignRight);
}

long sudoku::getDisplayValue(int i,int j) {
    return numbertext[i][j]->toPlainText().toLong();
}

void sudoku::on_actionQuit_triggered(){
    qApp->quit();
}



//Borrar Juego
void sudoku::on_pushButton_clicked(){
    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 9; j++){
            numbertext[i][j]->setText("");
        }
    }
}
//SALIR
void sudoku::on_pushButton_4_clicked(){
    this->close();
}
//JUEGO NUEVO
void sudoku::on_pushButton_3_clicked(){
    int k, aleatorio;
    QStringList  valores;
    QString plantilla1, plantilla2, plantilla3;

    QTime *seed = new QTime;
    seed->start();
    qsrand(seed->msec());

    if(ui->comboBox->currentText() == "Juvenil"){//MODO JUVENIL(FACIL)}
        k=0;
        plantilla1 = "7,8,4,9,5,2,3,1,6,9,2,6,1,4,3,8,5,7,3,5,1,8,6,7,9,4,2,4,7,8,5,2,1,6,9,3,1,6,5,3,7,9,2,8,4,2,9,3,6,8,4,1,7,5,6,4,9,2,1,5,7,3,8,5,1,2,7,3,8,4,6,9,8,3,7,4,9,6,5,2,1";
        valores = plantilla1.split(",");

        for(int i = 0;i < 9; i++){
            for(int j = 0; j < 9; j++){
                aleatorio = rand() % 10;
                if (aleatorio <= 6){
                    numbertext[i][j]->setTextColor(Qt::red);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                    numbertext[i][j]->setDisabled(true);
                }else{
                    numbertext[i][j]->setText("");
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                }
                k++;
            }
        }
    }else if(ui->comboBox->currentText() == "Profesional"){//MODO PROFESIONAL(MEDIO)
        k=0;
        plantilla2 = "5,9,7,4,3,2,6,1,8,2,8,4,1,6,7,3,9,5,6,3,1,8,9,5,2,4,7,4,5,3,6,7,1,9,8,2,8,7,9,2,5,3,4,6,1,1,6,2,9,4,8,5,7,3,9,2,5,7,1,6,8,3,4,7,4,8,3,2,9,1,5,6,3,1,6,5,8,4,7,2,9";
        valores = plantilla2.split(",");

        for(int i = 0;i < 9; i++){
            for(int j = 0; j < 9; j++){
                aleatorio = rand() % 10;
                if (aleatorio <= 4){
                    numbertext[i][j]->setTextColor(Qt::blue);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                    numbertext[i][j]->setDisabled(true);
                }else{
                    numbertext[i][j]->setText("");
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                }
                k++;
            }
        }
    }else if(ui->comboBox->currentText() == "Experto"){//MODO EXPERTO(DIFICIL)

    }
}


