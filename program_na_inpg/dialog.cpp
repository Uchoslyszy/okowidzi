#include "dialog.h"
#include "ui_dialog.h"
#include "Picture.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    image.generateHistogram();
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::show_()
{
    int wid = ui->image1->width();
    int hei = ui->image1->height();

    wyswietlenie=QPixmap::fromImage(image.imagePointer());
    ui->image1->setPixmap(wyswietlenie.scaled(wid,hei,Qt::KeepAspectRatio));
}

void Dialog::setImage(Picture new_image)
{
    image.imageCopy(new_image.Width(),new_image.Height(),new_image);
    image.generateHistogram();
}

Picture Dialog::imagePointer()
{
    return image;
}

void Dialog::setSize(int width,int height)
{
    ui->image1->setFixedSize(width,height);
}
