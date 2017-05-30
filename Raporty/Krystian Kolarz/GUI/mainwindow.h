#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
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
    void on_wczytajobraz_clicked();

    void on_tryb1_clicked();

    void wcisniety_przycisk();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
