#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "Picture.h"
#include "QFileDialog"
#include "QRect"
#include "QScreen"

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
            int height=0.5*screenGeometry.height();
            int width=0.5*screenGeometry.width();

            image.imageOpen(filename);
            int wid=ui->image1->width();
            int hei=ui->image1->height();
            wyswietlenie=QPixmap::fromImage(image.imagePointer());
            ui->image1->setPixmap(wyswietlenie.scaled(wid,hei,Qt::KeepAspectRatio));

        }
}




void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Choose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename,QString()) != 0)
        image.imageSave(filename);
}



void MainWindow::on_Gaussian_clicked()
{
    image.gaussianBlur(7,3);

    show_();
}

void MainWindow::on_pushButton_clicked()
{
    image.pixelizeFilter(20);

    show_();

}

void MainWindow::on_pushButton_2_clicked()
{
    image.equalFilter(10);

    show_();
}

void MainWindow::on_pushButton_3_clicked()
{
    image.medianFilter(3);

    show_();
}

void MainWindow::on_pushButton_4_clicked()
{
    image.grayscaling();

    show_();
}

void MainWindow::on_pushButton_5_clicked()
{
    image.contrast(2,5);

    show_();
}

void MainWindow::show_()
{
    int wid = ui->image1->width();
    int hei = ui->image1->height();

    wyswietlenie=QPixmap::fromImage(image.imagePointer());
    ui->image1->setPixmap(wyswietlenie.scaled(wid,hei,Qt::KeepAspectRatio));
}
