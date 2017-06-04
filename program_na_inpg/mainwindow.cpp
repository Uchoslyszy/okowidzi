#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "Picture.h"
#include "QFileDialog"
#include "QRect"
#include "QScreen"
#include "QInputDialog"
#include "QMessageBox"

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
            int height=0.9*screenGeometry.height();
            int width=0.9*screenGeometry.width();

            image.imageOpen(filename);

            wyswietlenie=QPixmap::fromImage(image.imagePointer());
            if(this->width()<width || this->height()<height)
                this->resize(width,height);
            ui->image1->resize(width,height);
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
    int   mask_size=2;
    double sigma;
    bool ok;


    mask_size=QInputDialog::getInt(this, tr("Gaussian Blur"),tr("Mask Size(has to be an odd number: "),QLineEdit::Normal,3,29,1,&ok);

    if(mask_size%2==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Mask size wasn't odd");
        msgBox.exec();
        return;
    }

    if(!ok)
        return;

    sigma=QInputDialog::getDouble(this,tr("Sigma Value"),tr("Sigma: "),QLineEdit::Normal,0,10,4,&ok);
    if(!ok)
        return;

    image.gaussianBlur(mask_size,sigma);

    imageShow();
}

void MainWindow::on_actionEqual_Filter_triggered()
{
    int mask_size=2;
    bool ok;

    mask_size=QInputDialog::getInt(this, tr("Equal filter"),tr("Mask Size(has to be an odd number: "),QLineEdit::Normal,3,29,1,&ok);
    if(mask_size%2==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Mask size wasn't odd");
        msgBox.exec();
        return;
    }

    if(!ok)
        return;

    image.equalFilter(mask_size);

    imageShow();
}

void MainWindow::on_actionPixelate_Filter_triggered()
{
    int pixel_size;
    bool ok;
    pixel_size=QInputDialog::getInt(this,tr("Pixelate Filter"),tr("New Pixel Size: "),QLineEdit::Normal,1,1000,1,&ok);
    if(!ok)
        return;

    image.pixelizeFilter(pixel_size);

    imageShow();

}

void MainWindow::on_actionContrast_triggered()
{
    int value1,value2;
    bool ok;
    value1=QInputDialog::getInt(this,tr(" "),tr(" "),QLineEdit::Normal,1,1000,1,&ok);
    if(!ok)
        return;
    value2=QInputDialog::getInt(this,tr(" "),tr(" "),QLineEdit::Normal,1,1000,1,&ok);
    if(!ok)
        return;

    image.contrast(value1,value2);

    imageShow();
}

void MainWindow::on_actionMedian_Filter_triggered()
{
    bool ok;
    int mask_size=2;

    mask_size=QInputDialog::getInt(this, tr("Median Filter"),tr("Mask Size(has to be an odd number: "),QLineEdit::Normal,3,29,1,&ok);
    if(mask_size%2==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Mask size wasn't odd");
        msgBox.exec();
        return;
    }

    if(!ok)
        return;
    image.medianFilter(mask_size);

    imageShow();
}

void MainWindow::on_actionLighten_triggered()
{
    bool ok;
    int steps;
    steps=QInputDialog::getInt(this,tr("Lighten"),tr("Number of steps to lighten the image: "),QLineEdit::Normal,-256,256,1,&ok);
    if(!ok)
        return;

    image.lightening(steps);
    imageShow();

}
