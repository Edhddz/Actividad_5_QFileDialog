#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    bool datosCorrectos();
};
#endif // MAINWINDOW_H

class Neurona
{
    int id;
    float voltaje;
    int posicion_x;
    int posicion_y;
    int red;
    int green;
    int blue;

public:
    Neurona(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red, int& green,
            int& blue);

    void setId(int id){this->id = id;}
    int getId(){return id;}

    void setVoltaje(float voltaje){this->voltaje = voltaje;}
    float getVoltaje(){return voltaje;}

    void setPosicionX(int posicion_x){this->posicion_x = posicion_x;}
    int getPosicionX(){return posicion_x;}

    void setPosicionY(int posicion_y){this->posicion_y = posicion_y;}
    int getPosicionY(){return posicion_y;}

    void setRed(int red){this->red = red;}
    int getRed(){return red;}

    void setGreen(int green){this->green = green;}
    int getGreen(){return green;}

    void setBlue(int blue){this->blue = blue;}
    int getBlue(){return blue;}

    std::string printNeurona();
    std::string getInfoNeurona();
};

class Nodo
{
public:
    Neurona* neurona;
    Nodo* siguiente;
};

class AdministradoraNeurona
{
    Nodo* inicio;
    int contadorNeuronas = 0;

public:
    void agregarInicio(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red,
                       int& green, int& blue);
    void agregarFinal(int& id, float& voltaje, int& posicion_x, int& posicion_y, int& red,
                      int& green, int& blue);
    void setContadorNeuronas(int& contador);
    std::string mostrar();
    QString guardarNeuronas();
    QString cargarNeuronas();
};
