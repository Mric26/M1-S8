#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect( ui->Algo, SIGNAL(clicked()), this, SLOT(LancerAlgo()) );
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::LancerAlgo(){
    recupererPoints();
    if( matricePts.size() != 0 ){
        for (int nb = 0; nb < 5; ++nb) {
            AlgoChaikin();
        }
    }
    ecrireFichier();
    QFile file("/home/s/segureta/Documents/S8/M1-S8/Geo Num/TP8_GeoNum/dessin.txt");
    file.rename("/home/s/segureta/Documents/S8/M1-S8/Geo Num/TP8_GeoNum/dessin.obj");
    cout << "END" << endl;
}

void MainWindow::AlgoChaikin(){
    vector< QVector3D > Ligne1;
    vector< QVector3D > Ligne2;
    QVector3D p;
    double x, y, z;
    for (int i = 0; i < matricePts.size()  - 1; ++i) {
        Ligne1.clear();
        Ligne2.clear();
        for (int j = 0; j < matricePts[i].size() - 1; ++j) {
            //point(0,0)
            x = (9*matricePts[i][j].x() + 3*matricePts[i+1][j].x() + 3*matricePts[i][j+1].x() + matricePts[i+1][j+1].x())/16;
            y = (9*matricePts[i][j].y() + 3*matricePts[i+1][j].y() + 3*matricePts[i][j+1].y() + matricePts[i+1][j+1].y())/16;
            z = (9*matricePts[i][j].z() + 3*matricePts[i+1][j].z() + 3*matricePts[i][j+1].z() + matricePts[i+1][j+1].z())/16;
            Ligne1.push_back( QVector3D(x, y, z) );
            //point(0,1)
            x = (3*matricePts[i][j].x() + 9*matricePts[i+1][j].x() + matricePts[i][j+1].x() + 3*matricePts[i+1][j+1].x())/16;
            y = (3*matricePts[i][j].y() + 9*matricePts[i+1][j].y() + matricePts[i][j+1].y() + 3*matricePts[i+1][j+1].y())/16;
            z = (3*matricePts[i][j].z() + 9*matricePts[i+1][j].z() + matricePts[i][j+1].z() + 3*matricePts[i+1][j+1].z())/16;
            Ligne1.push_back( QVector3D(x, y, z) );
            //point(1,0)
            x = (3*matricePts[i][j].x() + matricePts[i+1][j].x() + 9*matricePts[i][j+1].x() + 3*matricePts[i+1][j+1].x())/16;
            y = (3*matricePts[i][j].y() + matricePts[i+1][j].y() + 9*matricePts[i][j+1].y() + 3*matricePts[i+1][j+1].y())/16;
            z = (3*matricePts[i][j].z() + matricePts[i+1][j].z() + 9*matricePts[i][j+1].z() + 3*matricePts[i+1][j+1].z())/16;
            Ligne2.push_back( QVector3D(x, y, z) );
            //point(1,1)
            x = (matricePts[i][j].x() + 3*matricePts[i+1][j].x() + 3*matricePts[i][j+1].x() + 9*matricePts[i+1][j+1].x())/16;
            y = (matricePts[i][j].y() + 3*matricePts[i+1][j].y() + 3*matricePts[i][j+1].y() + 9*matricePts[i+1][j+1].y())/16;
            z = (matricePts[i][j].z() + 3*matricePts[i+1][j].z() + 3*matricePts[i][j+1].z() + 9*matricePts[i+1][j+1].z())/16;
            Ligne2.push_back( QVector3D(x, y, z) );
        }
        result.push_back(Ligne1);
        result.push_back(Ligne2);
    }
    matricePts.clear();
    matricePts = result;
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

QString MainWindow::pointToString( QVector3D p ){
    const string temp = "v " + to_string(p.x()) + " " + to_string(p.y()) + " " + to_string(p.z());
    QString res = QString::fromStdString(temp);
    return res;
}

QString MainWindow::pointsToFace( vector<int> tab ){
    string temp = "f";
    for (int i = 0; i < 4; ++i) {
       temp = temp + " ";
       temp = temp + to_string(tab[i]);
    }
    QString res = QString::fromStdString(temp);
    return res;
}


void MainWindow::ecrireFichier(){
    ofstream fichier("/home/s/segureta/Documents/S8/M1-S8/Geo Num/TP8_GeoNum/dessin.txt", ios::out | ios::trunc);
    if(fichier){
        int nbpoints = 0;
        vector<QVector3D> yolo;
        //ajout des point
        for (int j = 0; j < matricePts.size(); ++j) {
           yolo = result[j];
           for (int i = 0; i < yolo.size(); ++i) {
               QVector3D duSwag = yolo[i];
               QString chaine = pointToString(duSwag);
               fichier << chaine.toStdString() << endl;
               nbpoints++;
           }
        }
        //ajout des faces
        int ligne = matricePts.size();
        int colone = matricePts[0].size();
        vector<int> tab;
        for (int k = 0; k < ligne-1; ++k) {
            for (int l = 0; l < colone-1; ++l) {
               tab.clear();
               tab.push_back( k*colone + l + 1 );
               tab.push_back( k*colone + l + 2 );
               tab.push_back( (k+1)*colone + l + 1 );
               tab.push_back( (k+1)*colone + l + 2 );
               QString face = pointsToFace(tab);
               fichier << face.toStdString() << endl;
            }
        }
        fichier.close();
    }
    else{
        cerr << "Erreur à l'ouverture !" << endl;
    }
}
