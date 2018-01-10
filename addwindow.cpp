#include "addwindow.h"
#include "ui_addwindow.h"
#include <cstdlib>
#include <cstdio>

addWindow::addWindow(dbMenagement *db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
    this->db = db;

    current_tab = (tabs)ui->tabs->currentIndex();
    on_tabs_currentChanged(current_tab);
}

addWindow::addWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::addWindow)
{
     ui->setupUi(this);
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_buttonBox_accepted()
{ 
    query_string = "INSERT INTO ";
    current_tab = (tabs)ui->tabs->currentIndex();

    switch(current_tab)
    {
    case PASSENGER:
        if(!check::string_check(ui->lineEdit_Name_Passenger->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!check::string_check(ui->lineEdit_Surname_Passenger->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwisku nie może znajdować się cyfra!");
            return;
        }
        if(!check::is_string_number(ui->lineEdit_Phone_Passenger->text()))
        {
            QMessageBox::about(this,"Błąd","W Numerze telefonu nie moze znajdować się litera!");
            return;
        }
        if((!ui->lineEdit_Name_Passenger->isModified())||(!ui->lineEdit_Surname_Passenger->isModified())||(!ui->lineEdit_Phone_Passenger->isModified()))
        {
            QMessageBox::about(this,"Błąd", "Uzupełnij puste pola!");
            return;
        }

        query_string += "Pasazer(ID_Pasazer,Imie,Nazwisko,Numer_telefonu) VALUES(pasazer_seq.nextval, '";
        query_string += ui->lineEdit_Name_Passenger->text();
        query_string += "','";
        query_string += ui->lineEdit_Surname_Passenger->text();
        query_string += "','";
        query_string += ui->lineEdit_Phone_Passenger->text();
        query_string += "')";

        break;

    case WORKER:
        if(!check::string_check(ui->lineEdit_Name_Worker->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }

        if(!check::string_check(ui->lineEdit_Surname_Worker->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }

        if((!ui->lineEdit_Name_Worker->isModified())||(!ui->lineEdit_Surname_Worker->isModified()))
        {
            QMessageBox::about(this,"Błąd", "Uzupełnij puste pola!");
            return;
        }
        query_string += "Pracownik(ID_Pracownik,Imie,Nazwisko,Pensja) VALUES(pracownik_seq.nextval, '";
        query_string += ui->lineEdit_Name_Worker->text();
        query_string += "','";
        query_string += ui->lineEdit_Surname_Worker->text();
        query_string += "',";
        query_string += ui->spinBox->text();
        query_string += ")";
        break;

    case TRAIN:
        if(!check::string_check(ui->lineEdit_train_Name->text()))
        {
            QMessageBox::about(this,"Błąd","W nazwie pociągu nie może znajdować się cyfra!");
            return;
        }
        if(!ui->lineEdit_train_Name->isModified())
        {
            QMessageBox::about(this,"Błąd", "Uzupełnij puste pola!");
            return;
        }
        query_string +="Pociag(ID_Pociag,Ilosc_wagonow, Nazwa, Data_Produkcji) VALUES(pociag_seq.nextval, ";
        query_string += ui->spinBox_Train->text();
        query_string += ",'";
        query_string += ui->lineEdit_train_Name->text();
        query_string += "', TO_DATE('";
        query_string += ui->dateEdit_Train->text();
        query_string += "','DD.MM.YYYY'))";
        break;

    case STATION:
        if(!check::string_check(ui->lineEdi_Name_Station->text()))
        {
            QMessageBox::about(this,"Błąd","W nazwie stacji nie może znajdować się cyfra!");
            return;
        }
        if(!ui->lineEdi_Name_Station->isModified())
        {
            QMessageBox::about(this,"Błąd", "Uzupełnij puste pola!");
            return;
        }

        query_string += "Stacja(ID_Stacja, Nazwa) VALUES (stacja_seq.nextval, '";
        query_string += ui->lineEdi_Name_Station->text();
        query_string +=  "')";
        break;

    case COMPARTMENT:
        query_string += "Przedzial(ID_Przedzial,ID_Pociag) VALUES(przedzial_seq.nextval,";
        query_string += id_string;
        query_string += ")";
        break;

     case CONNECTION:
        if((!check::string_check(ui->lineEdit_Arrival->text()))||(!check::string_check(ui->lineEdit_Departure->text())))
        {
            QMessageBox::about(this,"Bład","Wykryto cyfrę w nazwie miejscowości! Zmień to!");
            return;
        }

        if((!ui->lineEdit_Arrival->isModified())||(!ui->lineEdit_Departure->isModified()))
        {
            QMessageBox::about(this,"Błąd", "Uzupełnij puste pola!");
            return;
        }

        query_string += "Polaczenie(ID_Polaczenie, Miejsce_Docelowe, Miejsce_Wyjazdu) VALUES(Polaczenie_seq.nextval,'";
        query_string += ui->lineEdit_Arrival->text();
        query_string += "','";
        query_string += ui->lineEdit_Departure->text();
        query_string += "')";
        break;

      case TRAIN_WORKER:
        query_string += "Pracownik_Pociagu(ID_Pociag,ID_Pracownik) VALUES(";
        query_string += id_string2;
        query_string += ",";
        query_string += id_string;
        query_string += ")";
        break;

    case TRAIN_STOP:
        query_string += "Przystanek(ID_Polaczenie, ID_Stacja) VALUES(";
        query_string += id_string;
        query_string += ",";
        query_string += id_string2;
        query_string += ")";
        break;
    case ROUTE:
        query_string += "Trasa(ID_Polaczenie, ID_Pociag) VALUES(";
        query_string += id_string;
        query_string += ",";
        query_string += id_string2;
        query_string += ")";
        break;

    case TICKET:
        query_string += "Bilet(ID_Bilet, Data_Wyjazdu, Data_Przyjazdu, Numer_Miejsca, ID_Pasazer,ID_Pracownik,ID_Polaczenie,ID_Przedzial) VALUES(bilet_seq.nextval, TO_DATE('";
        query_string += ui->dateEdit_departure_date->text();
        query_string += "','DD.MM.YYYY'),TO_DATE('";
        query_string += ui->dateEdit_arrival_date->text();
        query_string += "','DD.MM.YYYY'),";
        query_string += ui->spinBox_ticket_seat_number->text();
        query_string += ",";
        query_string += id_string;
        query_string += ",";
        query_string += id_string2;
        query_string += ",";
        query_string += id_string3;
        query_string += ",";
        query_string += id_string4;
        query_string += ")";
        break;

     default:
        break;
    }

    is_canceled = false;
    this->close();
}

void addWindow::on_buttonBox_rejected()
{
    is_canceled = true;
    this->close();
}

void addWindow::on_tabs_currentChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;
    QSqlQueryModel *model3 = new QSqlQueryModel;
    QSqlQueryModel *model4 = new QSqlQueryModel;

    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;

   //setting models to qtableviews
    switch(index)
    {
    case COMPARTMENT:
        query = db->select_query_execute("SELECT * FROM Pociag");
        model->setQuery(query);
        ui->tableView_Compartment->setModel(model);
        break;

    case TRAIN_WORKER:
        query = db->select_query_execute("SELECT * FROM Pracownik");
        model->setQuery(query);
        ui->tableView_trainworker_worker->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pociag");
        model2->setQuery(query2);
        ui->tableView_trainworker_train->setModel(model2);
        break;

    case TRAIN_STOP:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView_connection->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Stacja");
        model2->setQuery(query2);
        ui->tableView_station->setModel(model2);
        break;

    case ROUTE:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView_Route_Connection->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pociag");
        model2->setQuery(query2);
        ui->tableView_Route_Train->setModel(model2);
        break;

    case TICKET:
        query = db->select_query_execute("SELECT * FROM Pasazer");
        model->setQuery(query);
        ui->tableView_ticket_passenger->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pracownik");
        model2->setQuery(query2);
        ui->tableView_ticket_worker->setModel(model2);

        query3 = db->select_query_execute("SELECT * FROM Polaczenie");
        model3->setQuery(query3);
        ui->tableView_ticket_connection->setModel(model3);

        query4 = db->select_query_execute("SELECT * FROM Przedzial");
        model4->setQuery(query4);
        ui->tableView_ticket_compartment->setModel(model4);
        break;
    }
}

void addWindow::on_tableView_Compartment_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
}

void addWindow::on_tableView_trainworker_worker_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
}

void addWindow::on_tableView_trainworker_train_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void addWindow::on_tableView_connection_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string,this);
}

void addWindow::on_tableView_station_clicked(const QModelIndex &index)
{
   check::get_id_from_table(index,id_string2,this);
}

void addWindow::on_tableView_Route_Connection_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
}

void addWindow::on_tableView_Route_Train_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void addWindow::on_tableView_ticket_passenger_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
}

void addWindow::on_tableView_ticket_worker_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void addWindow::on_tableView_ticket_connection_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string3,this);
}

void addWindow::on_tableView_ticket_compartment_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string4,this);
}

