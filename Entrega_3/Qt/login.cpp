#include "login.h"
#include "ui_login.h"
#include "meli.h"

#include <QMessageBox>
#include <QTimer>
#include <QProcess>
#include <QTextEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login),
    session_url("https://www.frogymd.com.ar/API_ben/API.php?user="),
    login_manager(new QNetworkAccessManager(this)),
    weather_manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    weather_slot_validar_con_API();
    connect(weather_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(weather_slot_descargaFinalizada(QNetworkReply*)));

    connect(ui->submit_pusButton, SIGNAL(pressed()), this, SLOT(login_slot_validar_con_API()));
    connect(login_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(login_slot_descargaFinalizada(QNetworkReply*)));

}


Login::~Login(){
    delete ui;
}

void Login::login_slot_validar_con_API()
{
    session_url += ui->username_lineEdit->text();
    session_url += "&pass=";
    session_url += ui->password_lineEdit->text();
    login_manager->get(QNetworkRequest (QUrl(session_url)));

    qDebug() << "Solicitud de login enviada";
}

void Login::weather_slot_validar_con_API()
{
    QString weather_url = "https://api.openweathermap.org/data/2.5/weather?lat=-31.420082&lon=-64.188774&appid=e8764325548bedbb4c1c79da96558946&units=metric&lang=es&mode=html";
    weather_manager->get(QNetworkRequest(QUrl(weather_url)));

    qDebug() << "Solicitud de weather enviada";
}

void Login::login_slot_descargaFinalizada(QNetworkReply* reply)
{
    QString ba = (QString)reply->readAll();
    QMessageBox ingreso_mb;

    if (ba.contains("Bienvenido/a")){

        hide();
        meli* m = new meli(nullptr,session_url);
        //m->setWindowState(Qt::WindowFullScreen);
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
