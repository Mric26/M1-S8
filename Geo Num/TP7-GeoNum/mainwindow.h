#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QVector3D>
#include <fstream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void recupererPoints();

    double omega(int i, int k, double t, double tabP[]);
    int TrouverJ(double t, double tabnoeuds[], int tailleTabNoeuds);

    QVector3D PointBSplines(vector<QVector3D> tab, double t, int k);


    QString pointToString(QVector3D p);
    void ecrireFichier(string Nomfichier);

    void afficherMatrice();

    int getTaille() const;
    void setTaille(int value);

public slots:
    void AlgoBSplines();

private:
    Ui::MainWindow *ui;
    int taille;
    int degre;
    int nbCols, nbLignes;
    std::vector<std::vector<QVector3D> > matricePts;
    std::vector<std::vector<QVector3D> > result;
};

#endif // MAINWINDOW_H
