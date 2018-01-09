#include "deletewindow.h"
#include "ui_deletewindow.h"


deleteWindow::deleteWindow(dbMenagement *db, QWidget *parent):
    QDialog(parent),
    ui(new Ui::deleteWindow)
{
      this->db =db;
      ui->setupUi(this);
//      {PASSENGER, WORKER, TRAIN, STATION, COMPARTMENT, CONNECTION, TRAIN_WORKER, TRAIN_STOP, ROUTE, TICKET}current_tab;

     list = new QStringList();
     list->append("Pasazer");
     list->append("Pracownik");
     list->append("Pociag");
     list->append("Stacja");
     list->append("Przedział");
     list->append("Połączenie");
     list->append("Pracownik pociągu");
     list->append("Przystanek");
     list->append("Trasa");
     list->append("Bilet");

     model = new QStringListModel;

     model->setStringList(*list);
     ui->listView->setModel(model);

     delete list;
}

deleteWindow::~deleteWindow()
{
    delete ui;
}

void deleteWindow::on_listView_clicked(const QModelIndex &index)
{


    current_index = index.row();
    switch (current_index)
    {
    case PASSENGER:
        select_all_from_table("Pasazer");
        break;
    case WORKER:
        select_all_from_table("Pracownik");
        break;
    case TRAIN:
        select_all_from_table("Pociag");
        break;
    case STATION:
        select_all_from_table("Stacja");
        break;
    case COMPARTMENT:
        select_all_from_table("Przedzial");
        break;
    case TICKET:
        select_all_from_table("Bilet");
        break;
    case ROUTE:
        select_all_from_table("Trasa");
        break;
    case TRAIN_STOP:
        select_all_from_table("Przystanek");
        break;
    case TRAIN_WORKER:
        select_all_from_table("Pracownik_Pociagu");
        break;
    case CONNECTION:
        select_all_from_table("Polaczenie");
        break;
    }
}

void deleteWindow::select_all_from_table(QString table)
{
    QSqlQuery query;
    QSqlQueryModel *query_model = new QSqlQueryModel();

    query = db->select_query_execute("SELECT * FROM " + table);
    query_model->setQuery(query);
    ui->tableView->setModel(query_model);
}

void deleteWindow::on_tableView_clicked(const QModelIndex &index)
{
    get_id_from_table(index,id_string);
}

void deleteWindow::get_id_from_table(QModelIndex index, QString &id_string)
{
    if(index.column()==0)
        id_string = index.data().toString();
    else
        QMessageBox::about(this,"Błąd","Zaznacz ID!");
}


void deleteWindow::on_buttonBox_accepted()
{
    query_string = "DELETE FROM ";
    switch (current_index)
    {
    case PASSENGER:
        query_string += "Pasazer WHERE ID_Pasazer = ";
        query_string += id_string;
        break;
    case WORKER:
        query_string += "Pracownik WHERE ID_Pracownik = ";
        query_string += id_string;
        break;
    case TRAIN:
        query_string += "Pociag WHERE ID_Pociag = ";
        query_string += id_string;
        break;
    case STATION:
        query_string += "Stacja WHERE ID_Stacja = ";
        query_string += id_string;
        break;
    case COMPARTMENT:
        query_string += "Przedzial WHERE ID_Przedzial = ";
        query_string += id_string;
        break;
    case TICKET:
        query_string += "Bilet WHERE ID_Bilet = ";
        query_string += id_string;
        break;
    case ROUTE:

        break;
    case TRAIN_STOP:
        break;
    case TRAIN_WORKER:
        break;
    case CONNECTION:
        query_string += "Polaczenie WHERE ID_Polaczenie = ";
        query_string += id_string;
        break;
    }

    is_canceled = false;
    this->close();
}

void deleteWindow::on_buttonBox_helpRequested()
{}

void deleteWindow::on_buttonBox_rejected()
{
    is_canceled = true;
    this->close();
}
