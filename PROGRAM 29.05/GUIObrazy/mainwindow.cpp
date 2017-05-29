#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Picture.h"


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
        Picture before_image;
        before_image = Picture(filename);
        ui->image1->setPixmap(QPixmap::fromImage(before_image.image));



    }
}
