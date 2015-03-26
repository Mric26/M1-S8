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

    void Algo();

    void courbeBezier( std::vector<QPointF> tab );

    QString pointToString(int indice, QPointF p );

    void afficherMatrice();

    int getTaille() const;
    void setTaille(int value);

public slots:
    void lancerAlgo();

private:
    Ui::MainWindow *ui;
    std::vector<QPointF> tab;
    int taille;
    int degre;
    int nbCols, nbLignes;
    std::vector<std::vector<QVector3D> > matricePts;
};

#endif // MAINWINDOW_H
