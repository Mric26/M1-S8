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

    QObject::connect( ui->Courbe, SIGNAL(clicked()), this, SLOT(courbe()));
    QObject::connect( ui->Algo, SIGNAL(clicked()), this, SLOT(lancerAlgo()));

    dessinerGraphe();
}

MainWindow::~MainWindow(){
    delete scene;
    delete ui;
}

int MainWindow::getTaille() const{
    return taille;
}

void MainWindow::setTaille(int value){
    taille = value;
}

void MainWindow::recupererPoints(){ //format du texte: (x1;y1;z1)(x2;y2;z2)...(xn;yn;zn)
    QString contenu = ui->zonePoints->toPlainText();
    nbCols = ui->colonnes->value();
    nbLignes = ui->lignes->value();
    QVector3D tabPoints[nbCols*nbLignes];
    int sizeText = contenu.size();
    int nbPoints = 0;
    QString num= NULL;
    bool deuxiemeValeur= false;

    for (int i = 0; i < sizeText; ++i) {
        QChar c = contenu.at(i); //récupération du caractère
        if (c.isNumber()){ //récupération d'un digit
            num += (QString)(c);
        }else{
            if(c ==  '('){
                nbPoints++;
                tabPoints[nbPoints-1]= *(new QVector3D(0,0,0));
                deuxiemeValeur= false;
            }else if(c == (QChar)(';')){ //insèrer la nouvelle valeur X ou Y dans le tableau de points et réinitialiser la valeur de 'num'
                if(!deuxiemeValeur){ //on enregistre la premiere valeur
                    tabPoints[nbPoints-1].setX(num.toFloat());
                    num = "";
                    deuxiemeValeur = true;
                }else{ //on enregistre la deuxième valeur
                    tabPoints[nbPoints-1].setY(num.toFloat());
                    num = "";
                }
            }else if(c == (QChar)(')')){ //insèrer la nouvelle valeur Z dans le tableau de points et réinitialiser la valeur de 'num'
                tabPoints[nbPoints-1].setZ(num.toFloat());
                num = "";
            }
        }
    }

    for (int L = 0; L < nbLignes; ++L) {
        matricePts.push_back(std::vector<QVector3D>());
         for (int k = 0; k < nbCols; ++k){
            matricePts[L].push_back(tabPoints[ L*nbCols + k]);
        }
    }
}

void MainWindow::dessinerGraphe(){
    QPen YBrush(Qt::black);
    int height = ui->graphicsView->height();
    int width = ui->graphicsView->width();

    scene->addLine(5, 5, 5, height-5, YBrush);
    scene->addLine(5, height-5, width-5, height-5, YBrush);
}

void MainWindow::dessinerCourbe(Qt::GlobalColor coul){
    int bas = ui->graphicsView->height()-5;
    for (size_t i = 0; i < tab.size()-1; ++i) {
        QPointF p1 = tab[i];
        QPointF p2 = tab[i+1];
        scene->addLine(5+p1.x(), bas-p1.y(), 5+p2.x(), bas-p2.y(), QPen(coul));
    }
}

void MainWindow::courbe(){
    scene->clear();
    dessinerGraphe();
    tab.clear();
    recupererPoints();
    afficherMatrice();
}

void MainWindow::afficherMatrice(){
    for (int i = 0; i < nbLignes; ++i) {
        for (int j = 0; j < nbCols; ++j) {
            std::cout << "(" << matricePts[i].at(j).x() << ";" << matricePts[i].at(j).y() << ";" << matricePts[i].at(j).z() << ") ";
        }
        std::cout << std::endl;
    }
}

void MainWindow::lancerAlgo(){
        matricePts.clear();
        scene->clear();
        dessinerGraphe();
        tab.clear();
        recupererPoints();
        dessinerCourbe((Qt::black));
        Algo();
        dessinerCourbe(Qt::red);
}

void MainWindow::Algo(){
}

void MainWindow::courbeBezier( QPointF tab[] ){
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
            //dessine pour t = 0.3
            if( k == 3){
//                dessinerCourbe(tab,j, (Qt::green));
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
    //dessin courbe de bezier
//    dessinerCourbe(tabGlobal, 10, (Qt::red));
}


