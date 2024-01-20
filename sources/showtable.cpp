#include "headers/showtable.h"
#include "headers/globalAuthentication.h"
#include <QMessageBox>

ShowTables::ShowTables(QSqlQueryModel* model, QTableView* tableView)
{
    this->tableView = tableView;
    this->model = model;
}

ShowTables::ShowTables(QTableView* tableView) {
    this->tableView = tableView;
    model = new QSqlQueryModel;
}

ShowTables::~ShowTables() {
    delete tableView;
    delete model;
}

void ShowTables::showCompanies() const {
    if (auth.open()) {
        model->clear();

        model->setQuery("SELECT * FROM Companies;", auth);
        tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, "Компания");
        model->setHeaderData(2, Qt::Horizontal, "Фамилия");
        model->setHeaderData(3, Qt::Horizontal, "Имя");
        model->setHeaderData(4, Qt::Horizontal, "Отчество");

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showContacts() const {
    if (auth.open()) {
        model->clear();
        model->setQuery("SELECT * FROM Contacts;", auth);
        tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, "Номер телефона");
        model->setHeaderData(2, Qt::Horizontal, "Почта");

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showInfo() const {
    if (auth.open()) {
        model->clear();
        model->setQuery("SELECT idInfoCompany, nameCompany, phoneContacts, emailContacts FROM InfoCompany "
                        "INNER JOIN Companies ON idCompaniesInfo = idCompanies "
                        "INNER JOIN Contacts ON idContactsInfo = idContacts;", auth);
        tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, "Компания");
        model->setHeaderData(2, Qt::Horizontal, "Номер телефона");
        model->setHeaderData(3, Qt::Horizontal, "Почта");

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showServices() const {
    if (auth.open()) {
        model->clear();
        model->setQuery("SELECT * FROM Services;", auth);
        tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, "id");
        model->setHeaderData(1, Qt::Horizontal, "Услуга");

        tableView->resizeColumnsToContents();
    }
}

void ShowTables::showContracts() const {
    if (auth.open()) {
        model->clear();
        model->setQuery("SELECT numOfContract, DateOfConclusion, Deadline, nameCompany, "
                        "phoneContacts, emailContacts, Service FROM Contracts "
                        "INNER JOIN Services ON idServicesCon = idServices "
                        "INNER JOIN InfoCompany ON idInfoCompanyCon = idInfoCompany "
                        "INNER JOIN Companies ON idCompaniesInfo = idCompanies "
                        "INNER JOIN Contacts ON idContactsInfo = idContacts;", auth);
        tableView->setModel(model);

        model->setHeaderData(0, Qt::Horizontal, "номер контракта");
        model->setHeaderData(1, Qt::Horizontal, "Дата заключения контракта");
        model->setHeaderData(2, Qt::Horizontal, "Дедлайн");
        model->setHeaderData(3, Qt::Horizontal, "Компания");
        model->setHeaderData(4, Qt::Horizontal, "Номер телефона");
        model->setHeaderData(5, Qt::Horizontal, "Почта");
        model->setHeaderData(6, Qt::Horizontal, "Услуга");

        tableView->resizeColumnsToContents();
    }
}
