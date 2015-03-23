#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setVisible(true);

    QObject::connect( ui->Algo, SIGNAL(clicked()), this, SLOT(lancerAlgo()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::recupererPoints(){ //format du texte: (x1;y1)(x2;y2)...(xn;yn)
    QString contenu = ui->zonePoints->toPlainText();
    QPointF tabPoints[50];
    int sizeText = contenu.size();
    int nbPoints = 0;
    QString num= NULL;

    for (int i = 0; i < sizeText; ++i) {
        QChar c = contenu.at(i); //récupération du caractère
        if (c.isNumber()){ //récupération d'un digit
            num += (QString)(c);
        }else{
            if(c ==  '('){
                nbPoints++;
                tabPoints[nbPoints-1]= *(new QPointF(0,0));
            }else if(c == (QChar)(';')){ //insèrer la nouvelle valeur X dans le tableau de points et réinitialiser la valeur de 'num'
                tabPoints[nbPoints-1].setX(num.toFloat());
                num = "";
            }else if(c == (QChar)(')')){ //insèrer la nouvelle valeur Y dans le tableau de points et réinitialiser la valeur de 'num'
                tabPoints[nbPoints-1].setY(num.toFloat());
                num = "";
            }
        }
    }

    taille = nbPoints;
    for (int k = 0; k < taille; ++k) {
        tab.push_back(tabPoints[k]);
    }

}

void MainWindow::lancerAlgo(){
        tab.clear();
        recupererPoints();
        Algo();
}

void MainWindow::Algo(){
    for (int k = 0; k < taille; ++k) {
        QString p = pointToString(k, tab[k] );
        ui->zoneSortie->setText( ui->zoneSortie->toPlainText() + p );
    }
}

void MainWindow::courbeBezier( vector<QPointF> tab ){
    QPointF tabGlobal[10];
    //sauvegarde
    QPointF tabSauv[taille];
    for (int l = 0; l < taille; ++l) {
        tabSauv[l] = tab[l];
    }
    //calcul courbe
    for (int k = 0; k < 10; ++k) {
        for (int j = taille-1; j > 0; j--) {
            for (int i = 0; i < j; ++i) {
                float x = ((float)(tab[i+1].x()) - (float)(tab[i].x()))*(0.1*k);
                float y = ((float)(tab[i+1].y()) - (float)(tab[i].y()))*(0.1*k);
                tab[i] = *(new QPointF(tab[i].x()+x,tab[i].y()+y));
            }
        }
        //sauvegarde du point de la courbe
        float x = ((float)(tab[1].x()) - (float)(tab[0].x()))*(0.1*k);
        float y = ((float)(tab[1].y()) - (float)(tab[0].y()))*(0.1*k);
        tabGlobal[k] = *(new QPointF(tab[0].x()+x,tab[0].y()+y));
        //remise au tab des point initiaux
        for (int l = 0; l < taille; ++l) {
            tab[l] = tabSauv[l];
        }
    }
    //resultats
    for (int k = 0; k < 10; ++k) {
        QString p = pointToString(k, tabGlobal[k] );
        ui->zoneSortie->setText( p );
    }
}

QString MainWindow::pointToString( int indice, QPointF p ){
    string temp = "P" + to_string(indice) + " : " + to_string(p.x()) + " ; " + to_string(p.y()) + " )";
    QString res = "Yolo \n";
    return res;
}


