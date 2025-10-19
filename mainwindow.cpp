
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>


#include "core/Process.h"
#include "core/Metrics.h"
#include "scheduler/FCFS.h"
#include "scheduler/SJF.h"
#include "scheduler/SRTF.h"
#include "scheduler/RR.h"
#include "scheduler/PRIORITY.h"
#include "ui/GanttView.h"
#include "ui/MetricsView.h"
#include "ui/ConcurrencyView.h"
#include "memory/PageTable.h"
#include "memory/FIFO.h"
#include "memory/LRU.h"
#include "memory/OPT.h"

class PlanWidget : public QWidget {
    Q_OBJECT
public:
    PlanWidget(QWidget* parent=nullptr): QWidget(parent){
        auto root = new QVBoxLayout(this);
        auto controls = new QHBoxLayout();
        algo = new QComboBox(this);
        algo->addItems({"FCFS","SJF","SRTF","RR","PRIORITY"});
        quantum = new QSpinBox(this); quantum->setRange(1,50); quantum->setValue(2);
        btnRun = new QPushButton("Run", this);
        tbl = new QTableWidget(0,4,this);
        tbl->setHorizontalHeaderLabels({"PID","Llegada","Ráfaga","Prioridad"});
        gantt = new GanttView(this);
        metrics = new MetricsView(this);

        controls->addWidget(algo);
        controls->addWidget(new QLabel("Quantum:"));
        controls->addWidget(quantum);
        controls->addWidget(btnRun);
        root->addLayout(controls);
        root->addWidget(tbl);
        root->addWidget(gantt);
        root->addWidget(metrics);

        connect(btnRun, &QPushButton::clicked, this, [=]{
            std::vector<Process> procs;
            for (int r=0;r<tbl->rowCount();++r){
                auto get = [&](int c){ auto it=tbl->item(r,c); return it? it->text().toInt():0; };
                Process p(get(0), get(1), get(2), get(3));
                procs.push_back(p);
            }
            std::vector<Process> out;
            const QString a = algo->currentText();
            if (a=="FCFS"){ FCFS s; for(auto&p:procs) s.addProcess(p); out=s.run(); }
            else if (a=="SJF"){ SJF s; for(auto&p:procs) s.addProcess(p); out=s.run(); }
            else if (a=="SRTF"){ SRTF s; for(auto&p:procs) s.addProcess(p); out=s.run(); }
            else if (a=="RR"){ RR s(quantum->value()); for(auto&p:procs) s.addProcess(p); out=s.run(); }
            else { PRIORITY s; for(auto&p:procs) s.addProcess(p); out=s.run(); }

            gantt->setData(out);
            metrics->setMetrics(Metrics::from(out));
        });
        // seed some rows
        tbl->setRowCount(4);
        int seed[4][4]={{1,0,5,2},{2,2,3,1},{3,4,1,3},{4,5,2,2}};
        for(int r=0;r<4;r++)for(int c=0;c<4;c++){ tbl->setItem(r,c,new QTableWidgetItem(QString::number(seed[r][c]))); }
    }
private:
    QComboBox *algo; QSpinBox *quantum; QPushButton* btnRun;
    QTableWidget* tbl; GanttView* gantt; MetricsView* metrics;
};

#include "ui/ConcurrencyView.h"

class MemWidget : public QWidget {
    Q_OBJECT
public:
    MemWidget(QWidget* parent=nullptr): QWidget(parent){
        auto lay = new QVBoxLayout(this);
        auto ctrl = new QHBoxLayout();
        frames = new QSpinBox(this); frames->setRange(1,10); frames->setValue(3);
        policy = new QComboBox(this); policy->addItems({"FIFO","LRU","OPT"});
        btnSim = new QPushButton("Simular", this);
        refs = new QLineEdit("1 2 3 2 4 1 5 2 1 2 3 4 5", this);
        table = new QTableWidget(0, 4, this);
        table->setHorizontalHeaderLabels({"t","page","hit","frames"});
        lay->addLayout(ctrl);
        ctrl->addWidget(new QLabel("Frames:")); ctrl->addWidget(frames);
        ctrl->addWidget(new QLabel("Política:")); ctrl->addWidget(policy);
        ctrl->addWidget(new QLabel("Refs:")); ctrl->addWidget(refs);
        ctrl->addWidget(btnSim);
        lay->addWidget(table);

        connect(btnSim,&QPushButton::clicked,this,[=](){
            std::vector<int> r;
            for (auto s : refs->text().split(" ", Qt::SkipEmptyParts)) r.push_back(s.toInt());
            std::unique_ptr<ReplacementPolicy> pol;
            if (policy->currentText()=="FIFO") pol.reset(new FIFO());
            else if (policy->currentText()=="LRU") pol.reset(new LRU());
            else pol.reset(new OPT());
            PageTable pt(frames->value(), pol.get());
            table->setRowCount(0);
            for (int i=0;i<(int)r.size();++i){
                auto evt = pt.access(r, i);
                table->insertRow(table->rowCount());
                int row = table->rowCount()-1;
                table->setItem(row,0,new QTableWidgetItem(QString::number(evt.timeIndex)));
                table->setItem(row,1,new QTableWidgetItem(QString::number(evt.page)));
                table->setItem(row,2,new QTableWidgetItem(evt.hit?"hit":"fault"));
                QStringList fr;
                for (int f : pt.frames()) fr<< (f<0?"-":QString::number(f));
                table->setItem(row,3,new QTableWidgetItem(fr.join(",")));
            }
        });
    }
private:
    QSpinBox* frames; QComboBox* policy; QLineEdit* refs; QPushButton* btnSim; QTableWidget* table;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto plan = new PlanWidget(this);
    auto conc = new ConcurrencyView(this);
    auto mem  = new MemWidget(this);

    auto *tabPlanContainer = ui->centralwidget->findChild<QWidget*>("planContainer");
    auto *tabConcContainer = ui->centralwidget->findChild<QWidget*>("concContainer");
    auto *tabMemContainer  = ui->centralwidget->findChild<QWidget*>("memContainer");

    auto plc1 = new QVBoxLayout(tabPlanContainer); plc1->addWidget(plan);
    auto plc2 = new QVBoxLayout(tabConcContainer); plc2->addWidget(conc);
    auto plc3 = new QVBoxLayout(tabMemContainer);  plc3->addWidget(mem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.moc"
