#ifndef LOGIN_H
#define LOGIN_H
#include "admin_usuarios_db.h"
#include <QWidget>
#include <QString>
#include <QNetworkAccessManager> //Para ejecutar solicitudes GET, POST, etc
#include <QNetworkRequest> //Contiene la info que ira al server
#include <QNetworkReply> // Contiene la info que proviene del server
#include <QSqlQuery>
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
    QString session_url;
    QNetworkAccessManager* login_manager;
    QNetworkAccessManager* weather_manager;
    admin_usuarios_db* usuarios_db;

    void login_guardar_usuarios_db();
    bool usuario_existe(QString username, QString password);

private slots:
    void login_slot_validar_con_API();

    void weather_slot_validar_con_API();
        //Solicitud para el servidor web

    void login_slot_descargaFinalizada(QNetworkReply* reply);
        // Se ejecuta cuando la respuesta llega aca, es toda la info que mando el server
    void weather_slot_descargaFinalizada(QNetworkReply* w_reply);

    void login_slot_insertar_password();

};

#endif // LOGIN_H
