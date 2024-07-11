#include "login.h"
#include "ui_login.h"
#include "meli.h"

#include <QMessageBox>
#include <QTextEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>



Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login),
    login_manager(new QNetworkAccessManager(this)),
    weather_manager(new QNetworkAccessManager(this)),
    usuarios_db(new admin_usuarios_db())
{
    ui->setupUi(this);

    weather_slot_validar_con_API();
    connect(weather_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(weather_slot_descargaFinalizada(QNetworkReply*)));

    connect(ui->submit_pusButton, SIGNAL(pressed()), this, SLOT(login_slot_validar_con_API()));
    connect(login_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(login_slot_descargaFinalizada(QNetworkReply*)));
    connect(ui->username_lineEdit,SIGNAL(editingFinished()),this,SLOT(login_slot_insertar_password()));

}


Login::~Login(){
    delete ui;
}

bool Login::usuario_existe(QString username, QString password)
{
    usuarios_db->conectar("D:/sqlite/usuarios_guardados.db");
    QSqlQuery query_usuarios(usuarios_db->get_db());
    query_usuarios.prepare("SELECT username, password FROM usuarios");

    if(query_usuarios.exec())
    {
        while(query_usuarios.next())
        {
            if(query_usuarios.value("username") == username && query_usuarios.value("password") == password)
            {
                return true;
            }
        }
    }
    else
    {
        qDebug() << "No se ha podido verificar si el usuario existe";
    }

    usuarios_db->get_db().close();

    qDebug() << "El usuario ya existe en la base de datos\n";

    return false;

}

void Login::login_guardar_usuarios_db()
{
    QString username = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    if (!usuario_existe(username, password))
    {
        usuarios_db->conectar("D:/sqlite/usuarios_guardados.db");
        QSqlQuery query_usuarios(usuarios_db->get_db());
        query_usuarios.prepare("INSERT INTO usuarios (username, password) VALUES (:username, :password)");
        query_usuarios.bindValue(":username", username);
        query_usuarios.bindValue(":password", password);

        if (query_usuarios.exec())
        {
            qDebug() << "Usuario guardado exitosamente.";
        }
        else
        {
            qDebug() << "Error al guardar el usuario";
        }

        qDebug() << "Username:" << username;
        qDebug() << "Password:" << password;

        usuarios_db->get_db().close();
    }
}




void Login::login_slot_validar_con_API()
{
    session_url = "https://www.frogymd.com.ar/API_ben/API.php?user=";

    session_url += ui->username_lineEdit->text();
    session_url += "&pass=";
    session_url += ui->password_lineEdit->text();
    login_manager->get(QNetworkRequest (QUrl(session_url)));

    qDebug() << "Solicitud de login enviada";
}

void Login::weather_slot_validar_con_API()
{
    QString weather_url = "https://api.openweathermap.org/data/2.5/weather?lat=-31.420082&lon=-64.188774&appid={API_KEY}&units=metric&lang=es&mode=html";
    weather_manager->get(QNetworkRequest(QUrl(weather_url)));

    qDebug() << "Solicitud de weather enviada";
}
void Login::login_slot_descargaFinalizada(QNetworkReply* reply)
{
    QString ba = (QString)reply->readAll();
    QMessageBox ingreso_mb;

    if (ba.contains("Bienvenido/a"))
    {
       hide();

        if(ui->rememberMe_checkBox->isChecked())
        {
            login_guardar_usuarios_db();
        }

        meli* m = new meli(nullptr,session_url);
        m->show();
    }
    else
    {
        ingreso_mb.setText(ba);
        ingreso_mb.exec();

    }
}

void Login::weather_slot_descargaFinalizada(QNetworkReply* w_reply)
{
    QString weather_reply = (QString)w_reply->readAll();

    ui->weather_textEdit->setHtml(weather_reply);

}

void Login::login_slot_insertar_password()
{
    //Hacer la consulta de a la base de datos de si el checkbox estaba marcado para este usuario
    //si si se ejecuta esta funcin si no no

    QString username = ui->username_lineEdit->text();


    usuarios_db->conectar("D:/sqlite/usuarios_guardados.db");

    QSqlQuery query_usuarios(usuarios_db->get_db());
    query_usuarios.prepare("SELECT password FROM usuarios WHERE username = :username");
    query_usuarios.bindValue(":username", username);


    if (query_usuarios.exec() && query_usuarios.next())
    {

        QString password = query_usuarios.value("password").toString();
        qDebug() << password;
        ui->password_lineEdit->setText(password);

    }
    else
    {
        qDebug() << "Fallo en la conexion";
    }

    usuarios_db->get_db().close();
}

