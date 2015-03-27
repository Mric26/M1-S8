/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
<<<<<<< HEAD
** Created by: Qt User Interface Compiler version 5.3.0
=======
** Created by: Qt User Interface Compiler version 5.2.1
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
<<<<<<< HEAD
=======
#include <QtWidgets/QLabel>
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *zoneSortie;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *zonePoints;
    QHBoxLayout *horizontalLayout_2;
<<<<<<< HEAD
    QSpinBox *hauteur;
    QSpinBox *largeur;
=======
    QLabel *label;
    QSpinBox *lignes;
    QLabel *label_2;
    QSpinBox *colonnes;
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4
    QVBoxLayout *zoneBoutons;
    QPushButton *Algo;
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
        zoneSortie = new QTextEdit(centralWidget);
        zoneSortie->setObjectName(QStringLiteral("zoneSortie"));
        zoneSortie->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout_2->addWidget(zoneSortie);

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

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
<<<<<<< HEAD
        hauteur = new QSpinBox(centralWidget);
        hauteur->setObjectName(QStringLiteral("hauteur"));
        hauteur->setMaximumSize(QSize(50, 25));
        hauteur->setValue(3);

        horizontalLayout_2->addWidget(hauteur);

        largeur = new QSpinBox(centralWidget);
        largeur->setObjectName(QStringLiteral("largeur"));
        largeur->setMaximumSize(QSize(50, 25));
        largeur->setValue(4);

        horizontalLayout_2->addWidget(largeur);
=======
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lignes = new QSpinBox(centralWidget);
        lignes->setObjectName(QStringLiteral("lignes"));
        lignes->setMaximumSize(QSize(50, 25));

        horizontalLayout_2->addWidget(lignes);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        colonnes = new QSpinBox(centralWidget);
        colonnes->setObjectName(QStringLiteral("colonnes"));
        colonnes->setMaximumSize(QSize(50, 25));

        horizontalLayout_2->addWidget(colonnes);
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);

        zoneBoutons = new QVBoxLayout();
        zoneBoutons->setSpacing(6);
        zoneBoutons->setObjectName(QStringLiteral("zoneBoutons"));
        Algo = new QPushButton(centralWidget);
        Algo->setObjectName(QStringLiteral("Algo"));

        zoneBoutons->addWidget(Algo);


        horizontalLayout->addLayout(zoneBoutons);


        verticalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
<<<<<<< HEAD
        menuBar->setGeometry(QRect(0, 0, 1200, 19));
=======
        menuBar->setGeometry(QRect(0, 0, 1200, 20));
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4
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
<<<<<<< HEAD
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(100;100)(100;300)(300;300)(300;100)", 0));
=======
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(100;100;100)(100;200;300)(300;350;300)(300;200;100)", 0));
        label->setText(QApplication::translate("MainWindow", "                                                                                           nombre de lignes", 0));
        label_2->setText(QApplication::translate("MainWindow", "                                                                                     nombre de colonnes", 0));
>>>>>>> 21ed75b06b0e3152b02cf2c4b44d94a4a6e7fed4
        Algo->setText(QApplication::translate("MainWindow", "Algo", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
