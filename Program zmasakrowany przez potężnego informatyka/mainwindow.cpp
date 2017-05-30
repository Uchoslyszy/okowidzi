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

    //connect(objekt1,sygnał,obiekt2,slot)


    if(QString::compare(filename,QString()) != 0)
    {

        image.imageOpen(filename);
        image.generateHistogram();
        pokaz(1);


    }
}

void MainWindow::pokaz(int choose_label){
    QPixmap qpx_before_image = QPixmap::fromImage(image.imagePointer());
qpx_before_image = qpx_before_image.scaled(471,341,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    if(choose_label==0)
        ui->image2->setPixmap(qpx_before_image);
    if(choose_label==1)
        ui->image1->setPixmap(qpx_before_image);



}

void MainWindow::on_tryb1_clicked()
{
    int x = 3;
    double y = 3;

    //image.lightening(10);
    image.equalFilter(9);
     pokaz(0);

  // ui ->wczytajobraz -> Picture::gaussianBlur(x,y);
}
