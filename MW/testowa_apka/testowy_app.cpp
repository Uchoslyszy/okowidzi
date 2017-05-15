#include "testowy_app.h"
#include "ui_testowy_app.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Testowy_app::Testowy_app(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Testowy_app)
{
    ui->setupUi(this);
}

Testowy_app::~Testowy_app()
{
    delete ui;
}

void Testowy_app::on_costamButton_clicked()
{
    QCoreApplication::quit();
}

void Testowy_app::on_actionZapisz_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz Plik"), QString(),
                                                    tr("Pliki Tekstowe (*.txt);; Pliki C++ (*.cpp *.h"));
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, tr("Blad"),tr ("Nie udalo sie zapisac"));

        }else {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();
        }
    }
}

void Testowy_app::on_actionOtworz_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Otworz Plik"), QString(),
                                                    tr("Pliki Tekstowe (*.txt);;Pliki C++ (*.cpp *.h)"));

    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, tr("Blad"),tr ("Nie udalo sie otworzyc pliku"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}
