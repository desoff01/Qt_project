#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "headers/globalAuthentication.h"
#include "headers/otables.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEditPasswd->setEchoMode(QLineEdit::Password);
    ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-eye-158746.png"));
    ui->lineEditLogin->setCursorPosition(20);
    ui->labelLogin->setAlignment(Qt::AlignRight);
    ui->labelPasswd->setAlignment(Qt::AlignRight);

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/img/images/b2b.png"));

    connect(ui->pushButtonSignIn, &QPushButton::clicked, this, &MainWindow::pushButtonSignIn_clicked);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &MainWindow::showMinimized);
    connect(ui->pushButtonClose, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->pushButtonShowPass, &QPushButton::clicked, this, &MainWindow::pushButtonShowPass_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButtonSignIn_clicked() {

    ///
    /// getting password hash and username hash
    ///

    QByteArray loginString {hash.getLoginHash(ui->lineEditLogin->text().toStdString())};
    QByteArray passString {hash.getPasswordHash(ui->lineEditPasswd->text().toStdString())};

    // connection settings changed
    auth.setHostName(server);
    auth.setPort(3306);
    auth.setUserName(username);
    auth.setPassword(password);
    auth.setDatabaseName(database);
    if(auth.open()) {
        QSqlQuery q(auth);
        q.prepare("SELECT * FROM Users WHERE username = :username AND password = :password;");
        q.bindValue(":username", loginString.toHex());
        q.bindValue(":password", passString.toHex());
        q.exec();

        if(q.size() > 0) {
            OTables *out {new OTables()};
            this->close();
            out->show();
        }
        else {
            ui->labelStatus->setText("Incorrect Username or password");
        }
    } else {
        ui->labelStatus->setText("Cannot connect to database");
    }
}

void MainWindow::pushButtonShowPass_clicked() {
    if(showPassClicked) {
        showPassClicked = false;
        ui->lineEditPasswd->setEchoMode(QLineEdit::Password);
        ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-eye-158746.png"));
    } else {
        showPassClicked = true;
        ui->lineEditPasswd->setEchoMode(QLineEdit::Normal);
        ui->pushButtonShowPass->setIcon(QIcon(":/img/images/free-icon-hide-2767146.png"));
    }
}

