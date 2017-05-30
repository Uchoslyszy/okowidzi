#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include "Picture.h"

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

    void pokaz(int lol);
    void on_wczytajobraz_clicked();

    void on_tryb1_clicked();

private:
    Ui::MainWindow *ui;

    Picture image;
};

#endif // MAINWINDOW_H
