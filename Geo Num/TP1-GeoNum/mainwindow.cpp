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

    QObject::connect( ui->OK, SIGNAL(clicked()), this, SLOT(lancer()) );

    dessinerGraphe();
}

MainWindow::~MainWindow(){
    delete scene;
    delete ui;
}

void MainWindow::lancer(){
    recupererPoints();
    dessinerCourbe(tab, taille, (Qt::black));
    courbeBezier();
}
int MainWindow::getTaille() const
{
    return taille;
}

void MainWindow::setTaille(int value)
{
    taille = value;
}


void MainWindow::recupererPoints(){ //format du texte: (x1;y1)(x2;y2)...(xn;yn)
    QString contenu = ui->zoneTexte->toPlainText();
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

    for (int j = 0; j < nbPoints; ++j) {
        std::cout << "x: " << tabPoints[j].x() << " y: " << tabPoints[j].y() << std::endl;
    }

    taille = nbPoints;
    //*tab = *(new QPointF[taille]);
    for (int k = 0; k < taille; ++k) {
        tab[k] = tabPoints[k];
    }

    std::cout << "valeur de 'taille': " << std::endl;
    std::cout << taille << std::endl;
    std::cout << "contenu de la table de points" << std::endl;
    for (int j = 0; j < nbPoints; ++j) {
        std::cout << "x: " << tab[j].x() << " y: " << tab[j].y() << std::endl;
    }

//    tab[0] = *(new QPointF(100,100));
//    tab[1] = *(new QPointF(200,200));
//    tab[2] = *(new QPointF(300,300));
//    tab[3] = *(new QPointF(400,300));
//    tab[4] = *(new QPointF(500,200));

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

void MainWindow::courbeBezier(){
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
                dessinerCourbe(tab,j, (Qt::green));
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
    dessinerCourbe(tabGlobal, 10, (Qt::red));
}

