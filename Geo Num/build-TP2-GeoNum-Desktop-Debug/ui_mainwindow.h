/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(500, 400));

        verticalLayout_2->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        zonePoints = new QPlainTextEdit(centralWidget);
        zonePoints->setObjectName(QStringLiteral("zonePoints"));
        zonePoints->setMaximumSize(QSize(1000000, 50));

        verticalLayout->addWidget(zonePoints);

        zonePointControle = new QPlainTextEdit(centralWidget);
        zonePointControle->setObjectName(QStringLiteral("zonePointControle"));
        zonePointControle->setMaximumSize(QSize(1000000, 30));

        verticalLayout->addWidget(zonePointControle);


        horizontalLayout->addLayout(verticalLayout);

        zoneBoutons = new QVBoxLayout();
        zoneBoutons->setSpacing(6);
        zoneBoutons->setObjectName(QStringLiteral("zoneBoutons"));
        Bezier = new QPushButton(centralWidget);
        Bezier->setObjectName(QStringLiteral("Bezier"));

        zoneBoutons->addWidget(Bezier);

        Algo1 = new QPushButton(centralWidget);
        Algo1->setObjectName(QStringLiteral("Algo1"));

        zoneBoutons->addWidget(Algo1);

        Algo2 = new QPushButton(centralWidget);
        Algo2->setObjectName(QStringLiteral("Algo2"));

        zoneBoutons->addWidget(Algo2);


        horizontalLayout->addLayout(zoneBoutons);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1200, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(100;300)(300;100)(500;300)(700;100)(900;300)(1100;100)", 0));
        zonePointControle->setPlainText(QApplication::translate("MainWindow", "(100;115)(230;85)", 0));
        Bezier->setText(QApplication::translate("MainWindow", "Bezier", 0));
        Algo1->setText(QApplication::translate("MainWindow", "C1", 0));
        Algo2->setText(QApplication::translate("MainWindow", "C2", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
