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
    void dessinerCourbe(Qt::GlobalColor coul);

    int getTaille() const;
    void setTaille(int value);

    void Algo4PtsUniforme();

public slots:
    void courbe();
    void lancer4PtsUniforme();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QPointF> tab;
    int taille;
    int degre;
};

#endif // MAINWINDOW_H
