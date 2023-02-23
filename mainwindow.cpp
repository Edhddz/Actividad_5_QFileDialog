#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

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


Neurona::Neurona(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green, int& blue)
{
    if(id > 0){this->setId(id);}
    if(voltaje > 0){this->setVoltaje(voltaje);}
    if(posicion_x > 0){this->setPosicionX(posicion_x);}
    if(posicion_y > 0){this->setPosicionY(posicion_y);}
    if(red > 0){this->setRed(red);}
    if(green > 0){this->setGreen(green);}
    if(blue > 0){this->setBlue(blue);}
}

void Neurona::printNeurona()
{
    std::cout << "ID: " << this->getId() <<std::endl
              << "Voltaje: " << this->getVoltaje() <<std::endl
              << "Posicion X: " << this->getPosicionX() <<std::endl
              << "Posicion Y: " << this->getPosicionY() <<std::endl
              << "Red: " << this->getRed() <<std::endl
              << "Green: " << this->getGreen() <<std::endl
              << "Blue: " << this->getBlue() <<std::endl <<std::endl;
}

void AdministradoraNeurona::agregarInicio(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green, int& blue)
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
}
void AdministradoraNeurona::agregarFinal(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green, int& blue)
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
}
void AdministradoraNeurona::mostrar()
{
    Nodo* nodoTemporal = inicio;
    while (nodoTemporal != NULL) {
        nodoTemporal->neurona->printNeurona();
    }
}
