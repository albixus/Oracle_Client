#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "dbmenagement.h"

namespace Ui {
class addWindow;
}

class addWindow : public QDialog
{
    Q_OBJECT

public:
    explicit addWindow(QWidget *parent = 0);
    ~addWindow();
    QString get_query_string() { return query_string; }

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    QString query_string;
    Ui::addWindow *ui;
    enum tabs {PASSENGER, WORKER, TRAIN}current_tab;
};

#endif // ADDWINDOW_H
