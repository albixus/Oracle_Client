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
}

void updateWindow::on_tableView_Passenger_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);
    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pasazer WHERE ID_Pasazer = " + id_string);
    query.next();
    ui->lineEdit_passenger_name->setText(query.value(1).toString());
    ui->lineEdit_passenger_surname->setText(query.value(2).toString());
    ui->lineEdit_passenger_phone->setText(query.value(3).toString());
}

void updateWindow::on_tabWidget_currentChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;
    QSqlQueryModel *model3 = new QSqlQueryModel;
    QSqlQueryModel *model4 = new QSqlQueryModel;

    QSqlQuery query;
    QSqlQuery query2;
    QSqlQuery query3;
    QSqlQuery query4;

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
    }
}

void updateWindow::on_buttonBox_accepted()
{
    int index = ui->tabWidget->currentIndex();
    query_string = "UPDATE ";
    switch(index)
    {
    case PASSENGER:
        if(!string_check(ui->lineEdit_passenger_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!string_check(ui->lineEdit_passenger_surname->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwisku nie może znajdować się cyfra!");
            return;
        }
        if(!is_string_number(ui->lineEdit_passenger_phone->text()))
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
        if(!string_check(ui->lineEdit_worker_name->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!string_check(ui->lineEdit_worker_surname->text()))
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
        if(!string_check(ui->lineEdit_train_name->text()))
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
        if(!string_check(ui->lineEdit_station_name->text()))
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
        if(!string_check(ui->lineEdit_arrival->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwie nie może znajdować się cyfra!");
            return;
        }

        if(!string_check(ui->lineEdit_departure->text()))
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


    }


    this->close();
}

void updateWindow::on_buttonBox_rejected()
{
    this->close();
}

bool updateWindow::string_check(QString str)
{
    std::string stdstr = str.toStdString();
    for(unsigned int i =0; i<stdstr.size(); i++)
    {
        if(std::isdigit(stdstr.at(i)))
          return false;
    }
    return true;
}

bool updateWindow::is_string_number(QString str)
{
    std::string stdstr = str.toStdString();
    for(unsigned int i =0; i<stdstr.size(); i++)
    {
        if(std::isdigit(stdstr.at(i)))
          continue;
        return false;
    }
    return true;
}

void updateWindow::get_id_from_table(QModelIndex index, QString &id_string)
{
    if(index.column()==0)
        id_string = index.data().toString();
    else
        QMessageBox::about(this,"Błąd","Zaznacz ID!");
}

void updateWindow::on_tableView_Passenger_activated(const QModelIndex &index)
{

}

void updateWindow::on_tableView_worker_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pracownik WHERE ID_Pracownik = " + id_string);
    query.next();
    ui->lineEdit_worker_name->setText(query.value(1).toString());
    ui->lineEdit_worker_surname->setText(query.value(2).toString());
    ui->spinBox_worker_salary->setValue(query.value(3).toInt());
}


void updateWindow::on_tableView_train_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Pociag WHERE ID_Pociag = " + id_string);
    query.next();
    ui->spinBox_train->setValue(query.value(1).toInt());
    ui->lineEdit_train_name->setText(query.value(2).toString());
    ui->dateEdit_train->setDate(query.value(3).toDate());
}

void updateWindow::on_tableView_clicked(const QModelIndex &index)
{

}

void updateWindow::on_tableView_station_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Stacja WHERE ID_Stacja = " + id_string);
    query.next();
    ui->lineEdit_station_name->setText(query.value(1).toString());
}

void updateWindow::on_tableView_comparment_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);
}

void updateWindow::on_tableView_compartment_train_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string2);
}

void updateWindow::on_tableView_connection_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);

    QSqlQuery query;
    query = db->select_query_execute("SELECT * FROM Polaczenie WHERE ID_Polaczenie = " + id_string);
    query.next();
    ui->lineEdit_arrival->setText(query.value(1).toString());

    ui->lineEdit_departure->setText(query.value(2).toString());
}

void updateWindow::on_tableView_2_clicked(const QModelIndex &index)
{

}

void updateWindow::on_tableView_trainworker_worker_clicked(const QModelIndex &index)
{
     get_id_from_table(index,id_string);
}

void updateWindow::on_tableView_trainworker_train_clicked(const QModelIndex &index)
{
     get_id_from_table(index,id_string2);
}
