#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "Picture.h"
#include "QFileDialog"
#include "QRect"
#include "QScreen"
#include "QSlider"

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


int MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.bmp)"));

    if(QString::compare(filename,QString()) != 0)
        {
            QScreen *screen = QGuiApplication::primaryScreen();
             QRect  screenGeometry = screen->geometry();
            int height=ui->image1->height();
            int width=ui->image1->width();

            image.imageOpen(filename);

            wyswietlenie=QPixmap::fromImage(image.imagePointer());

            ui->image1->setPixmap(wyswietlenie.scaled(width,height,Qt::KeepAspectRatio));

        }
}




void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Choose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename,QString()) != 0)
        image.imageSave(filename);
}



void MainWindow::imageShow()
{
    int wid = ui->image1->width();
    int hei = ui->image1->height();


    wyswietlenie=QPixmap::fromImage(image.imagePointer());
    ui->image1->setPixmap(wyswietlenie.scaled(wid,hei,Qt::KeepAspectRatio));
}

void MainWindow::on_actionGrayscale_triggered()
{

    image.grayscaling();

    imageShow();
}

void MainWindow::on_actionGaussian_Blur_triggered()
{
    image.gaussianBlur(7,3);

    imageShow();
}

void MainWindow::on_actionEqual_Filter_triggered()
{

    image.equalFilter(10);

    imageShow();
}

void MainWindow::on_actionPixelate_Filter_triggered()
{


    image.pixelizeFilter(20);

    imageShow();

}

void MainWindow::on_actionContrast_triggered()
{
    image.contrast(2,5);

    imageShow();
}

void MainWindow::on_actionMedian_Filter_triggered()
{
    image.medianFilter(3);

    imageShow();
}


