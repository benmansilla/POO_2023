
#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login),
    manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);



    connect(ui->submit_pusButton, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));
}


Login::~Login()
{
    delete ui;
}

void Login::slot_validar_con_API(){
    QString sUrl = "https://www.frogymd.com.ar/API_ben/API.php?user=";
    sUrl += ui->username_lineEdit->text();
    sUrl += "&pass=";
    sUrl += ui->password_lineEdit->text();

    manager->get(QNetworkRequest (QUrl(sUrl)));

    qDebug() << "Solicitud enviada";
}


void Login::slot_descargaFinalizada(QNetworkReply* reply){

    QByteArray ba = reply->readAll();
    qDebug() << ba;

}
