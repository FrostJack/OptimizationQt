#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    painter = new Painter();
    QGridLayout* Graph = findChild<QGridLayout*>("Graph");
    Q_ASSERT(Graph);
    Graph -> addWidget(painter);

    QObject::connect(ui->funcBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), painter, &Painter::changeFunc);
    QObject::connect(ui->randomSearchButton, &QRadioButton::clicked, painter, &Painter::changeMethod);
    QObject::connect(ui->firstLeftSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeBorderLF);
    QObject::connect(ui->secondLeftSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeBorderLS);
    QObject::connect(ui->firstRightSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeBorderRF);
    QObject::connect(ui->secondRightSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeBorderRS);
    QObject::connect(ui->probSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeProb);
    QObject::connect(ui->epsSpin, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), painter, &Painter::changeEps);
    QObject::connect(ui->iterSpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), painter, &Painter::changeIter);
    QObject::connect(painter,&Painter::fAnsSignal, this, &MainWindow::fAnsSignal);
    QObject::connect(painter,&Painter::ansSignal, this, &MainWindow::ansSignal);
    QObject::connect(painter,&Painter::stepsSignal, this, &MainWindow::stepsSignal);
    QObject::connect(ui->epsButton, &QRadioButton::clicked, painter, &Painter::switchEps);
    QObject::connect(ui->iterButton, &QRadioButton::clicked, painter, &Painter::switchIter);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete painter;
}

void MainWindow::fAnsSignal(QString s) {
    findChild<QLabel*>("mLabel") -> setText(s);
}

void MainWindow::ansSignal(QString s) {
    findChild<QLabel*>("mpLabel") -> setText(s);
}

void MainWindow::stepsSignal(QString s) {
    findChild<QLabel*>("stepsLabel") -> setText(s);
}

