
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>
#include <QNetworkAccessManager> //Para ejecutar solicitudes GET, POST, etc
#include <QNetworkRequest> //Contiene la info que ira al server
#include <QNetworkReply> // Contiene la info que proviene del server
#include <QUrl>



QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget

{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login* ui;
    QNetworkAccessManager* manager;

private slots:
    void slot_validar_con_API();
        //Solicitud para el servidor web


    void slot_descargaFinalizada(QNetworkReply* reply);
        // Se ejecuta cuando la respuesta llega aca, es toda la info que mando el server

};

#endif // LOGIN_H
