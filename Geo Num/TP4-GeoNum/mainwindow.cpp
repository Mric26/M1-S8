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
    QObject::connect( ui->chaikin, SIGNAL(clicked()), this, SLOT(lancerChaikin()));
    QObject::connect( ui->QuatrePts, SIGNAL(clicked()), this, SLOT(lancer4Pts()));
    QObject::connect( ui->quatreptgene, SIGNAL(clicked()), this, SLOT(lancer4PtsG()));
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

void MainWindow::courbe(){
    scene->clear();
    dessinerGraphe();
    tab.clear();
    recupererPoints();
    dessinerCourbe((Qt::black));
}

void MainWindow::lancerChaikin(){
        scene->clear();
        dessinerGraphe();
        tab.clear();
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
    tab.clear();
    recupererPoints();
    dessinerCourbe((Qt::black));
    for (int i = 0; i < 8; ++i) {
        Algo4Pts();
    }
    dessinerCourbe(Qt::red);
}

void MainWindow::Algo4Pts(){
    QPointF x1, x2, x3, x4;
    std::vector<QPointF> tab2;
        for (size_t i = 0; i < tab.size(); ++i) {
            x1 = tab[(i-1)%tab.size()];
            x2 = tab[(i)%tab.size()];
            x3 = tab[(i+1)%tab.size()];
            x4 = tab[(i+2)%tab.size()];
            double x = ( 0.0625*( -x1.x() + 9*x2.x() + 9*x3.x() - x4.x() ) );
            double y = ( 0.0625*( -x1.y() + 9*x2.y() + 9*x3.y() - x4.y() ) );
            QPointF res = QPointF(x,y);
            tab2.push_back( x2 );
            tab2.push_back( res );
        }
        tab = tab2;
}

void MainWindow::lancer4PtsG(){
    scene->clear();
    dessinerGraphe();
    tab.clear();
    recupererPoints();
    dessinerCourbe((Qt::black));
    for (int i = 0; i < 8; ++i) {
        Algo4PtsG();
    }
    dessinerCourbe(Qt::red);
}

void MainWindow::Algo4PtsG(){
    double epsilone = 0.15;
    QPointF x1, x2, x3, x4;
    std::vector<QPointF> tab2;
        for (size_t i = 0; i < tab.size(); ++i) {
            x1 = tab[(i-1)%tab.size()];
            x2 = tab[(i)%tab.size()];
            x3 = tab[(i+1)%tab.size()];
            x4 = tab[(i+2)%tab.size()];
            double x = ( -(epsilone/8) * 0.5 * (x1.x() + x4.x()) + ((8 + epsilone)/8)*(x2.x() + x3.x()) * 0.5);//( -x1.x() + 9*x2.x() + 9*x3.x() - x4.x() ) );
            double y = ( -(epsilone/8) * 0.5 * (x1.y() + x4.y()) + ((8 + epsilone)/8)*(x2.y() + x3.y()) * 0.5);
            QPointF res = QPointF(x,y);
            tab2.push_back( x2 );
            tab2.push_back( res );
        }
        tab = tab2;
}

void MainWindow::lancerCornerCutting(){
    scene->clear();
    dessinerGraphe();
    tab.clear();
    recupererPoints();
    dessinerCourbe((Qt::black));
    for (int i = 0; i < 10; ++i) {
        AlgoCornerCutting();
    }
    dessinerCourbe(Qt::red);
}

void MainWindow::AlgoCornerCutting(){
    double a = 0.34;
    double b = 0.66;
    QPointF x1, x2;
    double x, y;
    std::vector<QPointF> tab2;
        for (size_t i = 0; i < tab.size(); ++i) {
            x1 = tab[(i)%tab.size()];
            x2 = tab[(i+1)%tab.size()];
            double x = ( (1-a) * x1.x() + a * x2.x() );
            double y = ( (1-a) * x1.y() + a * x2.y() );
            QPointF res = QPointF(x,y);
            x = ( (1-b) * x1.x() + b * x2.x() );
            y = ( (1-b) * x1.y() + b * x2.y() );
            QPointF res2 = QPointF(x,y);
            tab2.push_back( res );
            tab2.push_back( res2 );
        }
    tab.clear();
    tab = tab2;
}

