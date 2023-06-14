#include "meli.h"
#include "ui_meli.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QPixmap>

meli::meli(QWidget *parent, QString session_url) :
    QWidget(parent),
    ui(new Ui::meli),
    meli_manager_realizar_busqueda(new QNetworkAccessManager),
    meli_manager_obtener_ultima_busqueda(new QNetworkAccessManager),
    meli_manager_guardar_ultima_busqueda(new QNetworkAccessManager),
    meli_manager_obtener_imagen(new QNetworkAccessManager),
    ultima_busqueda_url(session_url),
    iterador(0),
    imagenes_producto_url({"1","2","3","4","5"})
{
    ui->setupUi(this);

    meli_manager_obtener_ultima_busqueda->get(QNetworkRequest(QUrl(ultima_busqueda_url))); // Consulta la ultima busqueda realizada
    connect(meli_manager_obtener_ultima_busqueda,SIGNAL(finished(QNetworkReply*)),this,SLOT(meli_slot_obtener_ultima_busqueda_descarga_finalizada(QNetworkReply*)));
    //Obtiene la ultima busqueda realizada
    connect(meli_manager_obtener_ultima_busqueda,SIGNAL(finished(QNetworkReply*)),this,SLOT(meli_slot_realizar_busqueda()));
    //Realiza la busqueda de la ultima busqueda

    connect(ui->pb_meli,SIGNAL(pressed()),this,SLOT(meli_slot_realizar_busqueda()));
    //Obtiene una busqueda hecha por el ususario
    connect(meli_manager_realizar_busqueda,SIGNAL(finished(QNetworkReply*)),this,SLOT(meli_slot_realizar_busqueda_descarga_finalizada(QNetworkReply*)));
    //Realiza la busqueda

    connect(meli_manager_obtener_imagen,SIGNAL(finished(QNetworkReply*)),this,SLOT(meli_slot_obtener_imagen_descarga_realizada(QNetworkReply*)));
}

meli::~meli()
{
    delete ui;
}

void meli::meli_guardar_ultima_busqueda(QString busqueda_url, QString producto)
{
    busqueda_url += "&l_search=";
    busqueda_url += producto;

    qDebug() << "meli_guaradar ultima busqueda\n" << busqueda_url;
    meli_manager_guardar_ultima_busqueda->get(QNetworkRequest(QUrl(busqueda_url)));
}

void meli::meli_set_datos_producto(QJsonArray results_array)
{
    if(!results_array.isEmpty())
    {
        QLabel* productos[] = {ui->label_producto_1, ui->label_producto_2, ui->label_producto_3, ui->label_producto_4, ui->label_producto_5};

        for (int i = 0; i<=4; i++)
        {
            QJsonObject results_object = results_array[i].toObject();
            QJsonObject results_object_seller = results_object["seller"].toObject();
            QJsonObject results_object_seller_address = results_object["seller_address"].toObject();
            QJsonObject results_object_seller_address_state = results_object_seller_address["state"].toObject();

            QString results_title = results_object["title"].toString();
            QString results_seller_nickname = results_object_seller["nickname"].toString();
            QString results_permalink = results_object["permalink"].toString();
            QString results_seller_address_state_name = results_object_seller_address_state["name"].toString();
            double results_price = results_object["price"].toDouble();


            QString datos_producto = "Producto: " + results_title + "\n" +
                                     "Precio: $" +  QString::number(results_price) + "\n"
                                     "Vendedor: " + results_seller_nickname + "\n"
                                     "Ubicacion: " + results_seller_address_state_name + "\n";


            productos[i]->setText(datos_producto);


            qDebug() << results_title << "\n" << results_price << "\n" << results_seller_nickname<< "\n" << results_seller_address_state_name << "\n" << results_permalink << "\n";
        }
    }

}

void meli::meli_set_imagen_producto(QJsonArray results_array)
{
    if(!results_array.isEmpty())
    {
        for(int i=0; i<=4; i++)
        {
            QJsonObject results_object = results_array[i].toObject();
            QString results_thumbnail = results_object["thumbnail"].toString();
            imagenes_producto_url.replace(i,results_thumbnail);

            qDebug() << imagenes_producto_url.at(i) << "\n";
        }

        meli_manager_obtener_imagen->get(QNetworkRequest(QUrl(imagenes_producto_url.at(iterador))));
    }


}


void meli::meli_slot_realizar_busqueda()
{
    QString producto = ui->le_meli->text();

    if(!producto.isEmpty())
    {
        QString meli_url = "https://api.mercadolibre.com/sites/MLA/search?&q=";
        meli_url += producto;
        meli_url += "&sort=price_asc";

        meli_manager_realizar_busqueda->get(QNetworkRequest(QUrl(meli_url)));

        meli_guardar_ultima_busqueda(ultima_busqueda_url,producto);

        qDebug() << "Solicitud de meli enviada";
    }

}

void meli::meli_slot_obtener_ultima_busqueda_descarga_finalizada(QNetworkReply *m_oub_reply)
{
    QString meli_ultima_busqueda_reply = (QString)m_oub_reply->readAll();

    QStringList lista = meli_ultima_busqueda_reply.split(".");
    this->setWindowTitle(lista.value(0));

    if(!lista.value(1).isEmpty())
    {
        QString ultima_busqueda = lista.value(1);


        qDebug() << "meli_slot_ultima_busqueda_descarga_finalizada\n";

        qDebug() << meli_ultima_busqueda_reply;

        ui->le_meli->setText(ultima_busqueda);
    }
}

void meli::meli_slot_realizar_busqueda_descarga_finalizada(QNetworkReply *m_rb_reply)
{
    QString meli_reply = (QString)m_rb_reply->readAll();



    QJsonDocument json_doc = QJsonDocument::fromJson(meli_reply.toUtf8());
    QJsonObject main_obj = json_doc.object();
    QJsonArray results_array = main_obj["results"].toArray();

    meli_set_datos_producto(results_array);
    meli_set_imagen_producto(results_array);
}

void meli::meli_slot_obtener_imagen_descarga_realizada(QNetworkReply *m_oi_reply)
{
    QLabel* imagenes_producto[] = {ui->label_imagen_producto_1, ui->label_imagen_producto_2, ui->label_imagen_producto_3, ui->label_imagen_producto_4, ui->label_imagen_producto_5};

    QByteArray imagen_producto_descargada = m_oi_reply->readAll();
    QPixmap imagen_producto;
    imagen_producto.loadFromData(imagen_producto_descargada);

    imagenes_producto[iterador]->setPixmap(imagen_producto.scaled(200,200));
    //imagenes_producto[iterador]->setScaledContents(true);

    iterador++;

    if(iterador <= 4)
    {
        meli_manager_obtener_imagen->get(QNetworkRequest(QUrl(imagenes_producto_url.at(iterador))));
    }
    else
    {
        iterador = 0;
    }


}







