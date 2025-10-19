#include "ConcurrencyView.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>

ConcurrencyView::ConcurrencyView(QWidget* parent)
    : QWidget(parent),
    pc(8, nullptr),
    rw(nullptr),
    sb(3, nullptr),
    semDemo(nullptr)
{
    auto lay = new QVBoxLayout(this);

    // -------------------------
    // PRODUCTOR-CONSUMIDOR
    // -------------------------
    auto lblPC = new QLabel("Producer–Consumer (buffer)", this);
    tblBuf = new QTableWidget(1, 8, this);
    lay->addWidget(lblPC);
    lay->addWidget(tblBuf);

    // -------------------------
    // LECTORES–ESCRITORES
    // -------------------------
    lblRW = new QLabel("Lectores–Escritores: (inactivo)", this);
    lay->addWidget(lblRW);

    // -------------------------
    // BARBERO DORMILÓN
    // -------------------------
    lblSB = new QLabel("Barbero Dormilón: (durmiendo)", this);
    lay->addWidget(lblSB);

    // -------------------------
    // SEMÁFORO DEMO
    // -------------------------
    lblSem = new QLabel("Semáforo: valor=1 | esperando=0", this);
    barSem = new QProgressBar(this);
    barSem->setRange(0, 1);
    barSem->setValue(1);
    barSem->setTextVisible(true);
    barSem->setFormat("Libre");
    lay->addWidget(lblSem);
    lay->addWidget(barSem);

    // -------------------------
    // BOTONES DE CONTROL
    // -------------------------
    auto btnStart = new QPushButton("Start All", this);
    auto btnStop  = new QPushButton("Stop All", this);
    lay->addWidget(btnStart);
    lay->addWidget(btnStop);

    // -------------------------
    // CONSOLA VISUAL
    // -------------------------
    txtLog = new QPlainTextEdit(this);
    txtLog->setReadOnly(true);
    txtLog->setPlaceholderText("Eventos del sistema de concurrencia...");
    txtLog->setStyleSheet("background-color: #111; color: #0f0; font-family: Consolas; font-size: 11pt;");
    lay->addWidget(txtLog);

    setLayout(lay);

    // -------------------------
    // CONEXIONES DE CONTROL
    // -------------------------
    connect(btnStart, &QPushButton::clicked, &pc, &ProducerConsumer::start);
    connect(btnStop,  &QPushButton::clicked, &pc, &ProducerConsumer::stop);
    connect(btnStart, &QPushButton::clicked, &rw, &ReadersWriters::start);
    connect(btnStop,  &QPushButton::clicked, &rw, &ReadersWriters::stop);
    connect(btnStart, &QPushButton::clicked, &sb, &SleepingBarber::start);
    connect(btnStop,  &QPushButton::clicked, &sb, &SleepingBarber::stop);
    connect(btnStart, &QPushButton::clicked, &semDemo, &SemaphoreDemo::start);
    connect(btnStop,  &QPushButton::clicked, &semDemo, &SemaphoreDemo::stop);

    // -------------------------
    // 🔹 RESET VISUAL DESPUÉS DE DETENER TODO
    // -------------------------
    connect(btnStop, &QPushButton::clicked, this, [this]() {

        // Limpia el buffer visual
        for (int r = 0; r < tblBuf->rowCount(); ++r) {
            for (int c = 0; c < tblBuf->columnCount(); ++c) {
                tblBuf->setItem(r, c, new QTableWidgetItem("-"));
            }
        }
        tblBuf->setHorizontalHeaderLabels(QStringList() << "count=0");

        // Reinicia etiquetas de estado
        lblRW->setText("Lectores–Escritores: (inactivo)");
        lblSB->setText("Barbero Dormilón: (durmiendo)");
        lblSem->setText("Semáforo: valor=1 | esperando=0");
        barSem->setValue(1);
        barSem->setFormat("Libre");
        barSem->setStyleSheet("QProgressBar::chunk { background: green; }");

        // Limpia consola visual
        txtLog->clear();
        txtLog->appendPlainText("🟥 Simulación detenida y restablecida.\n");
    });

    // -------------------------
    // PRODUCTOR-CONSUMIDOR (Tabla)
    // -------------------------
    connect(&pc, &ProducerConsumer::bufferUpdated, this,
            [this](QVector<int> buffer, int, int, int count){
                for (int c = 0; c < tblBuf->columnCount(); ++c) {
                    auto* it = new QTableWidgetItem(
                        c < buffer.size() ? QString::number(buffer[c]) : "-"
                        );
                    tblBuf->setItem(0, c, it);
                }
                tblBuf->setHorizontalHeaderLabels(
                    QStringList() << QString("count=%1").arg(count)
                    );
            });

    // -------------------------
    // LECTORES–ESCRITORES (Etiquetas)
    // -------------------------
    connect(&rw, &ReadersWriters::startedReading, this, [this]() {
        lblRW->setText("Lectores–Escritores: leyendo...");
    });
    connect(&rw, &ReadersWriters::startedWriting, this, [this]() {
        lblRW->setText("Lectores–Escritores: escribiendo...");
    });
    connect(&rw, &ReadersWriters::finished, this, [this]() {
        lblRW->setText("Lectores–Escritores: inactivo");
    });

    // -------------------------
    // BARBERO DORMILÓN (Etiquetas)
    // -------------------------
    connect(&sb, &SleepingBarber::startedCutting, this, [this]() {
        lblSB->setText("Barbero Dormilón: atendiendo cliente...");
    });
    connect(&sb, &SleepingBarber::sleeping, this, [this]() {
        lblSB->setText("Barbero Dormilón: durmiendo...");
    });
    connect(&sb, &SleepingBarber::finished, this, [this]() {
        lblSB->setText("Barbero Dormilón: libre");
    });

    // -------------------------
    // SEMÁFORO (Actualización Visual)
    // -------------------------
    connect(&semDemo, &SemaphoreDemo::statusChanged, this,
            [this](int value, int waiting, bool locked){
                lblSem->setText(QString("Semáforo: valor=%1 | esperando=%2")
                                    .arg(value)
                                    .arg(waiting));
                barSem->setValue(value);
                if (locked) {
                    barSem->setStyleSheet("QProgressBar::chunk { background: red; }");
                    barSem->setFormat("Bloqueado");
                    txtLog->appendPlainText("🚫 Proceso esperando semáforo...");
                } else {
                    barSem->setStyleSheet("QProgressBar::chunk { background: green; }");
                    barSem->setFormat("Libre");
                    txtLog->appendPlainText("✅ Semáforo liberado.");
                }
            });

    // -------------------------
    // REGISTRO DE EVENTOS EN CONSOLA VISUAL
    // -------------------------
    auto appendLog = [this](const QString& msg) {
        txtLog->appendPlainText(msg);
    };

    // Productor–Consumidor
    connect(&pc, &ProducerConsumer::produced, this, [appendLog](int v){
        appendLog(QString("🟢 Producido: %1").arg(v));
    });
    connect(&pc, &ProducerConsumer::consumed, this, [appendLog](int v){
        appendLog(QString("🔵 Consumido: %1").arg(v));
    });

    // Lectores–Escritores
    connect(&rw, &ReadersWriters::startedReading, this, [appendLog](){
        appendLog("📘 Lector comenzó a leer");
    });
    connect(&rw, &ReadersWriters::startedWriting, this, [appendLog](){
        appendLog("✏️ Escritor comenzó a escribir");
    });
    connect(&rw, &ReadersWriters::finished, this, [appendLog](){
        appendLog("✅ Lectura o escritura finalizada");
    });

    // Barbero Dormilón
    connect(&sb, &SleepingBarber::sleeping, this, [appendLog](){
        appendLog("😴 Barbero durmiendo...");
    });
    connect(&sb, &SleepingBarber::startedCutting, this, [appendLog](){
        appendLog("💈 Barbero atendiendo cliente...");
    });
    connect(&sb, &SleepingBarber::finished, this, [appendLog](){
        appendLog("✂️ Corte finalizado");
    });
}
