#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>

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
    void recupererPointsControles();
    void dessinerGraphe();
    void dessinerCourbe(QPointF tab[], int taille, Qt::GlobalColor coul);
    void courbeBezier(QPointF tabP[], int t);

    int getTaille() const;
    void setTaille(int value);

    void AlgoBSplines();
    QPointF PointBSplines(double t);
    int TrouverJ(double t, double tabnoeuds[], int tailleTabNoeuds);
    double omega(int i, int k, double t, double tabP[]);

public slots:
    void lancerBezier();
    void lancerBSplines();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPointF tab[50]; //table des points de contrôle
    QPointF tabControle[2];
    int taille;
    float t;
};

#endif // MAINWINDOW_H
