#include "updatewindow.h"
#include "ui_updatewindow.h"


updateWindow::updateWindow(QWidget *parent):
    QDialog(parent),
    ui(new Ui::updateWindow)
{
        ui->setupUi(this);
}

updateWindow::updateWindow(dbMenagement *db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateWindow)
{
    this->db = db;
    ui->setupUi(this);
    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());

}

updateWindow::~updateWindow()
{
    delete ui;
    delete model;
    delete model2;
    delete model3;
    delete model4;
    delete model5;
}

void updateWindow::on_tableView_Passenger_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pasazer WHERE ID_Pasazer = " + id_string);
    query.next();
    ui->lineEdit_passenger_name->setText(query.value(1).toString());
    ui->lineEdit_passenger_surname->setText(query.value(2).toString());
    ui->lineEdit_passenger_phone->setText(query.value(3).toString());
}

void updateWindow::on_tabWidget_currentChanged(int index)
{
    model = new QSqlQueryModel;
    model2 = new QSqlQueryModel;
    model3 = new QSqlQueryModel;
    model4 = new QSqlQueryModel;
    model5 = new QSqlQueryModel;

    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;
    QSqlQuery query5;

    switch(index)
    {
        case PASSENGER:
        query = db->select_query_execute("SELECT * FROM Pasazer");
        model->setQuery(query);
        ui->tableView_Passenger->setModel(model);
        break;
    case WORKER:
        query = db->select_query_execute("SELECT * FROM Pracownik");
        model->setQuery(query);
        ui->tableView_worker->setModel(model);
        break;

    case TRAIN:
        query = db->select_query_execute("SELECT * FROM Pociag");
        model->setQuery(query);
        ui->tableView_train->setModel(model);
        break;

    case STATION:
        query = db->select_query_execute("SELECT * FROM Stacja");
        model->setQuery(query);
        ui->tableView_station->setModel(model);
        break;

    case COMPARTMENT:
        query = db->select_query_execute("SELECT * FROM Przedzial");
        model->setQuery(query);
        ui->tableView_comparment->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pociag");
        model2->setQuery(query2);
        ui->tableView_compartment_train->setModel(model2);
        break;

    case CONNECTION:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView_connection->setModel(model);
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
        ui->tableView_trainstop_connection->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Stacja");
        model2->setQuery(query2);
        ui->tableView_trainstop_station->setModel(model2);
        break;

    case ROUTE:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView_route_connection->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pociag");
        model2->setQuery(query2);
        ui->tableView_route_train->setModel(model2);
        break;

    case TICKET:
        query = db->select_query_execute("SELECT * FROM Bilet");
        model->setQuery(query);
        ui->tableView_ticket->setModel(model);

        query2 = db->select_query_execute("SELECT * FROM Pasazer");
        model2->setQuery(query2);
        ui->tableView_ticket_passenger->setModel(model2);

        query3 = db->select_query_execute("SELECT * FROM Pracownik");
        model3->setQuery(query3);
        ui->tableView_ticket_worker->setModel(model3);

        query4 = db->select_query_execute("SELECT * FROM Polaczenie");
        model4->setQuery(query4);
        ui->tableView_ticket_connection->setModel(model4);

        query5 = db->select_query_execute("SELECT * FROM Przedzial");
        model5->setQuery(query5);
        ui->tableView_ticket_compartment->setModel(model5);
        break;
    }
}

void updateWindow::on_buttonBox_accepted()
{
    int index = ui->tabWidget->currentIndex();
    query_string = "UPDATE ";
    switch(index)
    {
    case PASSENGER:
        if(!check::string_check(ui->lineEdit_passenger_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!check::string_check(ui->lineEdit_passenger_surname->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwisku nie może znajdować się cyfra!");
            return;
        }
        if(!check::is_string_number(ui->lineEdit_passenger_phone->text()))
        {
            QMessageBox::about(this,"Błąd","W Numerze telefonu nie moze znajdować się litera!");
            return;
        }

        query_string += "Pasazer SET Imie = '";
        query_string += ui->lineEdit_passenger_name->text();
        query_string += "', Nazwisko = '";
        query_string += ui->lineEdit_passenger_surname->text();
        query_string += "', Numer_Telefonu = '";
        query_string += ui->lineEdit_passenger_phone->text();
        query_string += "'";
        query_string += "WHERE ID_Pasazer = ";
        query_string += id_string;
        break;

    case WORKER:
        if(!check::string_check(ui->lineEdit_worker_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!check::string_check(ui->lineEdit_worker_surname->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwisku nie może znajdować się cyfra!");
            return;
        }

        query_string += "Pracownik SET Imie = '";
        query_string += ui->lineEdit_worker_name->text();
        query_string += "', Nazwisko = '";
        query_string += ui->lineEdit_worker_surname->text();
        query_string += "', Pensja = ";
        query_string += ui->spinBox_worker_salary->text();
        query_string += " WHERE ID_Pracownik = ";
        query_string += id_string;
        break;

    case TRAIN:
        if(!check::string_check(ui->lineEdit_train_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwie Pociągu nie może znajdować się cyfra!");
            return;
        }

        query_string += "Pociag SET Ilosc_Wagonow = ";
        query_string += ui->spinBox_train->text();
        query_string += ", Nazwa = '";
        query_string += ui->lineEdit_train_name->text();
        query_string += "', Data_Produkcji = TO_DATE('";
        query_string += ui->dateEdit_train->text();
        query_string += "','DD.MM.YYYY') WHERE ID_Pociag = ";
        query_string += id_string;
        break;

    case STATION:
        if(!check::string_check(ui->lineEdit_station_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwie Stacji nie może znajdować się cyfra!");
            return;
        }

        query_string += "Stacja SET Nazwa = '";
        query_string += ui->lineEdit_station_name->text();
        query_string += "' WHERE ID_Stacja = ";
        query_string += id_string;
        break;

    case COMPARTMENT:
        query_string += "Przedzial SET ID_Pociag = ";
        query_string += id_string2;
        query_string += " WHERE ID_Przedzial = ";
        query_string += id_string;
        break;

    case CONNECTION:
        if(!check::string_check(ui->lineEdit_arrival->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwie nie może znajdować się cyfra!");
            return;
        }

        if(!check::string_check(ui->lineEdit_departure->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwie nie może znajdować się cyfra!");
            return;
        }

        query_string += "Polaczenie SET Miejsce_Docelowe = '";
        query_string += ui->lineEdit_arrival->text();
        query_string += "', Miejsce_Wyjazdu = '";
        query_string += ui->lineEdit_departure->text();
        query_string += "' WHERE ID_Polaczenie = ";
        query_string += id_string;
        break;

    case TRAIN_WORKER:
        query_string += "Pracownik_Pociagu SET ID_Pociag = ";
        query_string += id_string2;
        query_string += " WHERE ID_Pracownik = ";
        query_string += id_string;
        break;

    case TRAIN_STOP:
        query_string += "Przystanek SET ID_Stacja = ";
        query_string += id_string2;
        query_string += " WHERE ID_Polaczenie = ";
        query_string += id_string;
        break;

    case ROUTE:
        query_string += "Trasa SET ID_Pociag = ";
        query_string += id_string2;
        query_string += " WHERE ID_Polaczenie = ";
        query_string += id_string;
        break;

    case TICKET:
        query_string += "Bilet SET Data_Wyjazdu = TO_DATE('";
        query_string += ui->dateEdit_ticket_departure->text();
        query_string += "','DD.MM.YYYY'), Data_Przyjazdu = TO_DATE('";
        query_string += ui->dateEdit_ticket_arrival->text();
        query_string += "','DD.MM.YYYY'), Numer_Miejsca = ";
        query_string += ui->spinBox_ticket_seat->text();
        query_string += ", ID_Pasazer = ";
        query_string += id_string2;
        query_string += ", ID_Pracownik = ";
        query_string += id_string3;
        query_string += ", ID_Polaczenie = ";
        query_string += id_string4;
        query_string += ", ID_Przedzial = ";
        query_string += id_string5;
        query_string += " WHERE ID_Bilet = ";
        query_string += id_string;
    }

    is_canceled = false;
    this->close();
}

void updateWindow::on_buttonBox_rejected()
{
    is_canceled = true;
    this->close();
}

void updateWindow::on_tableView_Passenger_activated(const QModelIndex &index)
{

}

void updateWindow::on_tableView_worker_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pracownik WHERE ID_Pracownik = " + id_string);
    query.next();
    ui->lineEdit_worker_name->setText(query.value(1).toString());
    ui->lineEdit_worker_surname->setText(query.value(2).toString());
    ui->spinBox_worker_salary->setValue(query.value(3).toInt());
}


void updateWindow::on_tableView_train_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pociag WHERE ID_Pociag = " + id_string);
    query.next();
    ui->spinBox_train->setValue(query.value(1).toInt());
    ui->lineEdit_train_name->setText(query.value(2).toString());
    ui->dateEdit_train->setDate(query.value(3).toDate());
}


void updateWindow::on_tableView_station_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Stacja WHERE ID_Stacja = " + id_string);
    query.next();
    ui->lineEdit_station_name->setText(query.value(1).toString());
}

void updateWindow::on_tableView_comparment_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);
}

void updateWindow::on_tableView_compartment_train_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string2,this);
}

void updateWindow::on_tableView_connection_clicked(const QModelIndex &index)
{
    check::get_id_from_table(index,id_string,this);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Polaczenie WHERE ID_Polaczenie = " + id_string);
    query.next();
    ui->lineEdit_arrival->setText(query.value(1).toString());

    ui->lineEdit_departure->setText(query.value(2).toString());
}


void updateWindow::on_tableView_trainworker_worker_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string,this);
}

void updateWindow::on_tableView_trainworker_train_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void updateWindow::on_tableView_trainstop_connection_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string,this);
}

void updateWindow::on_tableView_trainstop_station_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void updateWindow::on_tableView_route_connection_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string,this);
}

void updateWindow::on_tableView_route_train_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void updateWindow::on_tableView_ticket_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string,this);
     QSqlQuery query;
     query = db->select_query_execute("SELECT * FROM Bilet WHERE ID_Bilet = " + id_string);
     query.next();

     ui->dateEdit_ticket_departure->setDate(query.value(1).toDate());

     ui->dateEdit_ticket_arrival->setDate(query.value(2).toDate());

     ui->spinBox_ticket_seat->setValue(query.value(3).toInt());

     QString passenger_id = query.value(4).toString();
     ui->label_id_passenger->setText(passenger_id);

     QString worker_id = query.value(5).toString();
     ui->label_id_worker->setText(worker_id);

     QString connection_id = query.value(6).toString();
     ui->label_id_connection->setText(connection_id);

     QString compartment_id = query.value(7).toString();
     ui->label_id_compartment->setText(compartment_id);


}

void updateWindow::on_tableView_ticket_passenger_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string2,this);
}

void updateWindow::on_tableView_ticket_worker_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string3,this);
}

void updateWindow::on_tableView_ticket_connection_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string4,this);
}

void updateWindow::on_tableView_ticket_compartment_clicked(const QModelIndex &index)
{
     check::get_id_from_table(index,id_string5,this);
}

void updateWindow::on_updateWindow_finished(int result)
{}

void updateWindow::on_tableView_2_clicked(const QModelIndex &index)
{

}
void updateWindow::on_tableView_clicked(const QModelIndex &index)
{

}
