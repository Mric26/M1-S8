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

    void AlgoChaikin();
    void Algo4Pts();

public slots:
    void lancerChaikin();
    void lancer4Pts();
    void lancerCornerCutting();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QPointF> tab;
    int taille;
};

#endif // MAINWINDOW_H
