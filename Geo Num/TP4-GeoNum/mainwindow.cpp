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

    QObject::connect( ui->chaikin, SIGNAL(clicked()), this, SLOT(lancerChaikin()));
    QObject::connect( ui->QuatrePts, SIGNAL(clicked()), this, SLOT(lancer4Pts()));
    QObject::connect( ui->cornerCutting, SIGNAL(clicked()), this, SLOT(lancerCornerCutting()));

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

void MainWindow::lancerChaikin(){
        scene->clear();
        dessinerGraphe();
        recupererPoints();
        dessinerCourbe((Qt::black));
        for (int i = 0; i < 5; ++i) {
            AlgoChaikin();
        }
        dessinerCourbe(Qt::red);

}

void MainWindow::AlgoChaikin(){
    QPointF x1, x2;
    std::vector<QPointF> tab2;
        for (size_t i = 0; i < tab.size()-1; ++i) {
            x1 = tab[i];
            x2 = tab[i+1];
            tab2.push_back( *(new QPointF(0.75*x1.x() + 0.25*x2.x() , 0.75*x1.y() + 0.25*x2.y())) );
            tab2.push_back( *(new QPointF(0.25*x1.x() + 0.75*x2.x() , 0.25*x1.y() + 0.75*x2.y())) );
        }
        tab = tab2;
}

void MainWindow::lancer4Pts(){
    scene->clear();
    dessinerGraphe();
    recupererPoints();
    dessinerCourbe((Qt::black));
    for (int i = 0; i < 5; ++i) {
        Algo4Pts();
    }
    dessinerCourbe(Qt::red);
}

void MainWindow::Algo4Pts(){
    QPointF x1, x2, x3, x4;
    std::vector<QPointF> tab2;
        for (size_t i = 1; i < tab.size()-2; ++i) {
            x1 = tab[i-1];
            x2 = tab[i];
            x3 = tab[i+1];
            x4 = tab[i+2];
            tab2.push_back( x2 );
            QPointF res = *(new QPointF());
            res.setX( 0.0625*( -x1.x() + 9*x2.x() + 9*x3.x() - x4.x() ) );
            res.setY( 0.0625*( -x1.y() + 9*x2.y() + 9*x3.y() - x4.y() ) );
            tab2.push_back( res );
        }
        tab = tab2;
}

void MainWindow::lancerCornerCutting(){

}

