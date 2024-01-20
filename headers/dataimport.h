#ifndef DATAIMPORT_H
#define DATAIMPORT_H

#include <QDialog>

///
/// data import window class
///

namespace Ui {
class DataImport;
}

class DataImport : public QDialog
{
    Q_OBJECT

public:
    explicit DataImport(QWidget *parent = nullptr);
    ~DataImport();

private slots:
    void pushButtonOpenFile_clicked();

    void pushButtonImport_clicked();

    void ComboBoxSelectTable_changed();

    void pushButtonAdd_clicked();

private:
    Ui::DataImport *ui;
    QString filename;
    int cols;
    QStringList strList;

    bool importTable(const QStringList& strList) const;
};

#endif // DATAIMPORT_H
