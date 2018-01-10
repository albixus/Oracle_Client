#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QMessageBox>

#include "dbmenagement.h"
#include "mainwindow.h"
#include "check.h"

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    //first argument use to execute queries on database which was connected in mainwindow
    explicit addWindow(dbMenagement *db, QWidget *parent = 0);

    explicit addWindow(QWidget *parent = 0);

    ~addWindow();

    //return query to execute in mainwindow
    QString get_query_string() { return query_string; }

public:
    //checking in what way user closed the window
    bool is_canceled;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tabs_currentChanged(int index);

    void on_tableView_Compartment_clicked(const QModelIndex &index);

    void on_tableView_trainworker_worker_clicked(const QModelIndex &index);

    void on_tableView_trainworker_train_clicked(const QModelIndex &index);

    void on_tableView_connection_clicked(const QModelIndex &index);

    void on_tableView_station_clicked(const QModelIndex &index);

    void on_tableView_Route_Connection_clicked(const QModelIndex &index);

    void on_tableView_Route_Train_clicked(const QModelIndex &index);

    void on_tableView_ticket_passenger_clicked(const QModelIndex &index);

    void on_tableView_ticket_worker_clicked(const QModelIndex &index);

    void on_tableView_ticket_connection_clicked(const QModelIndex &index);

    void on_tableView_ticket_compartment_clicked(const QModelIndex &index);

private:
    enum tabs {PASSENGER, WORKER, TRAIN, STATION, COMPARTMENT, CONNECTION, TRAIN_WORKER, TRAIN_STOP, ROUTE, TICKET}current_tab;
    Ui::addWindow *ui;

    dbMenagement *db;

    QString query_string;

    QString id_string;
    QString id_string2;
    QString id_string3;
    QString id_string4;
};

#endif // ADDWINDOW_H
