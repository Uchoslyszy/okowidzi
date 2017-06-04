#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Picture.h"
#include <QMainWindow>
#include <QPixmap>
#include <QSlider>



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

    void imageShow();

    void on_actionGrayscale_triggered();

    void on_actionGaussian_Blur_triggered();

    void on_actionEqual_Filter_triggered();

    void on_actionPixelate_Filter_triggered();

    void on_actionContrast_triggered();

    void on_actionMedian_Filter_triggered();



private:
    QPixmap wyswietlenie;
    Picture image;

    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
