#include "addwindow.h"
#include "ui_addwindow.h"

addWindow::addWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addWindow)
{
    ui->setupUi(this);
    query_string = "INSERT INTO ";
    current_tab = (tabs)ui->tabs->currentIndex();
}

addWindow::~addWindow()
{
    delete ui;
}

void addWindow::on_buttonBox_accepted()
{ 
    current_tab = (tabs)ui->tabs->currentIndex();

    switch(current_tab)
    {
    case PASSENGER:
        query_string += "Pasazer(ID_Pasazer,Imie,Nazwisko,Numer_telefonu) VALUES(pasazer_seq.nextval, '";
        query_string += ui->lineEdit_Name_Passenger->text();
        query_string += "','";
        query_string += ui->lineEdit_Surname_Passenger->text();
        query_string += "','";
        query_string += ui->lineEdit_Phone_Passenger->text();
        query_string += "')";

        break;

    case WORKER:

        break;

    case TRAIN:

        break;

     default:

        break;
    }

    this->close();
}

void addWindow::on_buttonBox_rejected()
{

    this->close();
}
