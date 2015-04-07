#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector3D>
#include <iostream>
#include <fstream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void afficherMatrice();
    QString pointToString(QVector3D p);
    QString pointsToFace(std::vector<int> tab);
    void ecrireFichier();
    void recupererPoints();
    void AlgoChaikin();

public slots:
    void LancerAlgo();

private:
    Ui::MainWindow *ui;
    int nbCols, nbLignes, taille;
    std::vector<std::vector<QVector3D> > matricePts;
    std::vector<std::vector<QVector3D> > result;
};

#endif // MAINWINDOW_H
