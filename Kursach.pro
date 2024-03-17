QT       += core gui sql pdfwidgets widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    sources/pdfviewer.cpp \
    sources/changepassword.cpp \
    sources/hash.cpp \
    sources/settings.cpp \
    sources/addqueries.cpp \
    sources/dataimport.cpp \
    sources/dialogaddtables.cpp \
    sources/dialogdeltables.cpp \
    sources/dialogedittables.cpp \
    sources/globalAuthentication.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/otables.cpp \
    sources/showtable.cpp \
    sources/pageselector.cpp \
    sources/zoomselector.cpp

HEADERS += \
    headers/pdfviewer.h \
    headers/changepassword.h \
    headers/settings.h \
    headers/addqueries.h \
    headers/dataimport.h \
    headers/dialogaddtables.h \
    headers/dialogdeltables.h \
    headers/dialogedittables.h \
    headers/globalAuthentication.h \
    headers/mainwindow.h \
    headers/otables.h \
    headers/showtable.h \
    headers/hash.h \
    headers/pageselector.h \
    headers/zoomselector.h

FORMS += \
    forms/changepassword.ui \
    forms/dataimport.ui \
    forms/dialogaddtables.ui \
    forms/dialogdeltables.ui \
    forms/dialogedittables.ui \
    forms/mainwindow.ui \
    forms/otables.ui \
    forms/pdfviewer.ui \
    forms/settings.ui

TRANSLATIONS += \
    Kursach_en_US.ts \
    Kursach_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

#INCLUDEPATH += /usr/include/qt6/QtPdfWidgets
#INCLUDEPATH += /usr/include/qt6/QtPdf
#INCLUDEPATH += /usr/include/qt/QtPdf

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
