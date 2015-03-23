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

    void Algo();

    void courbeBezier( std::vector<QPointF> tab );

    QString pointToString(int indice, QPointF p );

public slots:
    void lancerAlgo();

private:
    Ui::MainWindow *ui;
    std::vector<QPointF> tab;
    int taille;
    int degre;
};

#endif // MAINWINDOW_H
