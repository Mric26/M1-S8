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
         if (c.isNumber() || c == '-'){ //récupération d'un digit
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

void MainWindow::afficherMatrice(){ //rend le contenu de matriPts
    for (int i = 0; i < matricePts.size(); ++i) {
        for (int j = 0; j < matricePts.at(i).size(); ++j) {
            std::cout << "(" << matricePts[i].at(j).x() << ";" << matricePts[i].at(j).y() << ";" << matricePts[i].at(j).z() << ") ";
        }
        std::cout << std::endl;
    }
}

QString MainWindow::pointToString( QVector3D p ){
    const string temp = "v " + to_string(p.x()) + " " + to_string(p.y()) + " " + to_string(p.z()) + " ";
       QString res = QString::fromStdString(temp);
       return res;
}

void MainWindow::ecrireFichier(string Nomfichier){ //écrit le conteu de result dans un fichier dont le nom est passé en paramètre
    ofstream fichier("/home/chevailler/Documents/école/M1/S2/dépôt GIT tp/M1-S8/Geo Num/Tp6_GeoNum/" + Nomfichier, ios::out | ios::trunc);
        if(fichier){

            //écriture des points selon la convention "v x y z"
            for (int j = 0; j < result.size(); ++j) {
               for (int i = 0; i < result.at(j).size(); ++i) {
                   QVector3D vect = result.at(j)[i];
                   QString chaine = pointToString(vect);
                   fichier << chaine.toStdString() << endl;
               }
            }
            //écriture des faces selaon la convention "f PtNumero1 PtNumero2 PtNumero3 PtNumero4"
            for (int i = 0; i < result.size()-1; ++i) {
                vector <QVector3D> ligne1= result.at(i);
                vector <QVector3D> ligne2= result.at(i+1);
               for (int j = 0; j < result.at(i).size()-1; ++j) {
                   string face=
                            "f " + to_string(i*result.at(0).size() +j + 1)
                           + " " + to_string(i*result.at(0).size() +j + 2)
                           + " " + to_string((i+1)*result.at(0).size() +j + 2)
                           + " " + to_string((i+1)*result.at(0).size() +j + 1)
                           ;
                   //QString chaine = to(face);
                   fichier << face << endl;
               }
            }
            fichier.close();
            cout << "Succès de l'écriture" << endl;
        }
        else{
            cerr << "Erreur à l'ouverture !" << endl;
        }
}

void MainWindow::lancerAlgo(){
    recupererPoints();
    afficherMatrice();
    result = matricePts;
    ecrireFichier("source.obj");
    result.clear();

    Algo();
    ecrireFichier("res.obj");
}


void MainWindow::courbeBezier( vector<QVector3D> tab ){ //calcul d'une courbe de bézier pour un polygone de control
    vector<QVector3D> tabRes;
    //sauvegarde
    vector<QVector3D> tabSauv;
    tabSauv = tab;
    //calcul courbe
    for (int k = 0; k < 10; ++k) {
        for (int j = tab.size()-1; j > 0; j--) {
            for (int i = 0; i < j; ++i) {
                float x = ((float)(tab[i+1].x()) - (float)(tab[i].x()))*(0.1*k);
                float y = ((float)(tab[i+1].y()) - (float)(tab[i].y()))*(0.1*k);
                float z = ((float)(tab[i+1].z()) - (float)(tab[i].z()))*(0.1*k);
                tab.push_back(QVector3D(tab[i].x()+x, tab[i].y()+y, tab[i].z()+z) );
            }
        }
        //sauvegarde du point de la courbe
        float x = ((float)(tab[1].x()) - (float)(tab[0].x()))*(0.1*k);
        float y = ((float)(tab[1].y()) - (float)(tab[0].y()))*(0.1*k);
        float z = ((float)(tab[1].z()) - (float)(tab[0].z()))*(0.1*k);
        tabRes.push_back(QVector3D(tab[0].x()+x, tab[0].y()+y, tab[0].z()+z) );
        //remise au tab des point initiaux
        tab= tabSauv;
    }
    //resultats
    result.push_back(tabRes);
}

void MainWindow::Algo(){ //lance plusieurs fois le calcul des courbes de bezier

    //courbes de Bezier lancées sur chaque ligne
    for (int i = 0; i < ui->colonnes->value(); ++i) {
        courbeBezier( matricePts.at(i) );
    }
    matricePts.clear();
    matricePts =result;
    cout << "\n matrice "<< matricePts.size() << "x" << matricePts.at(0).size() << " résultat:" << endl;
    afficherMatrice();

    vector<vector <QVector3D> > temp;
    for (int i = 0; i < result.at(0).size(); ++i) {
        temp.push_back(vector <QVector3D>());
        for (int j = 0; j < result.size(); ++j) {
            temp.at(i).push_back(result.at(j).at(i));
        }
    }
    matricePts = temp;
    cout << " \n matrice renversée "<< matricePts.size() << "x" << matricePts.at(0).size() << " résultat: " << endl;
    afficherMatrice();

    //courbes de Bezier lanc"es sur chaque colonne
    for (int i = 0; i < matricePts.size(); ++i) {
        courbeBezier( matricePts.at(i) );
    }
    matricePts.clear();
    matricePts= result;
    cout << " \n matrice renversée travillée avec bezier "<< matricePts.size() << "x" << matricePts.at(0).size() << " résultat: " << endl;
    afficherMatrice();
}
