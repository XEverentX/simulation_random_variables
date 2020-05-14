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
 
    lambdaLineEdit = new QLineEdit("2", this);
    countLineEdit  = new QLineEdit("100", this);

    lambdaLable = new QLabel("lambda: ", this);
    countLable  = new QLabel("count: ", this);

    runButton = new QPushButton("Run", this);

    table = new QTableWidget(2, 1000, this);

    table->setItem(0, 0, new QTableWidgetItem("№"));
    table->setItem(1, 0, new QTableWidgetItem("X"));

    
    grid->addWidget(lambdaLable, 0, 0);
    grid->addWidget(lambdaLineEdit, 0, 1);
    grid->addWidget(countLable, 0, 2);
    grid->addWidget(countLineEdit, 0, 3);
 
    header->addLayout(grid);
    header->addWidget(runButton);

    layout->addLayout(header);
    layout->addWidget(table);

    setLayout(layout);

    connect(runButton, &QPushButton::clicked, this, &Experement::run);
}

void Experement::run()
{
    double lambda = lambdaLineEdit->text().toDouble();
    double alpha  = 0.;
    int    count  = countLineEdit->text().toInt();

    alpha = 2.0 * (1 / lambda - 1);

    auto inversedCumulativeFunction = [=] (double x) -> double {
        if (!util::belongsTo(x, 0., 1.))
        {
            throw 5;
        }

        if (util::belongsTo(x, 0., -alpha / 2.))
        {
            return alpha - sqrt(-2. * alpha * x);
        } else
        {
            return log(-lambda * (x - 2.)) / lambda;
        }
    };

    Distribution distribution;
    distribution.setInversedCumulativeFunction(inversedCumulativeFunction);

    auto statistic = distribution.experiment(count);

    auto v = statistic.getEventsList();

    for (int i = 0; i < count; i++)
    {
        Experement::table->setItem(0, i + 1, new QTableWidgetItem(QString::number(i + 1)));
        Experement::table->setItem(1, i + 1, new QTableWidgetItem(QString::number(v[i])));
    }
}
