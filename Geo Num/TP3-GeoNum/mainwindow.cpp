#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <math.h>

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
    QObject::connect( ui->BSplines, SIGNAL(clicked()), this, SLOT(lancerBSplines()) );

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

void MainWindow::lancerBSplines(){
    scene->clear();
    dessinerGraphe();
    recupererPoints();
    dessinerCourbe(tab, taille, (Qt::black));
    AlgoBSplines();
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

double MainWindow::omega(int i, int k, double t, double tabP[]){
   if(tabP[i] < tabP[i+k]){
       return ((t -tabP[i])/(tabP[i+k] - tabP[i]));
   }else{
       return 0;
   }
}

int MainWindow::TrouverJ(double t, double tabnoeuds[], int tailleTabNoeuds){ //fonction retournant
    int j= 0;
    bool fini = false;

    while(!fini){
        if(t >= tabnoeuds[j] && t <= tabnoeuds[j+1]){ //valeur trouvée
            fini= true;
        }else if(j > tailleTabNoeuds){ //valeur impossible à trouver
            fini= true;
            j = -1;
        }else{ //continuer l'itération
            j++;
        }
    }
    return j;
}

QPointF MainWindow::PointBSplines(double t){
    //degré de la courbe
    int k = ui->spinBoxDegre->value();

    //table des noeuds
    int m = taille + k;
    int nbNoeuds = m + 1;
    double tabNoeuds[nbNoeuds];
    for (int i = 0; i < nbNoeuds; ++i) {
        tabNoeuds[i] = double(i);
    }

    int j= TrouverJ(t, tabNoeuds, nbNoeuds);

        //calcul du point final de la courbe
        QPointF tabPointsInter[k+1]; //recopie des points de contrôle en local
        for (int i = 0; i < k+1; ++i) {
            tabPointsInter[i] = tab[j-k+i];
        }
        int x,y;
        int nbSousPoints = k+1;
        for (int r = 1; r < k+1; ++r) { //calcul des sous points
            for (int i = 1; i < nbSousPoints; ++i) {
                double om = omega(j - k + r + i - 1,k-r+1,t, tabNoeuds);
                x = (1- om)*tabPointsInter[i-1].x() + om*tabPointsInter[i].x();
                y = (1- om)*tabPointsInter[i-1].y() + om*tabPointsInter[i].y();
                tabPointsInter[i-1] = QPointF(x, y);
                std::cout << "x*" << x << " + y*" << y << std::endl;
            }
            nbSousPoints--;
        }

        std::cout << "valeur du point généré: " << tabPointsInter[0].x() << ";" << tabPointsInter[0].y() << std::endl;
        return tabPointsInter[0];
}

void MainWindow::AlgoBSplines(){
    QPointF result[50];
    int i= 0;
    int k = ui->spinBoxDegre->value();
    for (double t = k; t < taille; t+=0.1) {
        result[i] = PointBSplines(t);
        i++;
    }

    dessinerCourbe(result, (taille - k)*10,(Qt::red));

}
