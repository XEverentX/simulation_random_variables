// Copyright Lebedev Alexander 2020
#pragma once
 
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

private:
    QLineEdit *lambdaLineEdit;
    QLineEdit *countLineEdit;

    QLabel *lambdaLable;
    QLabel *countLable;

    QPushButton *runButton;

    QTableWidget *table;
    QTableWidget *statisticTable;
    QTableWidget *histTable;
    QTableWidget *densityTable;

    QCustomPlot *customPlot;
    QCustomPlot *histPlot;

    double segmentLen;
};
