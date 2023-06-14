
#include "login.h"
#include "ui_login.h"

#include <QMessageBox>
#include <QTextEdit>


Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login),
    manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    connect(ui->submit_pusButton, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));
}


Login::~Login(){
    delete ui;
}

void Login::slot_validar_con_API(){
    QString sUrl = "http://localhost/POO/API/API.php?user=";
    sUrl += ui->username_lineEdit->text();
    sUrl += "&pass=";
    sUrl += ui->password_lineEdit->text();

    manager->get(QNetworkRequest (QUrl(sUrl)));

    qDebug() << "Solicitud enviada";
}


void Login::slot_descargaFinalizada(QNetworkReply* reply){

    QByteArray ba = reply->readAll();
    QMessageBox ingreso_mb;
    QTextEdit html_te = QTextEdit(&ingreso_mb);

    ingreso_mb.setStyleSheet("QTextEdit{min-width:800px; min-height:500px;} QLabel{min-width:760px; min-height:500px;}");

    ingreso_mb.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //html_te.setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    qDebug() << ba;

    if (ba == "Acceso concedido"){
        const QString html_text = "<!DOCTYPE html><html><head><title>Trabajo exploratorio</title></head><body><h1>Qt Location API</h1><p>Esta API posee una librería para mapeado, navegación e información de lugares.</p><p>La API de Qt Location provee al desarrollador con un set de funciones para interactuar con mapas, datos de navegación y puntos de interés.</p><p>Con Maps API podemos asociar una posición en un mapa en varios formatos suplidos por el backend. Luego Places API se puede usar para marcar lugares en el mapa o incluso determinar la posición actual como punto de interés y asociarla con un ícono.</p><h1>Mapas y navegación</h1><p>A través de del módulo QtQuick se pueden mostrar información geográfica en un mapa, asi así como permitir al usuario interactuar con el mismo. También contiene utilidades para geocodificación (encontrar una coordenada geográfica de una dirección de una calle) y navegación (direcciones para peatones como para conductores).</p><h1>Enrutamiento y navegación</h1><p>El enrutamiento es la determinación de una ruta navegable de un punto a otro en un mapa. Dado un mapa que es consciente de las características que ayudan o dificultan la navegación, como puentes, vías fluviales, etc., se puede construir una serie de segmentos que componen el viaje. Si estos segmentos de ruta son simples, podemos agregar información de navegación en los puntos de conexión, maniobras de ruta, entre los segmentos.</p></body></html>";
        html_te.setText(html_text);
        ingreso_mb.exec();
    }
    else{

        const QString text = "<h3>Usuario y/o contraseña incorrecta</h3>";
        html_te.setText(text);
        ingreso_mb.exec();

    }


}
