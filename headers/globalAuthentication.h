#ifndef GLOBALAUTHENTICATION_H
#define GLOBALAUTHENTICATION_H
#include <QSqlDatabase>
#include <QApplication>
#include "hash.h"

///
/// class with global variables
///

extern QSqlDatabase auth;
extern Hash hash;

enum struct SelectTables {COMPANIES,
                    CONTACTS,
                    INFO,
                    SERVICES,
                    CONTRACTS};

extern SelectTables st;

#endif // GLOBALAUTHENTICATION_H
