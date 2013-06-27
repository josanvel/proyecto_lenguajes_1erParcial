#include "sudoku.h"
#include "ui_sudoku.h"
#include <math.h>

sudoku::sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sudoku)
{
    ui->setupUi(this);
    initGui();
}

sudoku::~sudoku(){
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

void sudoku::setCargar(QString datos, QString nivel, QString nombre){
   datosCargados = datos;
   QStringList  valores;
   int i,j,k=0;
   double cont =33, opera;
   valores = datosCargados.split(",");
   for(i = 0; i < 9; i++){
       for(j = 0; j < 9; j++){
           if(valores[k].toInt() == 33){
               numbertext[i][j]->setDisabled(false);
               numbertext[i][j]->setText("");
           }else{
               //DESENCRIPTAR PANTILLA DEL SUDOKU
               if((valores[k].toInt())%2 == 0){
                   opera = sqrt(valores[k].toDouble()-cont);
               }else{
                   opera = sqrt(2*(valores[k].toDouble()-cont));
               }
               numbertext[i][j]->setTextColor(Qt::red);
               numbertext[i][j]->setText(QString::number(opera));
               numbertext[i][j]->setDisabled(true);
           }
           numbertext[i][j]->setAlignment(Qt::AlignRight);
           k++;
       }
   }
   ui->textJugador->setText(nombre);
   ui->textJugador->setEnabled(false);
   ui->textNivel->setText(nivel);
   ui->textNivel->setEnabled(false);
   this->show();
}

//COMPRUEBA SI EL JUEGO ES CORRECTO
void sudoku::on_comprobar_clicked(){
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

//SALIR DESDE EL MENU
void sudoku::on_actionQuit_triggered(){
    qApp->quit();
}
//BORRAR JUEGO
void sudoku::on_borrarJuego_clicked(){
    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 9; j++){
            numbertext[i][j]->setText("");
        }
    }
}
//SALIR
void sudoku::on_salir_clicked(){
    this->close();
}
//JUEGO NUEVO
void sudoku::on_nuevoJuego_clicked(){
    int i=0, j=0, k=0, aleatorio;
    QStringList  valores;

    //Semilla del aleatorio
    QTime *seed = new QTime;
    seed->start();
    qsrand(seed->msec());

    QString niveles = ui->textNivel->text();
    if(niveles == "Juvenil"){//MODO JUVENIL(FACIL)}
        k=0;
        valores = plantilla1.split(",");

        for(i = 0;i < 9; i++){
            for(j = 0; j < 9; j++){
                aleatorio = rand() % 10;
                if (aleatorio <= 6){
                    numbertext[i][j]->setTextColor(Qt::red);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setDisabled(true);
                }else{
                    numbertext[i][j]->setDisabled(false);
                    numbertext[i][j]->setText("");
                }

                numbertext[i][j]->setAlignment(Qt::AlignRight);
                k++;
            }
        }
    }else if(niveles == "Profesional"){//MODO PROFESIONAL(MEDIO)
        k=0;
        valores = plantilla2.split(",");

        for(i = 0;i < 9; i++){
            for(j = 0; j < 9; j++){
                aleatorio = rand() % 10;
                if (aleatorio <= 4){
                    numbertext[i][j]->setTextColor(Qt::blue);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setDisabled(true);
                }else{
                    numbertext[i][j]->setDisabled(false);
                    numbertext[i][j]->setText("");
                }
                numbertext[i][j]->setAlignment(Qt::AlignRight);
                k++;
            }
        }
    }else if(niveles == "Experto"){//MODO EXPERTO(DIFICIL)
        k=0;
        valores = plantilla3.split(",");

        for(i = 0;i < 9; i++){
            for(j = 0; j < 9; j++){
                aleatorio = rand() % 10;
                if (aleatorio <= 2){
                    numbertext[i][j]->setTextColor(Qt::red);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setDisabled(true);
                }else{
                    numbertext[i][j]->setDisabled(false);
                    numbertext[i][j]->setText("");
                }
                numbertext[i][j]->setAlignment(Qt::AlignRight);
                k++;
            }
        }
    }
}
//RESOLVER JUEGO
void sudoku::on_resolverJuego_clicked(){
    int i=0, j=0, k=0;
    QStringList  valores;

    QString niveles = ui->textNivel->text();
    k=0;
    if(niveles == "Juvenil"){
        valores = plantilla1.split(",");
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                if(numbertext[i][j]->isEnabled()){
                    numbertext[i][j]->setTextColor(Qt::black);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                }
                k++;
            }
        }
    }else if(niveles == "Profesional"){
        valores = plantilla2.split(",");
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                if(numbertext[i][j]->isEnabled()){
                    numbertext[i][j]->setTextColor(Qt::black);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                }
                k++;
            }
        }
    }else if(niveles == "Experto"){
        valores = plantilla3.split(",");
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                if(numbertext[i][j]->isEnabled()){
                    numbertext[i][j]->setTextColor(Qt::black);
                    numbertext[i][j]->setText(valores[k]);
                    numbertext[i][j]->setAlignment(Qt::AlignRight);
                }
                k++;
            }
        }
    }
}
//CARGAR JUEGO
void sudoku::on_cargarJuego_clicked(){

    CargarSudoku *cargarJuego = new CargarSudoku(this);
    QStringList  valores;

    QString nomJugador, nivelC, datosSudoku;

    QString mFilemane = "guardar.txt";
    QFile mFile(mFilemane);
    mFile.open(QIODevice::Text | QIODevice::ReadOnly);
    if(!mFile.isOpen()){return;}
    QTextStream txtstr(&mFile);
    int cont=0;

    while(!txtstr.atEnd()){
        datosSudoku = txtstr.readLine();
        mFile.flush();
        mFile.close();

        valores = datosSudoku.split("/");
        nomJugador = valores[0];
        nivelC = valores[1];
        datosSudoku = valores[2];
        if(ui->textNivel->text() == nivelC)
            comboB->addItem(nomJugador);
        cont++;
    }

    this->close();
    QString jugador = ui->textJugador->text(), level = ui->textNivel->text();
    cargarJuego->setCombo(comboB, cont,jugador, level);
    cargarJuego->show();
}


/**ENCRIPTAR LA PARTIDA DE SUDOKU*/
void sudoku::encriptarS(){
    int i = 0, j = 0, cont = 33, num1 = 0, numT = 0;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            num1 = (matrizGuardar[i][j].toInt()) * (matrizGuardar[i][j].toInt());

            if((matrizGuardar[i][j].toInt() % 2) == 0)     numT = (num1 / 2) + cont;
            else       numT = num1 + cont;

            matrizGuardar[i][j].setNum(numT);
        }
    }
}
/**GUARDAR JUEGO*/
void sudoku::on_guardarJuego_clicked(){
    QString nomJugador = ui->textJugador->text();
    QString nivel= ui->textNivel->text();
    QString info = "";

    //Actualizar la matriz
    for(int i = 0;i < 9; i++){
        for(int j = 0; j < 9; j++){ matrizGuardar[i][j] = numbertext[i][j]->toPlainText(); }
    }

    encriptarS();
    for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                info = info+matrizGuardar[i][j]+",";
            }
    }
    QString mFilemane = "guardar.txt";
    QFile mFile(mFilemane);
    mFile.open(QIODevice::Text | QIODevice::Append);
    if(!mFile.isOpen()){return;}
    QTextStream txtstr(&mFile);
    txtstr << nomJugador+"/"+nivel+"/"+info+"\n";
    mFile.flush();
    mFile.close();

    QMessageBox::information(this, "Guardar-Sudoku", "La partida ha sido guardada \nEl nombre del jugador :"+nomJugador.toUpper(),"ACEPTAR");
    this->close();
}

/**Funcion de enviar nombre y nivel*/
void sudoku::obtenerNombreNivel(QString nivel, QString nombre){
    nivelSudoku = nivel;
    nombreJugador = nombre;
    
    ui->textJugador->setText(nombre);
    ui->textJugador->setEnabled(false);
    ui->textNivel->setText(nivel);
    ui->textNivel->setEnabled(false);
}


