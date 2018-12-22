#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Painter *painter;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fAnsSignal(QString s);
    void ansSignal(QString s);
    void stepsSignal(QString s);
signals:

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
