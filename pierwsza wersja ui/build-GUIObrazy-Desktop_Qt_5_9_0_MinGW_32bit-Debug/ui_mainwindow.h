/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *tryb1;
    QPushButton *tryb2;
    QPushButton *tryb3;
    QPushButton *wczytajobraz;
    QLabel *label;
    QLabel *label_2;
    QLabel *image1;
    QMenuBar *menuBar;
    QMenu *menuPrzerobka_obrazow;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1073, 599);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tryb1 = new QPushButton(centralWidget);
        tryb1->setObjectName(QStringLiteral("tryb1"));
        tryb1->setGeometry(QRect(520, 140, 75, 23));
        tryb2 = new QPushButton(centralWidget);
        tryb2->setObjectName(QStringLiteral("tryb2"));
        tryb2->setGeometry(QRect(520, 170, 75, 23));
        tryb3 = new QPushButton(centralWidget);
        tryb3->setObjectName(QStringLiteral("tryb3"));
        tryb3->setGeometry(QRect(520, 200, 75, 23));
        wczytajobraz = new QPushButton(centralWidget);
        wczytajobraz->setObjectName(QStringLiteral("wczytajobraz"));
        wczytajobraz->setGeometry(QRect(500, 480, 111, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 231, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(610, 10, 251, 31));
        image1 = new QLabel(centralWidget);
        image1->setObjectName(QStringLiteral("image1"));
        image1->setGeometry(QRect(10, 40, 471, 341));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1073, 21));
        menuPrzerobka_obrazow = new QMenu(menuBar);
        menuPrzerobka_obrazow->setObjectName(QStringLiteral("menuPrzerobka_obrazow"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuPrzerobka_obrazow->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tryb1->setText(QApplication::translate("MainWindow", "Tryb 1", Q_NULLPTR));
        tryb2->setText(QApplication::translate("MainWindow", "Tryb 2", Q_NULLPTR));
        tryb3->setText(QApplication::translate("MainWindow", "Tryb 3", Q_NULLPTR));
        wczytajobraz->setText(QApplication::translate("MainWindow", "Wczytaj obraz", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        image1->setText(QString());
        menuPrzerobka_obrazow->setTitle(QApplication::translate("MainWindow", "Przerobka obrazow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
