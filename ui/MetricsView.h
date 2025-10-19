
#pragma once
#include <QWidget>
#include <QLabel>
#include "../core/Metrics.h"

class MetricsView : public QWidget {
    Q_OBJECT
public:
    explicit MetricsView(QWidget* parent=nullptr);
    void setMetrics(const Metrics& m);
private:
    QLabel *lblWT, *lblTAT, *lblRT;
};
