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

    QObject::connect( ui->Algo, SIGNAL(clicked()), this, SLOT(AlgoBSplines()) );
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
        taille= nbPoints;

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

int MainWindow::getTaille() const{
    return taille;
}

void MainWindow::setTaille(int value){
    taille = value;
}

QString MainWindow::pointToString( QVector3D p ){
    const string temp = "( " + to_string(p.x()) + " ; " + to_string(p.y()) + " ; " + to_string(p.z()) + " )";
    QString res = QString::fromStdString(temp);
    return res;
}

void MainWindow::ecrireFichier(){
    ofstream fichier("/home/s/segureta/Documents/S8/M1-S8/Geo Num/TP7-GeoNum/test.txt", ios::out | ios::trunc);
    if(fichier){
        for (int j = 0; j < result.size(); ++j) {
           vector<QVector3D> yolo = result[j];
           for (int i = 0; i < yolo.size(); ++i) {
               QVector3D duSwag = yolo[i];
               QString chaine = pointToString(duSwag);
               fichier << chaine.toStdString() << endl;
           }
        }
        fichier.close();
    }
    else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
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

QVector3D MainWindow::PointBSplines( vector<QVector3D> tab, double t, int k){
    //table des noeuds
    int m = tab.size() + k;
    int nbNoeuds = m + 1;
    double tabNoeuds[nbNoeuds];
    for (int i = 0; i < nbNoeuds; ++i) {
        tabNoeuds[i] = double(i);
    }

    int j= TrouverJ(t, tabNoeuds, nbNoeuds);

    //calcul du point final de la courbe
    vector <QVector3D> tabPointsInter;
    tabPointsInter.clear();
    //recopie des points de contrôle en local
    for (int i = 0; i < k+1; ++i) {
        tabPointsInter.push_back(tab[j-k+i]);
    }
    double x,y,z;
    int nbSousPoints = k+1;
    for (int r = 1; r < k+1; ++r) { //calcul des sous points
        for (int i = 1; i < nbSousPoints; ++i) {
            double om = omega(j - k + r + i - 1, k-r+1, t, tabNoeuds);
            x = (1- om)*tabPointsInter[i-1].x() + om*tabPointsInter[i].x();
            y = (1- om)*tabPointsInter[i-1].y() + om*tabPointsInter[i].y();
            z = (1- om)*tabPointsInter[i-1].z() + om*tabPointsInter[i].z();
            tabPointsInter[i-1] = QVector3D(x, y, z);
        }
        nbSousPoints--;
    }
    return tabPointsInter.at(0);
    tabPointsInter.clear();
}

void MainWindow::AlgoBSplines(){
    result.clear();
    recupererPoints();

    afficherMatrice();
    vector<QVector3D> resultLigne, vect, temp;
    int k = ui->degK->value();
    int l = ui->degL->value();

    for (double u = k; u < ui->lignes->value(); u+=0.1) {
        cout << "étape pour u=" << u << endl;
        for (double v = l; v < ui->colonnes->value(); v+=0.1) {
            vect.clear();
            temp.clear();
            for (int i = 0; i < matricePts.size(); ++i) {
                vect = matricePts.at(i);
                QVector3D tmp= PointBSplines(vect, u, k);
                //problème de génération de points
                cout << tmp.x() << ";" << tmp.y() << ";" << tmp.z() << endl;
                temp.push_back( tmp );
                vect.clear();
            }
            resultLigne.push_back( PointBSplines(temp, v, l) );
        }
        result.push_back( resultLigne );
        resultLigne.clear();
    }

    cout << "le résultat possède " << result.size() << " lignes et " << result.at(1).size() << " colonnes" << endl;
    for (int var = 0; var < result.size(); ++var) {
        for (int var2 = 0; var2 < result.at(var).size(); ++var2) {
            cout << result.at(var).at(var2).x() << ";" << result.at(var).at(var2).y() << ";" << result.at(var).at(var2).z() << "   ";
        }
        cout << endl;
    }
    cout << "verif de valeur des points récupérés" << endl;

    ecrireFichier();

    //clear
    resultLigne.clear();
    vect.clear();
    temp.clear();
}

