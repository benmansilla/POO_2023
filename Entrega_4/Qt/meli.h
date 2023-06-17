#ifndef MELI_H
#define MELI_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QStringList>


namespace Ui {
class meli;
}

class meli : public QWidget
{
    Q_OBJECT

public:
    meli(QWidget *parent, QString session_url);
    ~meli();

private:
    Ui::meli *ui;
    QNetworkAccessManager* meli_manager_realizar_busqueda;
    QNetworkAccessManager* meli_manager_obtener_ultima_busqueda;
    QNetworkAccessManager* meli_manager_guardar_ultima_busqueda;
    QNetworkAccessManager* meli_manager_obtener_imagen;

    QString ultima_busqueda_url;
    int iterador;
    QStringList imagenes_producto_url;

    void meli_guardar_ultima_busqueda(QString busqueda_url, QString producto);
    void meli_set_datos_producto(QJsonArray results_array);
    void meli_set_imagen_producto(QJsonArray results_array);
    void meli_obetener_imagenes_url_producto(QJsonArray results_array);
    void meli_obtener_imagen(QStringList imagenes_url);

private slots:
    void meli_slot_realizar_busqueda();
    void meli_slot_obtener_ultima_busqueda_descarga_finalizada(QNetworkReply* m_oub_reply);
    void meli_slot_realizar_busqueda_descarga_finalizada(QNetworkReply* m_rb_reply);
    void meli_slot_obtener_imagen_descarga_realizada(QNetworkReply* m_oi_reply);



};

#endif // MELI_H
