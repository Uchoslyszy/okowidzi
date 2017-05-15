#ifndef TESTOWY_APP_H
#define TESTOWY_APP_H

#include <QMainWindow>

namespace Ui {
class Testowy_app;
}

class Testowy_app : public QMainWindow
{
    Q_OBJECT

public:
    explicit Testowy_app(QWidget *parent = 0);
    ~Testowy_app();

private slots:
    void on_costamButton_clicked();

    void on_actionZapisz_triggered();

    void on_actionOtworz_triggered();

private:
    Ui::Testowy_app *ui;
};

#endif // TESTOWY_APP_H
