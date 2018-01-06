#include "dbmenagement.h"
#include <QMessageBox>

dbMenagement::dbMenagement()
{
    db = QSqlDatabase::addDatabase("QOCI");
    db.setHostName("localhost");
    db.setUserName("test");
    db.setPassword("test");
    db.setPort(1521);
    db.setDatabaseName("XE");
}

dbMenagement::~dbMenagement()
{
    db.close();
    QSqlDatabase::removeDatabase("XE");
}

bool dbMenagement::open()
{
    return db.open();
}

bool dbMenagement::query_execute(QString query_string)
{
    QSqlQuery query;
    return query.exec(query_string);
}

bool dbMenagement::create_sequences()
{
       QSqlQuery sequence_query;
       bool status = true;

       if(!sequence_query.exec("CREATE SEQUENCE pasazer_seq"))
            status = false;

        if(!sequence_query.exec("CREATE SEQUENCE pracownik_seq"))
            status = false;

       if(!sequence_query.exec("CREATE SEQUENCE pociag_seq"))
           status = false;

       if(!sequence_query.exec("CREATE SEQUENCE stacja_seq;"))
           status = false;

       if(!sequence_query.exec("CREATE SEQUENCE przedzial_seq"))
           status = false;

       if(!sequence_query.exec("CREATE SEQUENCE polaczenie_seq"))
           status = false;

       if(!sequence_query.exec("CREATE SEQUENCE bilet_seq"))
           status = false;

       return status;
}

void dbMenagement::drop_all_tables()
{
    QSqlQuery drop_query;

    drop_query.exec("DROP TABLE Pasazer CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Pracownik CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Pociag CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Stacja CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Przedzial CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Polaczenie CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Bilet CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Trasa CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Przystanek CASCADE CONSTRAINTS");
    drop_query.exec("DROP TABLE Pracownik_Pociagu CASCADE CONSTRAINTS");
}

QSqlQuery dbMenagement::select_query_execute(QString query_string)
{
    QSqlQuery query;
    query.prepare(query_string);
    query.exec();

    return query;
}

bool dbMenagement::create_tables()
{
    QSqlQuery create_query;
    bool status = true;

    if(!create_query.exec("CREATE TABLE Pasazer(\
                          ID_Pasazer NUMBER(6) CONSTRAINT Pasazer_pk PRIMARY KEY,\
                          Imie VARCHAR2(50) NOT NULL,\
                          Nazwisko VARCHAR2(50) NOT NULL,\
                          Numer_telefonu VARCHAR2(15))"))
       status=false;

    if(!create_query.exec("CREATE TABLE Pracownik(\
                          ID_Pracownik NUMBER(6) CONSTRAINT Pracownik_pk PRIMARY KEY,\
                          Imie VARCHAR2(50) NOT NULL,\
                          Nazwisko VARCHAR2(50) NOT NULL,\
                          Pensja NUMBER(7))"))
       status=false;

     if(!create_query.exec("CREATE TABLE Pociag(\
                           ID_Pociag NUMBER(6) CONSTRAINT Pociag_pk PRIMARY KEY,\
                           Ilosc_wagonow NUMBER(2),\
                           Nazwa VARCHAR2(50) NOT NULL UNIQUE,\
                           Data_Produkcji DATE NOT NULL)"))
        status=false;

     if(!create_query.exec("CREATE TABLE Stacja(\
                           ID_Stacja NUMBER(6) CONSTRAINT Stacja_pk PRIMARY KEY,\
                           Nazwa VARCHAR2(50) NOT NULL)"))
        status=false;

     if(!create_query.exec("CREATE TABLE Przedzial(\
                           ID_Przedzial NUMBER(6) CONSTRAINT Przedzial_pk PRIMARY KEY,\
                           ID_Pociag NUMBER(6) CONSTRAINT Przedzial_fk REFERENCES Pociag(ID_Pociag)\
                           )"))
        status=false;

     if(!create_query.exec("CREATE TABLE Polaczenie(\
                           ID_Polaczenie NUMBER(6) CONSTRAINT Polaczenie_pk PRIMARY KEY,\
                           Miejsce_Docelowe VARCHAR2(50) NOT NULL,\
                           Miejsce_Wyjazdu VARCHAR2(50) NOT NULL)"))
        status=false;

     if(!create_query.exec("CREATE TABLE Bilet(\
                          ID_Bilet NUMBER(6) CONSTRAINT Bilet_pk PRIMARY KEY,\
                          Data_Wyjazdu DATE NOT NULL,\
                          Data_Przyjazdu DATE NOT NULL,\
                          Numer_Miejsca NUMBER(3) NOT NULL,\
                          ID_Pasazer NUMBER(6) CONSTRAINT Bilet_fk1 REFERENCES Pasazer(ID_Pasazer),\
                          ID_Pracownik NUMBER(6) CONSTRAINT Bilet_fk2 REFERENCES Pracownik(ID_Pracownik),\
                          ID_Polaczenie NUMBER(6) CONSTRAINT Bilet_fk3 REFERENCES Polaczenie(ID_Polaczenie),\
                          ID_Przedzial NUMBER(6) CONSTRAINT Bilet_fk4 REFERENCES Przedzial(ID_Przedzial))"))
         status=false;

    if(!create_query.exec("CREATE TABLE Trasa(\
                          ID_Polaczenie NUMBER(6) CONSTRAINT Trasa_fk1 REFERENCES Polaczenie(ID_Polaczenie),\
                          ID_Pociag NUMBER(6) CONSTRAINT Trasa_fk2 REFERENCES Pociag(ID_Pociag),\
                          PRIMARY KEY(ID_Polaczenie,ID_Pociag))"))
        status=false;

    if(!create_query.exec("CREATE TABLE Przystanek(\
                          ID_Polaczenie NUMBER(6) CONSTRAINT Przystanek_fk1 REFERENCES Polaczenie(ID_Polaczenie),\
                          ID_Stacja NUMBER(6) CONSTRAINT Przystanek_fk2 REFERENCES Stacja(ID_Stacja),\
                          PRIMARY KEY (ID_Polaczenie,ID_Stacja))"))
        status=false;

    if(!create_query.exec("CREATE TABLE Pracownik_Pociagu(\
                          ID_Pracownik NUMBER(6) CONSTRAINT Pracownik_Pociagu_fk1 REFERENCES Pracownik(ID_Pracownik),\
                          ID_Pociag NUMBER(6) CONSTRAINT Pracownik_Pociagu_fk2 REFERENCES Pociag(ID_Pociag),\
                          PRIMARY KEY (ID_Pracownik,ID_Pociag))"))
        status=false;

       return status;
}
