#include "histogram.h"
#include "ui_histogram.h"
#include "qcustomplot.h"


Histogram::Histogram(QWidget *parent,int *new_blue,int *new_red,int *new_green) :
    QMainWindow(parent),
    ui(new Ui::Histogram)
{
    int i;
    double currentmax=0;
    ui->setupUi(this);

    QVector<double> vector_blue(256);
    for(i=0;i<256;i++)
    {
        vector_blue[i]=new_blue[i];
        if(vector_blue[i]>currentmax)
            currentmax=vector_blue[i];
    }

    QVector<double> vector_red(256);
    for(i=0;i<256;i++)
    {
        vector_red[i]=new_red[i];
        if(vector_red[i]>currentmax)
            currentmax=vector_red[i];
    }

    QVector<double> vector_green(256);
    for(i=0;i<256;i++)
    {
        vector_green[i]=new_green[i];
        if(vector_green[i]>currentmax)
            currentmax=vector_green[i];
    }

    QVector<double> x(256);
    for(i=0;i<256;i++)
        x[i]=i+1;

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x,vector_blue);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QColor(255,0,0,255));
    ui->customPlot->graph(1)->setData(x,vector_red);
    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QColor(0,255,0,255));
    ui->customPlot->graph(2)->setData(x,vector_green);
    ui->customPlot->xAxis->setLabel("color value");
    ui->customPlot->yAxis->setLabel("pixel count");
    ui->customPlot->xAxis->setRange(1,256);
    ui->customPlot->yAxis->setRange(0,currentmax);
    ui->customPlot->replot();
}

Histogram::~Histogram()
{
    delete ui;
}



void Histogram::on_pushButton_clicked()
{
    this->close();
}
