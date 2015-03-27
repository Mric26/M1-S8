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
    void Algo();
    void courbeBezier( vector<QVector3D> tab );
    QString pointToString(int indice1, int indice2, QVector3D p );
    QString pointToString2(QVector3D p);
    void ecrireFichier(vector<QVector3D> tab);

public slots:
    void lancerAlgo();

private:
    Ui::MainWindow *ui;
    std::vector<QPointF> tab;
    int taille;
    int degre;
};

#endif // MAINWINDOW_H
