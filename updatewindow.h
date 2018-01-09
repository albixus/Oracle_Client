#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H

#include <QDialog>
#include "dbmenagement.h"
#include "addwindow.h"

namespace Ui {
class updateWindow;
}

class updateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit updateWindow(QWidget *parent = 0);    
    explicit updateWindow(dbMenagement *db, QWidget *parent);
    QString get_query_string() { return query_string; }
    bool is_canceled;
    ~updateWindow();

private slots:
    void on_tableView_Passenger_clicked(const QModelIndex &index);

    void on_tabWidget_currentChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_tableView_Passenger_activated(const QModelIndex &index);

    void on_tableView_worker_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_train_clicked(const QModelIndex &index);

    void on_tableView_station_clicked(const QModelIndex &index);

    void on_tableView_comparment_clicked(const QModelIndex &index);

    void on_tableView_compartment_train_clicked(const QModelIndex &index);

    void on_tableView_connection_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_trainworker_worker_clicked(const QModelIndex &index);

    void on_tableView_trainworker_train_clicked(const QModelIndex &index);

    void on_tableView_trainstop_connection_clicked(const QModelIndex &index);

    void on_tableView_trainstop_station_clicked(const QModelIndex &index);

    void on_tableView_route_connection_clicked(const QModelIndex &index);

    void on_tableView_route_train_clicked(const QModelIndex &index);

    void on_tableView_ticket_clicked(const QModelIndex &index);

    void on_tableView_ticket_passenger_clicked(const QModelIndex &index);

    void on_tableView_ticket_worker_clicked(const QModelIndex &index);

    void on_tableView_ticket_connection_clicked(const QModelIndex &index);

    void on_tableView_ticket_compartment_clicked(const QModelIndex &index);

    void on_updateWindow_finished(int result);

private:
    Ui::updateWindow *ui;
    dbMenagement *db;
    enum tabs {PASSENGER, WORKER, TRAIN, STATION, COMPARTMENT, CONNECTION, TRAIN_WORKER, TRAIN_STOP, ROUTE, TICKET}current_tab;
    bool string_check(QString str);
    bool is_string_number(QString str);
    QString id_string;
    QString id_string2;
    QString id_string3;
    QString id_string4;
    QString id_string5;
    QString query_string;

    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;
    QSqlQueryModel *model4;
    QSqlQueryModel *model5;

    void get_id_from_table(QModelIndex index, QString &id_string);
};

#endif // UPDATEWINDOW_H
