#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new dbMenagement();

    if(db->open())
        QMessageBox::about(this,"HURRA","Udało się nawiązać połączenie z baza");
    else
        QMessageBox::about(this,"Połączenie","Nie udało się nawiązać połączenia z baza");

    on_selectComboBox_currentIndexChanged(0);
  //  db->create_tables();
  //  db->create_sequences();
  //  QMessageBox::about(this,"HURRA","ok");
}

MainWindow::~MainWindow()
{
    delete db;
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    //opening add dialog
    addWindow *add_win = new addWindow(this);
    add_win->setModal(false);
    add_win->exec();

    query_string = add_win->get_query_string();
    if(db->query_execute(query_string))
        QMessageBox::about(this,"HURRA","Udało się INSERT");
    delete add_win;
}

void MainWindow::on_selectComboBox_currentIndexChanged(int index)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    switch(index)
    {
    case 0:
        query = db->select_query_execute("SELECT * FROM Pasazer");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 1:
        query = db->select_query_execute("SELECT * FROM Pracownik");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 2:
        query = db->select_query_execute("SELECT * FROM Pociag");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 3:
        query = db->select_query_execute("SELECT * FROM Stacja");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 4:
        query = db->select_query_execute("SELECT * FROM Polaczenie");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;

    case 5:
        query = db->select_query_execute("SELECT * FROM Bilet");
        model->setQuery(query);
        ui->tableView->setModel(model);
        break;
    }

    delete model;
}
