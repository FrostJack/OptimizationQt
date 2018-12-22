#include "painter.h"
#include "QPainter"
#include <iostream>

Painter::Painter(QWidget *parent) : QWidget(parent),
    gradient(0),
    iter(20000),
    prob(0.9),
    eps(0.0000001),
    path(0),
    steps(0),
    rChecked(1),
    left({-3, -3}),
    right({3, 3}),
    epsSave(0),
    iterSave(100000000),
    b()
{
    setMouseTracking(true);
    b.changeBorder(2, left, right);
    pfun = new TwoDim();
    popt = new RandomSearch(prob);
}

void Painter::paintEvent(QPaintEvent *event){
    QPainter p(this);
    QPen pen;
    QSize sz = size();

    int width=sz.width();
    int height=sz.height();
    calculateGradient();
    auto it = gradient.begin();
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            pen.setColor(QColor(0, 0, 255 - std::min((*it)[j]*4,255)));
            p.setPen(pen);
            p.drawPoint(i,j);
        }
        ++it;
    }
    draw_path();
}


void Painter::draw_path(){
    if (path.size() == 0)
        return;
    std::vector<QPointF> pathT;
    pathT.reserve(path[0].size());
    for(int j = 0; j < path[0].size(); ++j)
            pathT.push_back(transform({path[0][j], path[1][j]}));
    QPainter p(this);
    p.setPen(QColor(255, 0, 0));
    p.setBrush(QColor(255, 0, 0));
    p.drawEllipse(pathT[0], 3, 3);
    p.setPen(QColor(153, 0, 255));
    p.setBrush(QColor(153, 0, 255));
    for (int j = 0; j < pathT.size() - 1; ++j){
        p.drawLine(pathT[j], pathT[j+1]);
        if (j != pathT.size() - 2)
            p.drawEllipse(pathT[j+1], 3, 3);
    }
    p.setPen(QColor(255, 0, 0));
    p.setBrush(QColor(255, 0, 0));
    p.drawEllipse(pathT[pathT.size() - 1], 3, 3);
}

QPointF Painter::transform(const std::vector<double> x_){
    QSize sz = size();
    int width=sz.width();
    int height=sz.height();
    return QPointF((x_[0] - b.left[0]) / (b.right[0] - b.left[0]) * width,
            (1-(x_[1] - b.left[1])/ (b.right[1]-b.left[1])) * height);
}

void Painter::mousePressEvent(QMouseEvent *event) {
    path.clear();
    path.shrink_to_fit();
    int x=event->x();
    int y=event->y();
    QSize sz = size();
    int width=sz.width();
    int height=sz.height();

    std::vector<double> point(2);

    double step_x = (b.right[0] - b.left[0]) / width;
    double step_y = (b.right[1] - b.left[1]) / height;

    point[0] = b.left[0] + x * step_x;
    point[1] = b.right[1] - y * step_y;
    popt -> calculate(pfun, b, point, eps, iter);
    path = popt->path;
    steps = popt->getSteps();
    f_ans = QString::number(popt->f_ans);
    ans = QString::number(popt->ans[0]) + ", " + QString::number(popt->ans[1]);
    countSteps = QString::number(steps);
    emit fAnsSignal(f_ans);
    emit ansSignal(ans);
    emit stepsSignal(countSteps);
    repaint();
}

void Painter::calculateGradient(){
    gradient.clear();
    gradient.shrink_to_fit();
    std::vector<std::vector<double>> grid;
    double value;
    QSize sz = size();
    int width = sz.width();
    int height = sz.height();

    double step_x = (b.right[0] - b.left[0]) / width;
    double step_y = (b.right[1] - b.left[1]) / height;
    double min_v = pfun -> f(b.left);
    double max_v = pfun -> f(b.right);
    std::vector<double> row(height);
    for (int i = 0; i < width; ++i) {
        row.clear();
        for (int j = 0; j < height; ++j) {
            value = pfun -> f({b.left[0] + i * step_x, b.right[1] - j * step_y});
            if (min_v > value) {
                min_v = value;
            }
            if (max_v < value) {
                max_v = value;
            }
            row.push_back(value);
        }
        grid.push_back(row);
    }
    gradient = std::vector<std::vector<int>>(width);
    for (int i = 0; i < width; ++i) {
        gradient[i].resize(height);
        std::transform(grid[i].begin(), grid[i].end(), gradient[i].begin(), [&](double x) -> int {
            return (100*log((x - min_v) + 1) / log(max_v - min_v + 1));
        });
    };
}

void Painter::changeFunc(int index){
    delete pfun;
    switch(index){
    case 0: pfun = new TwoDim();
        break;
    case 1: pfun = new TwoDim2();
        break;
    }
    path.clear();
    path.shrink_to_fit();
    repaint();
}

void Painter::changeMethod(bool checked){
    delete popt;
    switch(checked){
    case 0: popt = new CoordDescent();
        rChecked = 0;
        break;
    case 1: popt = new RandomSearch(prob);
        rChecked = 1;
        break;
    }
}

void Painter::changeBorderLF(double x){
    left[0] = x;
    b.changeLeft(left);
    repaint();
}

void Painter::changeBorderRF(double x){
    right[0] = x;
    b.changeRight(right);
    repaint();
}

void Painter::changeBorderLS(double x){
    left[1] = x;
    b.changeLeft(left);
    repaint();
}

void Painter::changeBorderRS(double x){
    right[1] = x;
    b.changeRight(right);
    repaint();
}

void Painter::changeProb(double p){
    prob = p;
    if (rChecked){
        delete popt;
        popt = new RandomSearch(prob);
    }
}

void Painter::changeIter(int n){
    if (iterSave == 100000000)
        iter = n;
    else iterSave = n;
}

void Painter::changeEps(double e){
    if (!epsSave)
        eps = e;
    else epsSave = e;
}

void Painter::switchEps(bool checked){
    switch(checked){
    case 0: epsSave = eps;
        eps = 0;
        break;
    case 1: eps = epsSave;
        epsSave = 0;
        break;
    }
}

void Painter::switchIter(bool checked){
    switch(checked){
    case 0: iterSave = iter;
        iter = 1000000;
        break;
    case 1: iter = iterSave;
        iterSave = 1000000;
        break;
    }
}
