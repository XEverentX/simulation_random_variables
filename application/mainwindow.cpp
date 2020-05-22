// Copyright Lebedev Alexander 2020
#include "mainwindow.h"
#include <distribution.hpp>
#include <utils.hpp>

#include <iostream>
#include <functional>
#include <cmath>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
 
Experement::Experement(QWidget *parent)
    : QWidget(parent) {
        
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *header = new QHBoxLayout();
    QGridLayout *grid = new QGridLayout(); 
 
    lambdaLineEdit = new QLineEdit("4", this);
    countLineEdit  = new QLineEdit("10000", this);

    lambdaLable = new QLabel("lambda: ", this);
    countLable  = new QLabel("count: ", this);
    auto statLabel = new QLabel("Сharacteristics:", this);
 
    runButton = new QPushButton("Run", this);

    table = new QTableWidget(2, 10001, this);
    statisticTable = new QTableWidget(2, 8, this);

    table->setItem(0, 0, new QTableWidgetItem("№"));
    table->setItem(1, 0, new QTableWidgetItem("X"));
    statisticTable->setItem(0, 0, new QTableWidgetItem("ExpectedValue"));
    statisticTable->setItem(0, 1, new QTableWidgetItem("Mean"));
    statisticTable->setItem(0, 2, new QTableWidgetItem("|ExpectedValue - Mean|"));
    statisticTable->setItem(0, 3, new QTableWidgetItem("Dispersion"));
    statisticTable->setItem(0, 4, new QTableWidgetItem("SampleDispersion"));
    statisticTable->setItem(0, 5, new QTableWidgetItem("|Dispersion - SampleDispersion|"));
    statisticTable->setItem(0, 6, new QTableWidgetItem("Median"));
    statisticTable->setItem(0, 7, new QTableWidgetItem("Scale"));
    
    grid->addWidget(lambdaLable, 0, 0);
    grid->addWidget(lambdaLineEdit, 0, 1);
    grid->addWidget(countLable, 0, 2);
    grid->addWidget(countLineEdit, 0, 3);
 
    header->addLayout(grid);
    header->addWidget(runButton);

    layout->addLayout(header);
    layout->addWidget(table);

    layout->addWidget(statLabel);
    layout->addWidget(statisticTable);

    // Plot
    customPlot = new QCustomPlot(this);

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->setInteraction(QCP::iRangeDrag, true); 

    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    QSizePolicy sp = customPlot->sizePolicy();
    sp.setHorizontalStretch(1);
    sp.setVerticalStretch(1);
    customPlot->setSizePolicy(sp);
    layout->addWidget(customPlot);

    setLayout(layout);

    connect(runButton, &QPushButton::clicked, this, &Experement::run);
}

void Experement::run()
{
    double lambda = lambdaLineEdit->text().toDouble();
    double alpha  = 0.;
    int    count  = countLineEdit->text().toInt();

    alpha = 2.0 * (1. / lambda - 1.);

    auto inversedCumulativeFunction = [=] (double x) -> double {
        if (!util::belongsTo(x, 0., 1.))
        {
            throw 5;
        }

        if (util::belongsTo(x, 0., -alpha / 2.))
        {
            return alpha + sqrt(-2. * alpha * x);
        } else
        {
            return -log(-lambda * (x - 1.)) / lambda;
        }
    };

    auto cumulativeFunction = [=] (double x) -> double {
        if (x < alpha)
        {
            return 0.;
        }
        if (util::belongsTo(x, alpha, 0.))
        {
            return -(x * x) / (2. * alpha) + x - alpha / 2.;
        } else
        {
            return -alpha / 2. - (exp(-lambda * x) - 1.) / lambda;
        }
    };

    Distribution distribution;
    distribution.setInversedCumulativeFunction(inversedCumulativeFunction);
    distribution.setCumulativeFunction(cumulativeFunction);

    auto statistic = distribution.experiment(count);

    statistic.setParameters(alpha, lambda);

    auto v = statistic.getEventsList();

    auto coeficient = 1. / count;
    QVector<double> x(count);
    QVector<double> y1(count);
    QVector<double> y2(count);

    for (int i = 0; i < count; i++)
    {
        Experement::table->setItem(0, i + 1, new QTableWidgetItem(QString::number(i + 1)));
        Experement::table->setItem(1, i + 1, new QTableWidgetItem(QString::number(v[i])));

        x[i] = v[i];
        y1[i] = coeficient * (i + 1);
        y2[i] = cumulativeFunction(v[i]);
    }
    
    customPlot->clearGraphs();
    customPlot->addGraph();
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->graph(0)->setData(x, y1);
    customPlot->graph(0)->rescaleAxes();
    customPlot->graph(0)->setName("Sampled");

    customPlot->graph(1)->setData(x, y2);
    customPlot->graph(1)->rescaleAxes();
    customPlot->graph(1)->setName("Theoretical");

    customPlot->xAxis->setRange(x[0], x[count - 1]);
    customPlot->yAxis->setRange(0, 1);

    customPlot->legend->setVisible(true);

    customPlot->replot();

    statistic.calculate();

    auto diffMean = std::fabs(statistic.m_theoreticalExpectedValue - statistic.m_sampleMean);
    auto diffDispersion = std::fabs(statistic.m_theoreticalDispersion - statistic.m_sampleDispersion);

    Experement::statisticTable->setItem(1, 0, new QTableWidgetItem(QString::number(statistic.m_theoreticalExpectedValue)));
    Experement::statisticTable->setItem(1, 1, new QTableWidgetItem(QString::number(statistic.m_sampleMean)));
    Experement::statisticTable->setItem(1, 2, new QTableWidgetItem(QString::number(diffMean)));
    Experement::statisticTable->setItem(1, 3, new QTableWidgetItem(QString::number(statistic.m_theoreticalDispersion)));
    Experement::statisticTable->setItem(1, 4, new QTableWidgetItem(QString::number(statistic.m_sampleDispersion)));
    Experement::statisticTable->setItem(1, 5, new QTableWidgetItem(QString::number(diffDispersion)));
    Experement::statisticTable->setItem(1, 6, new QTableWidgetItem(QString::number(statistic.m_sampleMedian)));
    Experement::statisticTable->setItem(1, 7, new QTableWidgetItem(QString::number(statistic.m_scale)));
}
