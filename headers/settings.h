#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTranslator>

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = nullptr);
    ~settings();

private slots:
    void radioButtonRu_clicked();
    void radioButtonEn_clicked();
    void comboBoxFontSize_currentTextChanged(const QString& fontSize);
    void pushButtonChangePasswd_clicked();

private:
    Ui::settings *ui;
};

#endif // SETTINGS_H
