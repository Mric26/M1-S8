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
    QObject::connect( ui->BsplinesUniformes, SIGNAL(clicked()), this, SLOT(lancer4PtsUniforme()));

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

void MainWindow::lancer4PtsUniforme(){
        scene->clear();
        dessinerGraphe();
        tab.clear();
        recupererPoints();
        dessinerCourbe((Qt::black));
        Algo4PtsUniforme();
        dessinerCourbe(Qt::red);
}

void MainWindow::Algo4PtsUniforme(){
    degre= ui->degre->value();
    std::vector<QPointF> tab2;
    QPointF x1, x2;

    for (int n = 0; n < 8; ++n) {
        //dédoublement des points
        for (int j = 0; j < tab.size(); ++j) {
            x1 = tab[j];
            tab2.push_back(x1);
            tab2.push_back(x1);
        }

        tab= tab2;
        tab2.clear();
        for (int k = 0; k < degre; ++k) {
            //moyennage
            for (int i = 0; i < tab.size()-1; ++i) {
               x1= tab[i];
               x2= tab[i+1];
               tab2.push_back(QPointF(0.5*(x1.x() + x2.x()) , 0.5*(x1.y() + x2.y())));
            }
            tab= tab2;
            tab2.clear();
        }
    }


}


