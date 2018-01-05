#ifndef DBMENAGEMENT_H
#define DBMENAGEMENT_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>


class dbMenagement
{
public:
    dbMenagement(QString connection_string);
    ~dbMenagement();
private:
    QSqlDatabase db;
};

#endif // DBMENAGEMENT_H
