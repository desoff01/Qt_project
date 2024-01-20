#include "headers/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Kursach_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();
    return a.exec();
}
