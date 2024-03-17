#include "headers/dialogedittables.h"
#include "ui_dialogedittables.h"
#include "headers/globalAuthentication.h"

DialogEditTables::DialogEditTables(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditTables)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    query = QSqlQuery(auth);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &DialogEditTables::close);
    connect(ui->pushButtonEdit, &QPushButton::clicked, this, &DialogEditTables::pushButtonEdit_clicked);

    switch (st) {
    case SelectTables::COMPANIES:
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->hide();

        ui->label->setText(tr("Компания:"));
        ui->label_2->setText(tr("Фамилия:"));
        ui->label_3->setText(tr("Имя:"));
        ui->label_4->setText(tr("Отчество:"));
        break;

    case SelectTables::CONTACTS:
        ui->lineEdit_2->show();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Номер телефона:"));
        ui->label_2->setText(tr("Почта:"));
        break;

    case SelectTables::INFO:
        ui->lineEdit_2->show();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Номер телефона:"));
        ui->label_2->setText(tr("Компания:"));
        break;

    case SelectTables::SERVICES:
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->label->setText(tr("Услуга:"));
        break;

    case SelectTables::CONTRACTS:
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->lineEdit_5->show();

        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();

        ui->label->setText(tr("Компания:"));
        ui->label_2->setText(tr("Номер телефона:"));
        ui->label_3->setText(tr("Дата заключения:"));
        ui->label_4->setText(tr("Дедлайн:"));
        ui->label_5->setText(tr("Услуга:"));
        break;
    }
}

DialogEditTables::~DialogEditTables()
{
    delete ui;
}

void DialogEditTables::pushButtonEdit_clicked() {
    bool success;
    auth.open();

    switch(st) {
    case SelectTables::COMPANIES:
        query.prepare("UPDATE Companies SET `nameCompany` = :company,"
                      " `surnameDir` = :surname, `fnameDir` = :name, "
                      "`patronymicDir` = :patronymic"
                      " WHERE (`idCompanies` = :id)");
        query.bindValue(":company", ui->lineEdit->text());
        query.bindValue(":surname", ui->lineEdit_2->text());
        query.bindValue(":name", ui->lineEdit_3->text());
        query.bindValue(":patronymic", ui->lineEdit_4->text());
        query.bindValue(":id", ui->spinBox->text());
        success = query.exec();
        break;

    case SelectTables::CONTACTS:
        query.prepare("UPDATE Contacts SET `phoneContacts` = :phone, "
                      "`emailContacts` = :email WHERE (`idContacts` = :id)");
        query.bindValue(":phone", ui->lineEdit->text());
        query.bindValue(":email", ui->lineEdit_2->text());
        query.bindValue(":id", ui->spinBox->text());
        success = query.exec();
        break;

    case SelectTables::INFO:
    {
        query.prepare("SELECT idContacts FROM Contacts "
                      "WHERE phoneContacts = :phone");
        query.bindValue(":phone", ui->lineEdit->text());
        query.exec();
        query.first();
        QString idContacts {query.value(0).toString()};

        query.prepare("SELECT idCompanies FROM Companies "
                      "WHERE nameCompany = :company");
        query.bindValue(":company", ui->lineEdit_2->text());
        query.exec();
        query.first();
        QString idCompanies {query.value(0).toString()};

        query.prepare("UPDATE InfoCompany SET `idCompaniesInfo` = :idCompanies, "
                      "`idContactsInfo` = :idContacts WHERE (`idInfoCompany` = :idInfo)");
        query.bindValue(":idContacts", idContacts);
        query.bindValue(":idCompanies", idCompanies);
        query.bindValue(":idInfo", ui->spinBox->text());
        success = query.exec();
        break;
    }

    case SelectTables::SERVICES:
        query.prepare("UPDATE Services SET `Service` = :service"
                      " WHERE (`idServices` = :id)");
        query.bindValue(":service", ui->lineEdit->text());
        query.bindValue(":id", ui->spinBox->text());
        success = query.exec();
        break;

    case SelectTables::CONTRACTS:
    {
        query.prepare("SELECT idContacts FROM Contacts WHERE phoneContacts = :phone");
        query.bindValue(":phone", ui->lineEdit_2->text());
        query.exec();
        query.first();
        QString idContacts {query.value(0).toString()};

        query.prepare("SELECT idCompanies FROM Companies WHERE nameCompany = :company");
        query.bindValue(":company", ui->lineEdit->text());
        query.exec();
        query.first();
        QString idCompanies {query.value(0).toString()};

        query.prepare("SELECT idInfoCompany FROM InfoCompany WHERE"
                      " idCompaniesInfo = :idcompany AND idContactsInfo = :idcontact");
        query.bindValue(":idcompany", idCompanies);
        query.bindValue(":idcontact", idContacts);
        query.exec();
        query.first();
        QString idInfoCompany {query.value(0).toString()};

        query.prepare("SELECT idServices FROM Services WHERE Service = :service");
        query.bindValue(":service", ui->lineEdit_5->text());
        query.exec();
        query.first();
        QString idService {query.value(0).toString()};

        query.prepare("UPDATE Contracts SET `DateOfConclusion` = :conclusion,"
                      " `Deadline` = :deadline, `idInfoCompanyCon` = :idInfo, "
                      "`idServicesCon` = :idService WHERE (`numOfContract` = :id)");
        query.bindValue(":conclusion", ui->lineEdit_3->text());
        query.bindValue(":deadline", ui->lineEdit_4->text());
        query.bindValue(":idinfo", idInfoCompany);
        query.bindValue(":idservice", idService);
        query.bindValue(":id", ui->spinBox->text());
        success = query.exec();
        break;
    }
    }

    if (success) {
        ui->labelStatus->setText(tr("Запись изменена"));
        ui->labelStatus->setStyleSheet("color: #63c71c");
    } else {
        ui->labelStatus->setText(tr("Запись не изменена"));
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}
