#include "headers/otables.h"
#include "ui_otables.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include "headers/dialogaddtables.h"
#include "headers/dialogdeltables.h"
#include "headers/dialogedittables.h"
#include "headers/mainwindow.h"
#include "headers/dataimport.h"
#include "headers/globalAuthentication.h"
#include <QFileDialog>
#include <QTextStream>

OTables::OTables(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OTables)
{
    ui->setupUi(this);

    ui->tableView->verticalHeader()->setVisible(false);

    setWindowIcon(QIcon(":/img/images/b2b.png"));

    showTables = new ShowTables(ui->tableView);

    menuSettings = new QAction("Настройки...", this);
    menuOpenPDF = new QAction("Открыть PDF...", this);
    menuExit = new QAction("Выйти", this);
    ui->menubar->addAction(menuSettings);
    ui->menubar->addAction(menuOpenPDF);
    ui->menubar->addMenu("|")->setEnabled(false);
    ui->menubar->addAction(menuExit);

    connect(ui->pushButtonCompanies, &QPushButton::clicked, this, &OTables::pushButtonCompanies_clicked);
    connect(ui->pushButtonContacts, &QPushButton::clicked, this, &OTables::pushButtonContacts_clicked);
    connect(ui->pushButtonInfo, &QPushButton::clicked, this, &OTables::pushButtonInfo_clicked);
    connect(ui->pushButtonServices, &QPushButton::clicked, this, &OTables::pushButtonServices_clicked);
    connect(ui->pushButtonContracts, &QPushButton::clicked, this, &OTables::pushButtonContracts_clicked);

    connect(ui->actionAddEntry, &QAction::triggered, this, &OTables::AddEntry_triggered);
    connect(ui->actionEditEntry, &QAction::triggered, this, &OTables::EditEntry_triggered);
    connect(ui->actionDelEntry, &QAction::triggered, this, &OTables::DelEntry_triggered);

    connect(ui->actionImportTable, &QAction::triggered, this, &OTables::ImportTable_triggered);
    connect(ui->actionExportTable, &QAction::triggered, this, &OTables::ExportTable_triggered);

    connect(menuSettings, &QAction::triggered, this, &OTables::menuSettings_triggered);
    connect(menuOpenPDF, &QAction::triggered, this, &OTables::menuOpenPDF_triggered);

    connect(menuExit, &QAction::triggered, this, &OTables::menuExit_triggered);

    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &OTables::lineEditSearch_textChanged);
}

OTables::~OTables()
{
    delete showTables;
    delete ui;

    delete menuSettings;
    delete menuOpenPDF;
    delete menuExit;
}

void OTables::pushButtonCompanies_clicked() {
    st = SelectTables::COMPANIES;
    showTables->showCompanies();
}

void OTables::pushButtonContacts_clicked() {
    st = SelectTables::CONTACTS;
    showTables->showContacts();
}

void OTables::pushButtonInfo_clicked() {
    st = SelectTables::INFO;
    showTables->showInfo();
}

void OTables::pushButtonServices_clicked() {
    st = SelectTables::SERVICES;
    showTables->showServices();
}

void OTables::pushButtonContracts_clicked() {
    st = SelectTables::CONTRACTS;
    showTables->showContracts();
}

void OTables::AddEntry_triggered() {
    auto add (std::make_unique<DialogAddTables>());
    add->exec();
    updateTable();
}

void OTables::EditEntry_triggered() {
    auto edit (std::make_unique<DialogEditTables>());
    edit->exec();
    updateTable();
}

void OTables::DelEntry_triggered() {
    auto del (std::make_unique<DialogDelTables>());
    del->exec();
    updateTable();
}

void OTables::ImportTable_triggered() {
    auto di (std::make_unique<DataImport>());
    di->exec();
}

///
/// export the output table as a csv file
///

void OTables::ExportTable_triggered() {
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName {QFileDialog::getSaveFileName(0, "Save file",
            QCoreApplication::applicationDirPath(), filters, &defaultFilter)};

    QFile file(fileName);

    QAbstractItemModel *model {ui->tableView->model()};

    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;

        for (int i {0}; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
            else
                strList.append("");
        }

        data << strList.join(",") << "\n";

        for (int i {0}; i < model->rowCount(); i++) {
            strList.clear();
            for (int j {0}; j < model->columnCount(); j++) {
                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append(model->data(model->index(i, j)).toString());
                else
                    strList.append("");
            }
            data << strList.join(",") + "\n";
        }
        file.close();
    }
}

// not implemented
void OTables::menuSettings_triggered() {
    QMessageBox::information(this, "Header", "Menu Settings pressed");
}

// not implemented
void OTables::menuOpenPDF_triggered() {
    QMessageBox::information(this, "Header", "Menu Open PDF pressed");
}

void OTables::menuExit_triggered() {
    MainWindow *wnd {new MainWindow};
    wnd->show();

    this->close();
}

///
/// search in the table according to the entered string
///

void OTables::lineEditSearch_textChanged(const QString &arg1) {
    if (arg1 != nullptr) {
        for (int i {0}; i <= ui->tableView->model()->columnCount(); i++) {
            for (int j {0}; j <= ui->tableView->model()->rowCount(); j++) {
                QModelIndex ind {ui->tableView->model()->index(j, i)};

                if (ind.data().toString() == ui->lineEditSearch->text()) {
                    ui->tableView->selectRow(j);
                    break;
                }
            }
        }
    }
}

///
/// Needed to display the table after changing the data
///

void OTables::updateTable() const {
    switch (st) {
    case SelectTables::COMPANIES:
        showTables->showCompanies();
        break;
    case SelectTables::CONTACTS:
        showTables->showContacts();
        break;
    case SelectTables::INFO:
        showTables->showInfo();
        break;
    case SelectTables::SERVICES:
        showTables->showServices();
        break;
    case SelectTables::CONTRACTS:
        showTables->showContracts();
        break;
    }
}

