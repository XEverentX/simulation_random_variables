// Copyright Lebedev Alexander 2020
#pragma once

#include <functional>
#include <vector>

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "3rdparty/qcustomplot.h"
 
class Experement : public QWidget {
    
public:
    Experement(QWidget *parent = 0);

    ~Experement() = default;

    void run();

    void plotHist();

    void createDensityTable(const std::vector<double> &points, const QVector<double> &fossilData);

    void setFunctions();

    std::vector<double> getQ();
    
    double getR0();

    double getF0(double x);

    void checkHypothesis();

    void fillHypothesisTable();

private:
    QLineEdit *lambdaLineEdit;
    QLineEdit *countLineEdit;
    QLineEdit *partitionLineEdit;
    QLineEdit *importanceLineEdit;
    QLineEdit *FR0LineEdit;


    QLabel *lambdaLable;
    QLabel *countLable;
    QLabel *hypothesisLable;

    QPushButton *runButton;

    QTableWidget *table;
    QTableWidget *statisticTable;
    QTableWidget *histTable;
    QTableWidget *densityTable;
    QTableWidget *hypothesisTable;

    QCustomPlot *customPlot;
    QCustomPlot *histPlot;

    double segmentLen;
    std::vector<double> q;
    std::vector<int> data;

    std::function<double(double)> inversedCumulativeFunction;
    std::function<double(double)> cumulativeFunction;
    std::function<double(double)> densityFunction;
};
