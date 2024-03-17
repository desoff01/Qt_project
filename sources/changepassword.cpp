#include "headers/changepassword.h"
#include "ui_changepassword.h"
#include "headers/hash.h"
#include "headers/globalAuthentication.h"
#include <QMessageBox>
#include <QSqlQuery>

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->lineEditCurrPasswd->setEchoMode(QLineEdit::Password);
    ui->lineEditNewPasswd->setEchoMode(QLineEdit::Password);
    ui->lineEditRepNewPasswd->setEchoMode(QLineEdit::Password);

    connect(ui->pushButtonClose, &QPushButton::clicked, this, &ChangePassword::close);
    connect(ui->pushButtonMinimize, &QPushButton::clicked, this, &ChangePassword::showMinimized);
    connect(ui->pushButtonChangePasswd, &QPushButton::clicked,
            this, &ChangePassword::pushButtonChangePasswd_clicked);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::pushButtonChangePasswd_clicked() {
    if(auth.open()) {
        QByteArray currPass {hash.getPasswordHash(ui->lineEditCurrPasswd->text().toStdString())};

        QSqlQuery q(auth);
        q.prepare("SELECT idUsers FROM Users WHERE username = :username AND password = :password;");
        q.bindValue(":username", hash.getSavedLogin().toHex());
        q.bindValue(":password", currPass.toHex());
        q.exec();

        if(q.size() > 0) {
            if (ui->lineEditNewPasswd->text() == ui->lineEditRepNewPasswd->text()) {
                q.first();
                int idUsers {q.value(0).toInt()};
                q.clear();

                q.prepare("UPDATE Users SET `password` = :newPass WHERE (`idUsers` = :id);");
                q.bindValue(":id", idUsers);
                q.bindValue(":newPass", hash.getPasswordHash(ui->lineEditNewPasswd->text().toStdString()).toHex());
                q.exec();

                ui->labelStatus->setText(tr("Пароль изменён"));
                ui->labelStatus->setStyleSheet("color: #63c71c");
            } else {
                ui->labelStatus->setText(tr("Пароли не совпадают"));
                ui->labelStatus->setStyleSheet("color: #c71c1c");
            }
        } else {
            ui->labelStatus->setText(tr("Неверный текущий пароль"));
            ui->labelStatus->setStyleSheet("color: #c71c1c");
        }
    } else {
        ui->labelStatus->setText(tr("Не удаётся подключиться к базе данных")); // Cannot connect to database
        ui->labelStatus->setStyleSheet("color: #c71c1c");
    }
}
