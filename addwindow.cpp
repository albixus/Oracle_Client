#include "addwindow.h"
#include "ui_addwindow.h"
#include <cstdlib>
#include <cstdio>

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
        if(!string_check(ui->lineEdit_Name_Passenger->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }
        if(!string_check(ui->lineEdit_Surname_Passenger->text()))
        {
            QMessageBox::about(this,"Błąd","W Nazwisku nie może znajdować się cyfra!");
            return;
        }
        if(!is_string_number(ui->lineEdit_Phone_Passenger->text()))
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
        if(!string_check(ui->lineEdit_Name_Worker->text()))
        {
            QMessageBox::about(this,"Błąd","W Imieniu nie może znajdować się cyfra!");
            return;
        }

        if(!string_check(ui->lineEdit_Surname_Worker->text()))
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

bool addWindow::string_check(QString str)
{
    std::string stdstr = str.toStdString();
    for(unsigned int i =0; i<stdstr.size(); i++)
    {
        if(std::isdigit(stdstr.at(i)))
          return false;
    }
    return true;
}

bool addWindow::is_string_number(QString str)
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
