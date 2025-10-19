
#include "GanttView.h"
#include <QPainter>
#include <algorithm>

GanttView::GanttView(QWidget* parent): QWidget(parent) {
    setMinimumHeight(160);
}

void GanttView::setData(const std::vector<Process>& v){
    data = v;
    timeMax = 0;
    for (auto& p : data) timeMax = std::max(timeMax, p.finishTime);
    update();
}

void GanttView::paintEvent(QPaintEvent*){
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int w = width(), h = height();
    p.drawRect(rect().adjusted(0,0,-1,-1));
    if (data.empty() || timeMax<=0) return;
    // draw timeline bars
    int rowH = std::max(24, h / (int)data.size());
    int y = 10;
    for (const auto& pr : data){
        int x1 = (int)((double)pr.startTime / timeMax * (w-40)) + 20;
        int x2 = (int)((double)pr.finishTime / timeMax * (w-40)) + 20;
        p.drawRect(QRect(x1, y, std::max(4, x2-x1), rowH-8));
        p.drawText(x1+4, y+rowH/2, QString("P%1").arg(pr.pid));
        y += rowH;
    }
}
