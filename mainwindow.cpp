#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QString>
#include <fstream>
#include <QFileDialog>

#define NOMBRE_ARCHIVO "Neuronas.txt"
#define DELIMITADOR_CAMPO '|'
#define DELIMITADOR_REGISTRO '\n'

QString input;
AdministradoraNeurona admiNeurona;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Métodos CLase Nerona
Neurona::Neurona(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green,
                 int& blue)
{
    if(id > 0){this->setId(id);}
    if(voltaje > 0){this->setVoltaje(voltaje);}
    if(posicion_x > 0){this->setPosicionX(posicion_x);}
    if(posicion_y > 0){this->setPosicionY(posicion_y);}
    if(red > 0){this->setRed(red);}
    if(green > 0){this->setGreen(green);}
    if(blue > 0){this->setBlue(blue);}
}
std::string Neurona::printNeurona()
{
    std::stringstream ss;
    ss <<  "ID: " << this->getId() <<std::endl
       << "Voltaje: " << this->getVoltaje() <<std::endl
       << "Posicion X: " << this->getPosicionX() <<std::endl
       << "Posicion Y: " << this->getPosicionY() <<std::endl
       << "Red: " << this->getRed() <<std::endl
       << "Green: " << this->getGreen() <<std::endl
       << "Blue: " << this->getBlue() <<std::endl <<std::endl;

    return ss.str();
}
std::string Neurona::getInfoNeurona()
{
    std::stringstream ss;

    ss << this->getId() << DELIMITADOR_CAMPO << this->getVoltaje() << DELIMITADOR_CAMPO
       << this->getPosicionX() << DELIMITADOR_CAMPO << this->getPosicionY() << DELIMITADOR_CAMPO
       << this->getRed() << DELIMITADOR_CAMPO << this->getGreen() << DELIMITADOR_CAMPO
       << this->getBlue() << DELIMITADOR_REGISTRO;

    return ss.str();
}

//Métodos Clase AdministradoraNeurona
void AdministradoraNeurona::agregarFinal(int& id, float& voltaje, int& posicion_x, int& posicion_y,
                                          int& red, int& green, int& blue)
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->neurona = new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue);
    nuevoNodo->siguiente = NULL;

    if(inicio == NULL){inicio = nuevoNodo;}
    else
    {
        Nodo* temp = inicio;
        while (temp->siguiente != NULL){temp = temp->siguiente;}
        temp->siguiente = nuevoNodo;
    }
    contadorNeuronas++;
}
void AdministradoraNeurona::agregarInicio(int& id, float& voltaje, int& posicion_x, int& posicion_y,
                                         int& red, int& green, int& blue)
{
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->neurona = new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue);
    nuevoNodo->siguiente = NULL;

    if(inicio == NULL){inicio = nuevoNodo;}
    else
    {
        nuevoNodo->siguiente = inicio;
        inicio = nuevoNodo;
    }
    contadorNeuronas++;
}
std::string AdministradoraNeurona::mostrar()
{
    std::stringstream ss;
    int contadorNeuronas = 0;

    Nodo* nodoTemporal = inicio;
    while (nodoTemporal != NULL) {
        ss << nodoTemporal->neurona->printNeurona();
        contadorNeuronas++;
        nodoTemporal = nodoTemporal->siguiente;
    }
    if(contadorNeuronas > 0)
    {
        return ss.str();
    }
    else
        return "No hay neuronas registradas";

}

void AdministradoraNeurona::setContadorNeuronas(int& contador)
{
    contadorNeuronas = contador;
}

QString AdministradoraNeurona::guardarNeuronas()
{
    std::ofstream archivoNeuronas;
    std::stringstream ss;

    if(contadorNeuronas > 0)
    {
        archivoNeuronas.open(NOMBRE_ARCHIVO, std::ios::out);
        if(archivoNeuronas.is_open())
        {
            Nodo* nodoTemporal = inicio;
            ss << contadorNeuronas << DELIMITADOR_CAMPO;
            for(int i = 0; i<contadorNeuronas && nodoTemporal != NULL; i++)
            {
                ss << nodoTemporal->neurona->getInfoNeurona();
                nodoTemporal = nodoTemporal->siguiente;
            }
            archivoNeuronas << ss.str();
            ss.str(std::string()); //Vacía el contenido del Stringstream
            ss << "Neuronas registradas en el archivo " << NOMBRE_ARCHIVO;

            return QString::fromStdString(ss.str());
        }
        else {ss.str(std::string()); ss << "No fue posible abrir el archivo...";}
        archivoNeuronas.close();
    }
    else{ss << "No hay Neuronas registradas";}

    return QString::fromStdString(ss.str());
}

QString AdministradoraNeurona::cargarNeuronas()
{
    std::ifstream archivoNeuronas;
    int contadorNeuronas, id, pos_X, pos_Y, red, green, blue, pos;
    float voltaje;
    char delimCampo;
    std::string cadena, subcadena;

    QString fName = QFileDialog::getOpenFileName();

    archivoNeuronas.open(fName.toStdString());
    if(archivoNeuronas)
    {
        archivoNeuronas >> contadorNeuronas;
        archivoNeuronas >> delimCampo;
        admiNeurona.setContadorNeuronas(contadorNeuronas);
        for(int i = 0; i < contadorNeuronas; i++)
        {
            std::getline(archivoNeuronas, cadena);

            pos = cadena.find_first_of(DELIMITADOR_CAMPO, 0);
            subcadena = cadena.substr(0, pos);
            id = std::stoi(subcadena);
            cadena = cadena.substr(pos+1);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO, 0);
            subcadena = cadena.substr(0, pos);
            voltaje = std::stof(subcadena);
            cadena = cadena.substr(0, pos);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(0, pos);
            pos_X = std::stoi(subcadena);
            cadena = cadena.substr(0, pos);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(0, pos);
            pos_Y = std::stoi(subcadena);
            cadena = cadena.substr(0, pos);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(0, pos);
            red = std::stoi(subcadena);
            cadena = cadena.substr(0, pos);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(0, pos);
            green = std::stoi(subcadena);
            cadena = cadena.substr(0, pos);
            pos = cadena.find_first_of(DELIMITADOR_CAMPO);
            subcadena = cadena.substr(0, pos);
            blue = std::stoi(subcadena);

            admiNeurona.agregarInicio(id, voltaje, pos_X, pos_Y, red, green, blue);
        }

        return "Se han cargado las neuronas desde el archivo";
    }
    else {
        return "No se abrio el archivo";
    }
}

//Interacción con la interfaz
void MainWindow::on_pushButton_2_clicked() //Recupera la información de los LineTextEdit
{
    int id, posX, posY, r, g, b;
    float voltaje;
    bool dataError;

    ui->lineEdit->setInputMask(0000); //Establece un InputMask para aceptar número únicamente
    ui->lineEdit_2->setInputMask(0000);
    ui->lineEdit_3->setInputMask(0000);
    ui->lineEdit_4->setInputMask(0000);
    ui->lineEdit_5->setInputMask(0000);
    ui->lineEdit_6->setInputMask(0000);
    ui->lineEdit_7->setInputMask(0000);

    if(datosCorrectos())
    {
        id = ui->lineEdit->text().toInt(); //ID
        voltaje = ui->lineEdit_2->text().toFloat(); //Voltaje
        posX = ui->lineEdit_3->text().toInt(); //Posicion X
        posY = ui->lineEdit_4->text().toInt(); //Posicion Y
        r = ui->lineEdit_5->text().toInt(); //Color Rojo
        g = ui->lineEdit_6->text().toInt(); //Color Verde
        b = ui->lineEdit_7->text().toInt(); //Color Azul

        if(ui->radioButton->isChecked())
        {
            admiNeurona.agregarInicio(id, voltaje, posX, posY, r, g, b);
            ui->plainTextEdit->insertPlainText("Neurona creada!\n");
        }
        else if(ui->radioButton_2->isChecked())
        {
            admiNeurona.agregarFinal(id, voltaje, posX, posY, r, g, b);
            ui->plainTextEdit->insertPlainText("Neurona creada!\n");
        }
        else
        {
            ui->plainTextEdit->insertPlainText("Selecciona la ubicación en la que deseas guardar la "
                                               "neurona");
        }
    }
    else {
        ui->plainTextEdit->setPlainText("Verifica la información, sólo se aceptan números...");
    }

}

void MainWindow::on_pushButton_clicked() //Botón Mostrar Neuronas
{
    ui->plainTextEdit->setPlainText(QString::fromStdString(admiNeurona.mostrar()));
}

void MainWindow::on_pushButton_3_clicked() //Borra el contenido de los campos LineTextEdit
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

bool MainWindow::datosCorrectos() //Verifica que los valores ingresados sean todos válidos, numéricos en éste caso
{
    if(ui->lineEdit->hasAcceptableInput() && ui->lineEdit_2->hasAcceptableInput() &&
       ui->lineEdit_3->hasAcceptableInput() && ui->lineEdit_4->hasAcceptableInput() &&
       ui->lineEdit_5->hasAcceptableInput() && ui->lineEdit_6->hasAcceptableInput() &&
       ui->lineEdit_7->hasAcceptableInput()) return true;
    else {
        return false;
    }
}

void MainWindow::on_pushButton_4_clicked() //Botón de Respaldar Neuronas
{
    ui->plainTextEdit->setPlainText(admiNeurona.guardarNeuronas());
}

void MainWindow::on_pushButton_5_clicked() //Botón de Cargar Neuronas
{
    ui->plainTextEdit->setPlainText(admiNeurona.cargarNeuronas());
}

