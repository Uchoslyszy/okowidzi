#ifndef DIALOG_H
#define DIALOG_H
#include "Picture.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void show_();
    void setSize(int width,int height);
    void setImage(Picture new_image);
    Picture imagePointer();
    ~Dialog();

private:
    QPixmap wyswietlenie;

    Picture image;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
