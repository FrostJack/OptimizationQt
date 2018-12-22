#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include "Func.h"
#include "Optim.h"
#include "RandomSearch.h"
#include "CoordDescent.h"

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = 0);

signals:
    void fAnsSignal(QString s);
    void ansSignal(QString s);
    void stepsSignal(QString s);
public slots:
    void changeFunc(int index);
    void changeMethod(bool checked);
    void changeBorderLF(double x);
    void changeBorderLS(double x);
    void changeBorderRF(double x);
    void changeBorderRS(double x);
    void changeProb(double p);
    void changeIter(int n);
    void changeEps(double e);
    void switchEps(bool checked);
    void switchIter(bool checked);
private:
    std::vector<std::vector<int>> gradient; /**< stores function values on grid, transformed into interval [0,1]*/
    std::vector<std::vector<double>> path;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) override;
    void draw_path();
    QPointF transform(const std::vector<double> x_);
    void calculateGradient();

    QString f_ans;
    QString ans;
    QString countSteps;

    bool rChecked;
    int steps;
    int iter;
    int iterSave;
    std::vector<double> left, right;
    double prob;
    double eps;
    double epsSave;
    Func *pfun;
    Optim *popt;
    Border b;
};

#endif // PAINTER_H
