#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QIcon>
#include <array>
#include "headers/hash.h"

///
/// login window class
///

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pushButtonSignIn_clicked();

    void pushButtonShowPass_clicked();

private:
    Ui::MainWindow *ui;
    bool showPassClicked {false};
    const std::array<int, 3> xorArr {0x10, 0x20, 0x30};
};
#endif // MAINWINDOW_H
