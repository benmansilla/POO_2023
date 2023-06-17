#ifndef ADMIN_USUARIOS_DB_H
#define ADMIN_USUARIOS_DB_H

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class admin_usuarios_db : public QObject
{
    Q_OBJECT

public:
    admin_usuarios_db();
    bool conectar(QString archivo_sqlite);
    QSqlDatabase get_db();
private:

    QSqlDatabase db;



};

#endif // ADMIN_USUARIOS_DB_H
