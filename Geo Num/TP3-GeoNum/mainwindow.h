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

public slots:
    void lancerBezier();
    void lancerBSplines();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPointF tab[50];
    QPointF tabControle[2];
    int taille;
    float t;
};

#endif // MAINWINDOW_H
