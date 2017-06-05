#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QMainWindow>

namespace Ui {
class Histogram;
}

class Histogram : public QMainWindow
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = 0,int *new_blue=NULL,int *new_red=NULL,int *new_green=NULL);
    ~Histogram();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Histogram *ui;

};

#endif // HISTOGRAM_H
