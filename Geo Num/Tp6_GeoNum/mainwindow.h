#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QVector3D>

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
    void dessinerGraphe();
    void dessinerCourbe(Qt::GlobalColor coul);

    int getTaille() const;
    void setTaille(int value);

    void Algo();

    void courbeBezier(QPointF tab[]);

    void afficherMatrice();

public slots:
    void courbe();
    void lancerAlgo();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QPointF> tab;
    int taille;
    int degre;
    int nbCols, nbLignes;
    std::vector<std::vector<QVector3D> > matricePts;
};

#endif // MAINWINDOW_H
