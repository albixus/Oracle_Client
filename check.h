#ifndef CHECK_H
#define CHECK_H
#include <QString>
#include <QModelIndex>
#include <QMessageBox>
class check
{
public:
    check();
    static bool string_check(QString str);
    static bool is_string_number(QString str);
    static void get_id_from_table(QModelIndex index, QString &id_string,QWidget *parent);

};

#endif // CHECK_H
