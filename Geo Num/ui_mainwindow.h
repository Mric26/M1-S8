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
    QVBoxLayout *zoneBoutons;
    QPushButton *chaikin;
    QPushButton *QuatrePts;
    QPushButton *cornerCutting;
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


        horizontalLayout->addLayout(verticalLayout);

        zoneBoutons = new QVBoxLayout();
        zoneBoutons->setSpacing(6);
        zoneBoutons->setObjectName(QStringLiteral("zoneBoutons"));
        chaikin = new QPushButton(centralWidget);
        chaikin->setObjectName(QStringLiteral("chaikin"));

        zoneBoutons->addWidget(chaikin);

        QuatrePts = new QPushButton(centralWidget);
        QuatrePts->setObjectName(QStringLiteral("QuatrePts"));

        zoneBoutons->addWidget(QuatrePts);

        cornerCutting = new QPushButton(centralWidget);
        cornerCutting->setObjectName(QStringLiteral("cornerCutting"));

        zoneBoutons->addWidget(cornerCutting);


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
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(100;100)(100;300)(300;300)(300;100)", 0));
        chaikin->setText(QApplication::translate("MainWindow", "chaikin", 0));
        QuatrePts->setText(QApplication::translate("MainWindow", "sh\303\251ma \303\240 4pts", 0));
        cornerCutting->setText(QApplication::translate("MainWindow", "corner-cutting", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
