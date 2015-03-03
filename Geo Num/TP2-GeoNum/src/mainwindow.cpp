#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    this->ui->graphicsView->setScene(this->scene);
    this->setVisible(true);

    QObject::connect( ui->Bezier, SIGNAL(clicked()), this, SLOT(lancerBezier()) );
    QObject::connect( ui->Algo1, SIGNAL(clicked()), this, SLOT(lancerAlgo1()) );
    QObject::connect( ui->Algo2, SIGNAL(clicked()), this, SLOT(lancerAlgo2()) );

    dessinerGraphe();
}

MainWindow::~MainWindow(){
    delete scene;
    delete ui;
}

void MainWindow::lancerBezier(){
    scene->clear();
    dessinerGraphe();
    recupererPoints();
    dessinerCourbe(tab, taille, (Qt::black));
    courbeBezier(tab, taille);
}

void MainWindow::lancerAlgo1(){
    scene->clear();
    dessinerGraphe();
    recupererPoints();
    recupererPointsControles();
    dessinerCourbe(tab, taille, (Qt::black));
    Algo1();
}

void MainWindow::lancerAlgo2(){
    scene->clear();
    dessinerGraphe();
    recupererPoints();
    recupererPointsControles();
    dessinerCourbe(tab, taille, (Qt::black));
    Algo2();
}

int MainWindow::getTaille() const{
    return taille;
}

void MainWindow::setTaille(int value){
    taille = value;
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
        tab[k] = tabPoints[k];
    }

}

void MainWindow::recupererPointsControles(){
    QString contenu = ui->zonePointControle->toPlainText();
    QPointF tabPoints2[2];
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
                tabPoints2[nbPoints-1]= *(new QPointF(0,0));
            }else if(c == (QChar)(';')){ //insèrer la nouvelle valeur X dans le tableau de points et réinitialiser la valeur de 'num'
                tabPoints2[nbPoints-1].setX(num.toFloat());
                num = "";
            }else if(c == (QChar)(')')){ //insèrer la nouvelle valeur Y dans le tableau de points et réinitialiser la valeur de 'num'
                tabPoints2[nbPoints-1].setY(num.toFloat());
                num = "";
            }
        }
    }

    for (int k = 0; k < 2; ++k) {
        tabControle[k] = tabPoints2[k];
    }
}

void MainWindow::dessinerGraphe(){
    QPen YBrush(Qt::black);
    int height = ui->graphicsView->height();
    int width = ui->graphicsView->width();

    scene->addLine(5, 5, 5, height-5, YBrush);
    scene->addLine(5, height-5, width-5, height-5, YBrush);
}

void MainWindow::dessinerCourbe(QPointF tab[], int taille, Qt::GlobalColor coul){
    int bas = ui->graphicsView->height()-5;
    for (int i = 0; i < taille-1; ++i) {
        scene->addLine(5+tab[i].x(), bas-tab[i].y(), 5+tab[i+1].x(), bas-tab[i+1].y(), QPen(coul));
    }
}

void MainWindow::courbeBezier(QPointF tabP[], int t){
    int pas = 11;
    QPointF tabGlobal[pas];
    //sauvegarde
    QPointF tabSauv[t];
    for (int l = 0; l < t; ++l) {
        tabSauv[l] = tabP[l];
    }
    //calcul courbe
    for (int k = 0; k < pas; ++k) {
        for (int j = t-1; j > 0; j--) {
            for (int i = 0; i < j; ++i) {
                float x = ((float)(tabP[i+1].x()) - (float)(tabP[i].x()))*(0.1*k);
                float y = ((float)(tabP[i+1].y()) - (float)(tabP[i].y()))*(0.1*k);
                tabP[i] = *(new QPointF(tabP[i].x()+x,tabP[i].y()+y));
            }
        }
        //sauvegarde du point de la courbe
        float x = ((float)(tabP[1].x()) - (float)(tabP[0].x()))*(0.1*k);
        float y = ((float)(tabP[1].y()) - (float)(tabP[0].y()))*(0.1*k);
        tabGlobal[k] = *(new QPointF(tabP[0].x()+x,tabP[0].y()+y));
        //remise au tab des point initiaux
        for (int l = 0; l < t; ++l) {
            tabP[l] = tabSauv[l];
        }
    }
    //dessin courbe de bezier
    dessinerCourbe(tabGlobal, pas, (Qt::red));
}

void MainWindow::Algo1(){

    QPointF tabinter[3];

    //init
    tabinter[0]= tab[0];
    tabinter[1]= tabControle[0];
    tabinter[2]= tab[1];
    courbeBezier(tabinter,3);

    //boucle
    for (int i = 1; i < taille-1; i++) {
        tabinter[0]= tab[i];
        float x = (2*tabinter[2].x()) - tabinter[1].x();
        float y = (2*tabinter[2].y()) - tabinter[1].y();
        tabinter[1]= *(new QPointF(x,y));
        tabinter[2]= tab[i+1];
        courbeBezier(tabinter,3);
    }
}

void MainWindow::Algo2(){

    QPointF tabinter[4];

    //init
    tabinter[0]= tab[0];
    tabinter[1]= tabControle[0];
    tabinter[2]= tabControle[1];
    tabinter[3]= tab[1];
    courbeBezier(tabinter,4);

    //boucle
    for (int i = 1; i < taille-1; i++) {
        tabinter[0]= tab[i];
        float x1 = tabinter[0].x() + ( tabinter[3].x() - tabinter[2].x() );
        float y1 = tabinter[0].y() + ( tabinter[3].y() - tabinter[2].y() );
        float x2 = 2*x1 - tabinter[0].x() + tabinter[3].x() - (2*tabinter[2].x()) + tabinter[1].x();
        float y2 = 2*y1 - tabinter[0].y() + tabinter[3].y() - (2*tabinter[2].y()) + tabinter[1].y();
        tabinter[1]= *(new QPointF(x1,y1));
        tabinter[2]= *(new QPointF(x2,y2));
        tabinter[3]= tab[i+1];
        courbeBezier(tabinter,4);
    }

}

