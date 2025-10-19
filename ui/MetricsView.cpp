#include "MetricsView.h"
#include <QGridLayout>

MetricsView::MetricsView(QWidget* parent): QWidget(parent){
    auto lay = new QGridLayout(this);
    lblWT = new QLabel("-", this);
    lblTAT= new QLabel("-", this);
    lblRT = new QLabel("-", this);

    lay->addWidget(new QLabel("Promedio Tiempo de Espera (WT):"), 0, 0);
    lay->addWidget(lblWT, 0, 1);

    lay->addWidget(new QLabel("Promedio Tiempo de Retorno (TAT):"), 1, 0);
    lay->addWidget(lblTAT, 1, 1);

    lay->addWidget(new QLabel("Promedio Tiempo de Respuesta (RT):"), 2, 0);
    lay->addWidget(lblRT, 2, 1);

    setLayout(lay);
}

void MetricsView::setMetrics(const Metrics& m){
    lblWT->setText(QString::number(m.avgWT, 'f', 2));
    lblTAT->setText(QString::number(m.avgTAT, 'f', 2));
    lblRT->setText(QString::number(m.avgRT, 'f', 2));
}
