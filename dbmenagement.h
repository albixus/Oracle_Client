#ifndef DBMENAGEMENT_H
#define DBMENAGEMENT_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>

class dbMenagement
{
public:
    dbMenagement();
    ~dbMenagement();
    bool open();
    bool query_execute(QString query_string);
    bool create_tables();
    bool create_sequences();
    void drop_all_tables();
    QSqlQuery select_query_execute(QString query_string);
private:
    QSqlDatabase db;

};

#endif // DBMENAGEMENT_H
