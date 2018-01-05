#include "dbmenagement.h"

dbMenagement::dbMenagement()
{
    db = QSqlDatabase::addDatabase("QOCI");
    db.setUserName("system");
    db.
}
