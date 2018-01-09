#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new dbMenagement();


    if(db->open())
        QMessageBox::about(this,"OK","Udało się nawiązać połączenie z baza");
    else
        QMessageBox::critical(this,"Błąd","Nie udało się nawiązać połączenia z baza");

    on_selectComboBox_currentIndexChanged(0);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,150);
    ui->tableView->setColumnWidth(3,150);
    //db->drop_all_tables();
    // db->create_tables();
    // db->create_sequences();
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
    addWindow *add_win = new addWindow(db,this);
    add_win->setModal(false);
    add_win->exec();
    query_string = add_win->get_query_string();

    if(!add_win->is_canceled)
        if(db->query_execute(query_string))
            QMessageBox::about(this,"OK","Udało się dodać pozycję do bazy");
        else
            QMessageBox::critical(this,"Błąd","Nie udało się dodać do bazy");

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
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{}

void MainWindow::on_updateButton_clicked()
{
    updateWindow *update_win = new updateWindow(db,this);
    update_win->setModal(false);
    update_win->exec();
    query_string = update_win->get_query_string();

    if(!update_win->is_canceled)
        if(db->query_execute(query_string))
            QMessageBox::about(this,"OK","Modyfikacja danych powiodła się!");
        else
            QMessageBox::critical(this,"Błąd!","Modyfikacja danych nie powiodła się!");

    delete update_win;
}

void MainWindow::on_deleteButton_clicked()
{
    deleteWindow *del_win = new deleteWindow(db,this);
    del_win -> setModal(false);
    del_win ->exec();

    query_string = del_win->get_query_string();

    if(db->query_execute(query_string))
        QMessageBox::about(this,"OK","Modyfikacja danych powiodła się!");
    else
        QMessageBox::critical(this,"Błąd!","Modyfikacja danych nie powiodła się!");
}
