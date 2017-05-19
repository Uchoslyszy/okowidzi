#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_wczytajobraz_clicked()
{
    ui->label->setText("PRZED");
    ui->label_2->setText("PO");

    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.bmp)"));

    if(QString::compare(filename,QString()) != 0)
    {
        QPixmap image;
        bool valid = image.load(filename);

        if(valid)
        {
            int wid = ui->image1->width();
            int hei = ui->image1->height();
           // image = image.scaled(wid, hei, Qt::SmoothTransformation);
            ui->image1->setPixmap(image.scaled(wid,hei,Qt::KeepAspectRatio));
        }
    }
}
