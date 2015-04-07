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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QLabel *label_3;
    QSpinBox *degK;
    QLabel *label_4;
    QSpinBox *degL;
    QLabel *label;
    QSpinBox *lignes;
    QLabel *label_2;
    QSpinBox *colonnes;
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
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        degK = new QSpinBox(centralWidget);
        degK->setObjectName(QStringLiteral("degK"));
        degK->setMaximum(10);
        degK->setValue(3);

        horizontalLayout_2->addWidget(degK);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_4);

        degL = new QSpinBox(centralWidget);
        degL->setObjectName(QStringLiteral("degL"));
        degL->setMaximum(10);
        degL->setValue(3);

        horizontalLayout_2->addWidget(degL);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        lignes = new QSpinBox(centralWidget);
        lignes->setObjectName(QStringLiteral("lignes"));
        lignes->setMaximumSize(QSize(50, 25));
        lignes->setValue(6);

        horizontalLayout_2->addWidget(lignes);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        colonnes = new QSpinBox(centralWidget);
        colonnes->setObjectName(QStringLiteral("colonnes"));
        colonnes->setMaximumSize(QSize(50, 25));
        colonnes->setValue(6);

        horizontalLayout_2->addWidget(colonnes);


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
        zonePoints->setPlainText(QApplication::translate("MainWindow", "(0;0;0)(2;0;0)(5;0;0)(7;0;0)(10;0;0)(12;0;0)(0;2;0)(2;2;1)(5;2;2)(7;2;3)(10;2;1)(12;2;0)(0;5;0)(2;5;1)(5;5;2)(7;5;3)(10;5;1)(12;5;0)(0;7;0)(2;7;-1)(5;7;-2)(7;7;-3)(10;7;-1)(12;7;0)(0;10;0)(2;10;-1)(5;10;-2)(7;10;-3)(10;10;-1)(12;10;0)(0;12;0)(2;12;0)(5;12;0)(7;12;0)(10;12;0)(12;12;0)", 0));
        label_3->setText(QApplication::translate("MainWindow", "degr\303\251 K", 0));
        label_4->setText(QApplication::translate("MainWindow", "       degr\303\251 L", 0));
        label->setText(QApplication::translate("MainWindow", "  nombre de lignes", 0));
        label_2->setText(QApplication::translate("MainWindow", " nombre de colonnes", 0));
        Algo->setText(QApplication::translate("MainWindow", "Algo", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
