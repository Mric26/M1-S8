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
    void afficherMatrice();

    QString pointToString(QVector3D p);
     void ecrireFichier(string Nomfichier);

    void Algo();
    void courbeBezier( vector<QVector3D> tab );

public slots:
    void lancerAlgo();

private:
    Ui::MainWindow *ui;
    int degre;
    int nbCols, nbLignes;
    std::vector<std::vector<QVector3D> > result;
    std::vector<std::vector<QVector3D> > matricePts;
};

#endif // MAINWINDOW_H
