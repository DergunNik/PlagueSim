#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::MainWindow(GenHandler &&generator, QWidget *parent) :
    _cityManager(new CityManager(std::move(generator))),
    _cityVisualizer(new CityVisualizer(_cityManager, this)),
    _layout(new QGridLayout(this)),
    _timer(new QTimer(this)),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->speedSlider, &QSlider::valueChanged, this, &MainWindow::speedChanged);
    connect(ui->continueCB, &QCheckBox::stateChanged, this, &MainWindow::pauseStateChanged);
    connect(ui->endBtn, &QPushButton::clicked, this, &MainWindow::endBtnClicked);

    connect(_cityVisualizer, &CityVisualizer::selectedDistrict, this, &MainWindow::detrictSelected);
    
    _layout->addWidget(ui->statLbl, 0, 1);
    _layout->addWidget(_cityVisualizer, 1, 1, 1, 2);
    _layout->addWidget(ui->groupBox, 1, 0);
    _layout->addWidget(ui->newsLineEdit, 0, 2);
    _layout->addWidget(ui->endBtn, 0, 0);
    ui->centralwidget->setLayout(_layout);

    for (auto& now : _cityManager->citizens()) {
        now.setDisease(&_cityManager->settings().disease);
        auto temp = now.schedule();
        temp.setDistrictManager(&_cityManager->districtsManager());
        now.setSchedule(temp);
    }

    _cityManager->citizens()[0].makeZeroParient();
    _cityManager->citizens()[0].setResponsibility(IRRESPONSIBLE);

    for (auto now : _cityManager->districtsManager().getAllDistricts()) {
        _distrVis[now->pos()] = new DistrictVisualizer(now, this);
        _distrVis[now->pos()]->hide();
        connect(_distrVis[now->pos()], &DistrictVisualizer::backToMap, this, &MainWindow::mapSelected);
        _layout->addWidget(_distrVis[now->pos()], 1, 1, 1, 2);
    }

    _statistics = Statistics(&_cityManager->citizens());
    _who = new WHO(&_statistics, _cityManager, this);
    connect(_who, &WHO::news, this, &MainWindow::getNews);

    speedChanged();
    nextLoop();
    _timer->start(MS_IN_SEC / FPS);
    connect(_timer, &QTimer::timeout, this, &MainWindow::tick);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::tick()
{
    if (!_isPaused) {
        for (auto now : _distrVis) {
            now->moveAll(_tickValue * BASIC_VELOCITY);
        }

        updateTime();

        _tickCntr += _tickValue;
        if (_tickCntr > REQUIRED_TICKS) {
            nextLoop();
        }
    }
}


void MainWindow::getNews(QString news)
{
    ui->newsLineEdit->setText(QString("Последние новости: ") + news);
    if (news.back() == '!') {
        _isPaused = true;
        ui->continueCB->setChecked(false);
    }
}


void MainWindow::nextLoop()
{
    _cityVisualizer->setDay(_halfdaysCntr % 2 == 1);

    _statistics.append();
    _who->checkState();

    for (auto now : _cityManager->districtsManager().getAllDistricts()) {
        now->resetCitizens();
    }

    for (auto& now : _cityManager->citizens()) {
        now.update();

        WHO::toHospital(now, _cityManager);
        now.goTo(_halfdaysCntr);

    }

    _cityVisualizer->reset(_cityManager);

    for (auto now : _distrVis) {
        now->update();
    }

    updateInfo();

    ++_halfdaysCntr;
    _tickCntr = 0;
}

void MainWindow::updateTime()
{
    ushort minuts = (DAY * HOUR) * (static_cast<float>(_tickCntr) / REQUIRED_TICKS);
    ushort hours = minuts / HOUR + (_halfdaysCntr % 2 == 0 ? DAY : 0);
    minuts %= HOUR;
    ui->timeLbl->setText(QString::number(hours) + QString(" часов, ") +
                         QString::number(minuts) + QString("минут"));
}


void MainWindow::updateInfo()
{
    float norm = _statistics.history().back().alive - _statistics.history().back().infected;
    float inf = _statistics.history().back().infected;
    float dead = _statistics.history().back().dead;

    ui->statLbl->setText(QString("Здоровых: ") + QString::number(norm) +
                         QString(", больных: ") + QString::number(inf) +
                         QString(", мёртвых: ") + QString::number(dead) +
                         QString(_halfdaysCntr % 2 == 1 ? " к 12:00" : " к 00:00"));

    ui->dayLbl->setText(QString("День ") + QString::number(_halfdaysCntr / 2 + 1));
}


void MainWindow::speedChanged()
{
    _speed = ui->speedSlider->value() / 100.0F;
    _tickValue = MIN_VALUE + (MAX_VALUE - MIN_VALUE) * _speed;
}


void MainWindow::endBtnClicked()
{
    _timer->stop();
    emit endSimulation();
}


void MainWindow::detrictSelected(ushort x, ushort y)
{
    if (_distrVis.contains(_curDistr)) {
        _distrVis[_curDistr]->hide();
    }
    _cityVisualizer->hide();
    _curDistr = QPair<ushort, ushort>(x, y);
    _distrVis[_curDistr]->show();
}


void MainWindow::mapSelected()
{
    _distrVis[_curDistr]->hide();
    _cityVisualizer->show();
}


void MainWindow::pauseStateChanged()
{
    _isPaused = !ui->continueCB->isChecked();
}


Statistics* MainWindow::statistics()
{
    return &_statistics;
}


CityManager *MainWindow::cityManager()
{
    return _cityManager;
}
