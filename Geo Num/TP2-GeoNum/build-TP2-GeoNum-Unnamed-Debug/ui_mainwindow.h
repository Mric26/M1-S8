/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *zonePoints;
    QPlainTextEdit *zonePointControle;
    QVBoxLayout *zoneBoutons;
    QPushButton *Bezier;
    QPushButton *Algo1;
    QPushButton *Algo2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(500, 400));

        verticalLayout_2->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        zonePoints = new QPlainTextEdit(centralWidget);
        zonePoints->setObjectName(QString::fromUtf8("zonePoints"));
        zonePoints->setMaximumSize(QSize(1000000, 50));

        verticalLayout->addWidget(zonePoints);

        zonePointControle = new QPlainTextEdit(centralWidget);
        zonePointControle->setObjectName(QString::fromUtf8("zonePointControle"));
        zonePointControle->setMaximumSize(QSize(1000000, 30));

        verticalLayout->addWidget(zonePointControle);


        horizontalLayout->addLayout(verticalLayout);

        zoneBoutons = new QVBoxLayout();
        zoneBoutons->setSpacing(6);
        zoneBoutons->setObjectName(QString::fromUtf8("zoneBoutons"));
        Bezier = new QPushButton(centralWidget);
        Bezier->setObjectName(QString::fromUtf8("Bezier"));

        zoneBoutons->addWidget(Bezier);

        Algo1 = new QPushButton(centralWidget);
        Algo1->setObjectName(QString::fromUtf8("Algo1"));

        zoneBoutons->addWidget(Algo1);

        Algo2 = new QPushButton(centralWidget);
        Algo2->setObjectName(QString::fromUtf8("Algo2"));

        zoneBoutons->addWidget(Algo2);


        horizontalLayout->addLayout(zoneBoutons);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(100;300)(300;100)(500;300)(700;100)(900;300)(1100;100)", 0, QApplication::UnicodeUTF8));
        zonePointControle->setPlainText(QApplication::translate("MainWindow", "(100;115)(230;85)", 0, QApplication::UnicodeUTF8));
        Bezier->setText(QApplication::translate("MainWindow", "Bezier", 0, QApplication::UnicodeUTF8));
        Algo1->setText(QApplication::translate("MainWindow", "C1", 0, QApplication::UnicodeUTF8));
        Algo2->setText(QApplication::translate("MainWindow", "C2", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
