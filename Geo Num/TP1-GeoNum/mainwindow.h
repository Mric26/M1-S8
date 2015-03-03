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
    void dessinerGraphe();
    void dessinerCourbe(QPointF tab[], int taille, Qt::GlobalColor coul);
    void courbeBezier();

    int getTaille() const;
    void setTaille(int value);

public slots:
    void lancer();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPointF tab[50];
    int taille;
    float t;
};

#endif // MAINWINDOW_H
