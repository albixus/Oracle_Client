#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QAction>

namespace Ui {
class deleteWindow;
}

class deleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit deleteWindow(QWidget *parent = 0);
    ~deleteWindow();

private:
    Ui::deleteWindow *ui;
};

#endif // DELETEWINDOW_H
