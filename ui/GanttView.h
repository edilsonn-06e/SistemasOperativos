
#pragma once
#include <QWidget>
#include "../core/Process.h"

class GanttView : public QWidget {
    Q_OBJECT
public:
    explicit GanttView(QWidget* parent=nullptr);
    void setData(const std::vector<Process>& v);
protected:
    void paintEvent(QPaintEvent*) override;
private:
    std::vector<Process> data;
    int timeMax = 0;
};
