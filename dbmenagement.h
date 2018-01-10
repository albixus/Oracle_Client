#ifndef DBMENAGEMENT_H
#define DBMENAGEMENT_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>

//made to use db in diffrent windows easier
class dbMenagement
{
public:

    dbMenagement();

    ~dbMenagement();

    bool open();

    bool query_execute(QString query_string);

    //use only when you are making SELECT queries
    QSqlQuery select_query_execute(QString query_string);

private:
    QSqlDatabase db;

private:
    bool create_tables();

    bool create_sequences();

    void drop_all_tables();

};

#endif // DBMENAGEMENT_H
