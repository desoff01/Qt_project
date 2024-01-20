#ifndef DIALOGADDTABLES_H
#define DIALOGADDTABLES_H

#include <QDialog>

///
/// data add window class
///

namespace Ui {
class DialogAddTables;
}

class DialogAddTables : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddTables(QWidget *parent = nullptr);
    ~DialogAddTables();

private slots:
    void pushButtonAdd_clicked();

private:
    Ui::DialogAddTables *ui;
};

#endif // DIALOGADDTABLES_H
