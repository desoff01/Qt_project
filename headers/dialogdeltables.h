#ifndef DIALOGDELTABLES_H
#define DIALOGDELTABLES_H

#include <QDialog>
#include <QSqlQuery>

///
/// data delete window class
///

namespace Ui {
class DialogDelTables;
}

class DialogDelTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDelTables(QWidget *parent = nullptr);
    ~DialogDelTables();

private slots:
    void pushButtonDel_clicked();

private:
    Ui::DialogDelTables *ui;
    QSqlQuery query;
};

#endif // DIALOGDELTABLES_H
