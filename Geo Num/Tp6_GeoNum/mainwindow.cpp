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
        tab.clear();
        recupererPoints();
        Algo();
}

int MainWindow::getTaille() const{
    return taille;
}

void MainWindow::setTaille(int value){
    taille = value;
}


void MainWindow::Algo(){
    vector< vector<QVector3D> > tab;
    for (int i = 0; i < 3; ++i) {
       tab.push_back( vector<QVector3D>() );
    }

    tab[0].push_back( *(new QVector3D(200,300,0)) );
    tab[0].push_back( *(new QVector3D(275,375,0)) );
    tab[0].push_back( *(new QVector3D(400,375,0)) );
    tab[0].push_back( *(new QVector3D(475,300,0)) );

    tab[1].push_back( *(new QVector3D(150,200,0)) );
    tab[1].push_back( *(new QVector3D(225,275,0)) );
    tab[1].push_back( *(new QVector3D(350,275,0)) );
    tab[1].push_back( *(new QVector3D(425,200,0)) );

    tab[2].push_back( *(new QVector3D(100,100,0)) );
    tab[2].push_back( *(new QVector3D(175,175,0)) );
    tab[2].push_back( *(new QVector3D(300,175,0)) );
    tab[2].push_back( *(new QVector3D(375,100,0)) );

    for (int i = 0; i < ui->colonnes->value(); ++i) {
        for (int j = 0; j < ui->lignes->value(); ++j) {
           QString p = pointToString(i, j, tab[i][j] );
           ui->zoneSortie->setText( ui->zoneSortie->toPlainText() + p );
        }
        courbeBezier( tab[i] );
        ecrireFichier( tab[i] );
    }
}

void MainWindow::courbeBezier( vector<QVector3D> tab ){
    QVector3D tabRes[10];
    //sauvegarde
    QVector3D tabSauv[tab.size()];
    for (int l = 0; l < tab.size(); ++l) {
        tabSauv[l] = tab[l];
    }
    //calcul courbe
    for (int k = 0; k < 10; ++k) {
        for (int j = tab.size()-1; j > 0; j--) {
            for (int i = 0; i < j; ++i) {
                float x = ((float)(tab[i+1].x()) - (float)(tab[i].x()))*(0.1*k);
                float y = ((float)(tab[i+1].y()) - (float)(tab[i].y()))*(0.1*k);
                float z = ((float)(tab[i+1].z()) - (float)(tab[i].z()))*(0.1*k);
                tab[i] = *(new QVector3D(tab[i].x()+x, tab[i].y()+y, tab[i].z()+z) );
            }
        }
        //sauvegarde du point de la courbe
        float x = ((float)(tab[1].x()) - (float)(tab[0].x()))*(0.1*k);
        float y = ((float)(tab[1].y()) - (float)(tab[0].y()))*(0.1*k);
        float z = ((float)(tab[1].z()) - (float)(tab[0].z()))*(0.1*k);
        tabRes[k] = *(new QVector3D(tab[0].x()+x, tab[0].y()+y, tab[0].z()+z) );
        //remise au tab des point initiaux
        for (int l = 0; l < tab.size(); ++l) {
            tab[l] = tabSauv[l];
        }
    }
    //resultats
    tab.clear();
    for (int t = 0; t < 10; ++t) {
       tab.push_back( tabRes[t] );
    }
}

QString MainWindow::pointToString( int indice1, int indice2, QVector3D p ){
    const string temp = "P (" + to_string(indice1) + "," + to_string(indice2) +") = ( " + to_string(p.x()) + " ; " + to_string(p.y()) + " ; " + to_string(p.z()) + " ) \n";
    QString res = QString::fromStdString(temp);
    return res;
}

QString MainWindow::pointToString2( QVector3D p ){
    const string temp = "( " + to_string(p.x()) + " ; " + to_string(p.y()) + " ; " + to_string(p.z()) + " )";
    QString res = QString::fromStdString(temp);
    return res;
}

void MainWindow::ecrireFichier( vector<QVector3D> tab ){
    ofstream fichier("/home/s/segureta/Documents/S8/M1-S8/Geo Num/Tp6_GeoNum/test.txt", ios::out | ios::ate);
    if(fichier){
        for (int i = 0; i < tab.size(); ++i) {
            QVector3D temp = tab[i];
            QString chaine = pointToString2(temp);
            fichier << chaine.toStdString() << endl;
        }
        fichier.close();
    }
    else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
}

