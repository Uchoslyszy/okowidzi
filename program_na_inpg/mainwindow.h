#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Picture.h"
#include <QMainWindow>
#include <QPixmap>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    int on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_Gaussian_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void show_();

private:
    QPixmap wyswietlenie;
    Picture image;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
