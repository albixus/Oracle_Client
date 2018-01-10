#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QAction>
#include "dbmenagement.h"
#include <QMessageBox>
#include "check.h"

namespace Ui {
class deleteWindow;
}

class deleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit deleteWindow(dbMenagement *db,QWidget *parent = 0);

    ~deleteWindow();

    QString get_query_string() { return query_string; }

public:
    bool is_canceled;

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_buttonBox_helpRequested();

    void on_buttonBox_rejected();

private:
    enum tabs {PASSENGER, WORKER, TRAIN, STATION, COMPARTMENT, CONNECTION, TRAIN_WORKER, TRAIN_STOP, ROUTE, TICKET}current_tab;
    Ui::deleteWindow *ui;
    dbMenagement *db;

    QString id_string;
    QString query_string;

    QStringListModel *model;
    QStringList *list;

    int current_index;

private:
    //making a SELECT * on table given in parameter
    void select_all_from_table(QString table);
};

#endif // DELETEWINDOW_H
