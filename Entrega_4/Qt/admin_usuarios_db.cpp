#include "admin_usuarios_db.h"

admin_usuarios_db::admin_usuarios_db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");

}

bool admin_usuarios_db::conectar(QString archivo_sqlite)
{

    db.setDatabaseName(archivo_sqlite);

    if(db.open())
    {
        return true;
    }

    return false;
}

QSqlDatabase admin_usuarios_db::get_db(){
    return db;
}
