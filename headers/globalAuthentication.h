#ifndef GLOBALAUTHENTICATION_H
#define GLOBALAUTHENTICATION_H
#include <QSqlDatabase>

///
/// class with global variables
///

extern QSqlDatabase auth;

enum struct SelectTables {COMPANIES,
                    CONTACTS,
                    INFO,
                    SERVICES,
                    CONTRACTS};

extern SelectTables st;

#endif // GLOBALAUTHENTICATION_H
