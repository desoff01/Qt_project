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

    std::string username = ui->lineEditLogin->text().toStdString();
    for (size_t i {0}; i < username.length(); i++) {
        username[i] ^= xorArr[i % 3] + 1;
    }
    std::string password = ui->lineEditPasswd->text().toStdString();
    for (size_t i {0}; i < password.length(); i++) {
        password[i] ^= xorArr[i % 3] + 3;
    }

    QCryptographicHash hash(QCryptographicHash::Sha1);
    QByteArray byteArr(username.c_str());
    hash.addData(byteArr);
    hash.addData("th1s-i5_S01t");
    QByteArray userString {hash.result()};

    hash.reset();

    byteArr = password.c_str();
    hash.addData(byteArr);
    hash.addData("PT_h4ckDa9s");
    QByteArray passString {hash.result()};

    // connection settings changed
    auth.setHostName(HostName);
    auth.setPort(3306);
    auth.setUserName(UserName);
    auth.setPassword(Password);
    auth.setDatabaseName(DatabaseName);
    if(auth.open()) {
        QSqlQuery q(auth);
        q.prepare("SELECT * FROM Users WHERE username = :username AND password = :password;");
        q.bindValue(":username", userString.toHex());
        q.bindValue(":password", passString.toHex());
        q.exec();

        if(q.size() > 0) {
            OTables *out {new OTables()};
            this->close();
            out->show();
        }
        else {
            QMessageBox::information(this, "Authentication", "Incorrect Username or password");
        }
    } else {
        QMessageBox::critical(this, "Cannot connect to database", "Check your internet connection");
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

