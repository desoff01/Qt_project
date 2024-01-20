#ifndef DIALOGEDITTABLES_H
#define DIALOGEDITTABLES_H

#include <QDialog>
#include <QSqlQuery>

///
/// data change window class
///

namespace Ui {
class DialogEditTables;
}

class DialogEditTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditTables(QWidget *parent = nullptr);
    ~DialogEditTables();

private slots:
    void pushButtonEdit_clicked();

private:
    Ui::DialogEditTables *ui;
    QSqlQuery query;
};

#endif // DIALOGEDITTABLES_H
