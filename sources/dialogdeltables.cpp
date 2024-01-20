#include "headers/dialogdeltables.h"
#include "ui_dialogdeltables.h"
#include "headers/globalAuthentication.h"

DialogDelTables::DialogDelTables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDelTables)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    query = QSqlQuery(auth);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DialogDelTables::close);
    connect(ui->pushButtonDel, &QPushButton::clicked, this, &DialogDelTables::pushButtonDel_clicked);
}

DialogDelTables::~DialogDelTables()
{
    delete ui;
}

void DialogDelTables::pushButtonDel_clicked() {
    bool success;
    auth.open();

    switch(st) {
    case SelectTables::COMPANIES:
        query.prepare("DELETE FROM Companies WHERE idCompanies = :id");
        query.bindValue(":id", ui->spinBox->text());
        break;
    case SelectTables::CONTACTS:
        query.prepare("DELETE FROM Contacts WHERE idContacts = :id");
        query.bindValue(":id", ui->spinBox->text());
        break;
    case SelectTables::INFO:
        query.prepare("DELETE FROM InfoCompany WHERE idInfoCompany = :id");
        query.bindValue(":id", ui->spinBox->text());
        break;
    case SelectTables::SERVICES:
        query.prepare("DELETE FROM Services WHERE idServices = :id");
        query.bindValue(":id", ui->spinBox->text());
        break;
    case SelectTables::CONTRACTS:
        query.prepare("DELETE FROM Contracts WHERE numOfContract = :id");
        query.bindValue(":id", ui->spinBox->text());
        break;
    }
    success = query.exec();

    if (success) {
        ui->labelStatus->setText("Запись удалена");
        ui->labelStatus->setStyleSheet("color: #63c71c");
    } else {
        ui->labelStatus->setText("Неверный id");
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}
