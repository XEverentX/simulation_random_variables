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
    QHBoxLayout *graphLayout = new QHBoxLayout();
    QHBoxLayout *histLayout = new QHBoxLayout();
 
    lambdaLineEdit = new QLineEdit("4", this);
    countLineEdit  = new QLineEdit("10000", this);

    lambdaLable = new QLabel("lambda: ", this);
    countLable  = new QLabel("count: ", this);
    auto statLabel = new QLabel("Сharacteristics:", this);
    auto histLable = new QLabel("Histogram init:", this);

    lambdaLable->setMaximumHeight(12);
    statLabel->setMaximumHeight(12);
    histLable->setMaximumHeight(12);
 
    runButton = new QPushButton("Run", this);
    auto plotButton = new QPushButton("Replot Hist", this);
    plotButton->setMaximumWidth(150);

    table = new QTableWidget(2, 10001, this);
    statisticTable = new QTableWidget(2, 8, this);
    histTable = new QTableWidget(2, 1001, this);
    densityTable = new QTableWidget(3, 30, this);

    table->setMaximumHeight(85);
    statisticTable->setMaximumHeight(85);
    histTable->setMaximumHeight(85);
    densityTable->setMaximumHeight(115);

    table->horizontalHeader()->hide();
    statisticTable->horizontalHeader()->hide();
    histTable->horizontalHeader()->hide();
    densityTable->horizontalHeader()->hide();

    histTable->setItem(0, 0, new QTableWidgetItem("Count / Values"));
    histTable->setItem(1, 0, new QTableWidgetItem("30"));
    
    densityTable->setItem(0, 0, new QTableWidgetItem("x[i]"));
    densityTable->setItem(1, 0, new QTableWidgetItem("f(x[i])"));
    densityTable->setItem(2, 0, new QTableWidgetItem("n[i]/(n * d[i])"));

    for (int i = 0; i < 1000; i++)
    {
        histTable->setItem(0, i + 1, new QTableWidgetItem((QString::number(i + 1))));
    }

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

    histLayout->addWidget(histLable);
    histLayout->addWidget(plotButton);

    layout->addLayout(histLayout);
    layout->addWidget(histTable);

    layout->addWidget(densityTable);

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

    graphLayout->addWidget(customPlot);

    histPlot = new QCustomPlot(this);

    histPlot->xAxis2->setVisible(true);
    histPlot->xAxis2->setTickLabels(false);
    histPlot->yAxis2->setVisible(true);
    histPlot->yAxis2->setTickLabels(false);

    QSizePolicy hsp = histPlot->sizePolicy();
    hsp.setHorizontalStretch(1);
    hsp.setVerticalStretch(1);
    histPlot->setSizePolicy(hsp);

    graphLayout->addWidget(histPlot);

    layout->addLayout(graphLayout);

    setLayout(layout);

    connect(runButton, &QPushButton::clicked, this, &Experement::run);
    connect(plotButton, &QPushButton::clicked, this, &Experement::plotHist);
}

void Experement::run()
{
    // Init
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

    // Run
    auto statistic = distribution.experiment(count);

    statistic.setParameters(alpha, lambda);

    statistic.calculate();

    auto v = statistic.getEventsList();

    auto coeficient = 1. / count;
    QVector<double> x(count);
    QVector<double> y1(count);
    QVector<double> y2(count);

    // Set results into the table
    Experement::table->setColumnCount(count + 1);

    for (int i = 0; i < count; i++)
    {
        Experement::table->setItem(0, i + 1, new QTableWidgetItem(QString::number(i + 1)));
        Experement::table->setItem(1, i + 1, new QTableWidgetItem(QString::number(v[i])));

        x[i] = v[i];
        y1[i] = coeficient * (i + 1);
        y2[i] = cumulativeFunction(v[i]);
    }

    // Plot cumulative function
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

    int histCount = Experement::histTable->item(1, 0)->text().toInt();

    segmentLen = statistic.getHistSegmentsLen(histCount);
    for (int i = 0; i < histCount; i++)
    {
        histTable->setItem(1, i + 1, new QTableWidgetItem(QString::number(segmentLen * i + v[0])));
    }
    
    // Plot hstogram
    plotHist();

    // Insert statistic into the table
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

    Experement::statisticTable->resizeColumnsToContents();
}

void Experement::plotHist()
{
    int histCount = Experement::histTable->item(1, 0)->text().toInt();

    std::vector<double> points;
    for (int i = 0; i < histCount; i++)
    {
        points.push_back(Experement::histTable->item(1, i + 1)->text().toDouble());
    }

    histPlot->clearGraphs();

    QCPBars* fossil = new QCPBars(histPlot->xAxis, histPlot->yAxis);
 
    QPen pen;
    pen.setWidthF(1.5);
    pen.setColor(QColor(50, 50, 100));
    fossil->setPen(pen);
    fossil->setBrush(QColor(50, 50, 250, 70));
 
    QVector<double> ticks;
    QVector<QString> labels;

    for (int i = 1; i < histCount; i++)
    {
        double label = (points[i] + points[i - 1]) / 2.;
        label = static_cast<double>(static_cast<int>(label * 100)) / 100.;

        labels.push_back(QString::number(label));
        ticks.push_back(i);
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    histPlot->xAxis->setTicker(textTicker);
    histPlot->xAxis->setTickLabelRotation(60);
    histPlot->xAxis->setSubTicks(false);
    histPlot->xAxis->setTickLength(0, 4);
    histPlot->xAxis->grid()->setVisible(true);
    histPlot->xAxis->setRange(0, histCount);
 
    histPlot->yAxis->setRange(0, 1);
    histPlot->yAxis->setPadding(5);
    histPlot->yAxis->setLabel("Histogram");
    histPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    histPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    histPlot->yAxis->grid()->setSubGridPen(gridPen);
 
    QVector<double> fossilData(histCount - 1);
    std::vector<int> data(histCount);

    int count = countLineEdit->text().toInt();

    for (int i = 1; i <= count; i++)
    {
        double value = table->item(1, i)->text().toDouble();
        int number = std::lower_bound(points.begin(), points.end(), value) - points.begin();
        if (number >= histCount) number--;
        data[number]++;
    }

    for (int i = 0; i < histCount - 1; i++)
    {
        fossilData[i] = static_cast<double>(data[i + 1]) / (count * (points[i + 1] - points[i]));
    }

    fossil->setData(ticks, fossilData);

    histPlot->replot();

    histPlot->removePlottable(fossil);

    createDensityTable(points, fossilData);
}

void Experement::createDensityTable(const std::vector<double> &points, const QVector<double> &fossilData)
{
    int histCount = Experement::histTable->item(1, 0)->text().toInt();
    double lambda = lambdaLineEdit->text().toDouble();
    double alpha  = 0.;

    alpha = 2.0 * (1. / lambda - 1.);

    auto densityFunction = [&] (double x) -> double {
        if (x < alpha)
        {
            return 0;
        }
        if (util::belongsTo(x, alpha, 0.))
        {
            return 1. - x / alpha;
        } else
        {
            return exp(-lambda * x);
        }
        
    };

    densityTable->setColumnCount(histCount);
    for (int i = 1; i < histCount; i++)
    {
        auto point = (points[i] + points[i - 1]) / 2.;
        Experement::densityTable->setItem(0, i, new QTableWidgetItem(QString::number(point)));
        Experement::densityTable->setItem(1, i, new QTableWidgetItem(QString::number(densityFunction(point))));
        Experement::densityTable->setItem(2, i, new QTableWidgetItem(QString::number(fossilData[i - 1])));
    }
}
