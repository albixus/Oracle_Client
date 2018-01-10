#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addwindow.h"
#include "dbmenagement.h"
#include "updatewindow.h"
#include <QMessageBox>
#include "deletewindow.h"
#include "check.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_addButton_clicked();

    void on_selectComboBox_currentIndexChanged(int index);

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_updateButton_clicked();

    void on_deleteButton_clicked();

    void on_listView_queries_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    dbMenagement *db;

    QString query_string;

    QStringListModel *model;
    QStringList *list;
};

#endif // MAINWINDOW_H
