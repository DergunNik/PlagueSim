#include "districtvisualizer.h"
#include "ui_districtvisualizer.h"


DistrictVisualizer::DistrictVisualizer(QWidget *parent) :
    QWidget(parent),
    _scene(new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, this)),
    ui(new Ui::DistrictVisualizer)
{
    ui->setupUi(this);
    connect(ui->backBtn, &QPushButton::clicked, this, &DistrictVisualizer::backBtnClicked);
}


DistrictVisualizer::DistrictVisualizer(District* district, QWidget *parent) :
    QWidget(parent),
    _district(district),
    _scene(new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT, this)),
    ui(new Ui::DistrictVisualizer)
{
    ui->setupUi(this);
    connect(ui->backBtn, &QPushButton::clicked, this, &DistrictVisualizer::backBtnClicked);

    reset(district);

    ui->graphicsView->setScene(_scene);
    ui->idLbl->setText("ID: " + QString::number(_district->pos().first) + "/" + QString::number(_district->pos().second));
}


DistrictVisualizer::~DistrictVisualizer()
{
    delete ui;
}


QPointF DistrictVisualizer::randVect()
{
    QPointF v((1 - QRandomGenerator::global()->bounded(DELTA)),
              1 - QRandomGenerator::global()->bounded(DELTA));
    float length = qSqrt(v.x() * v.x() + v.y() * v.y());
    if (length > NULL_PRECISION) {
        v.rx() /= length;
        v.ry() /= length;
    }
    return v;
}


void DistrictVisualizer::initHome()
{
    QSet<uint> familiesMem;
    for (auto now : _district->citizens()) {
        familiesMem.insert(now->familyNumber());
    }

    const uint familyAmnt = familiesMem.size();
    const uint matrixSize = qSqrt(familyAmnt) + 1;

    float boxWidth = _districtWidth / matrixSize;
    float boxHeight = _districtHeight / matrixSize;

    uint lastFamily = -1;
    uint boxCntr = -1;

    QRectF lastBox(0, 0, boxWidth, boxHeight);

    for (uint i = 0; i < _district->citizens().size(); ++i) {
        if (_district->citizens().at(i)->familyNumber() != lastFamily) {
            ++boxCntr;

            lastBox = QRectF(boxWidth * (boxCntr / matrixSize) + SCENE_TAB,
                             boxHeight * (boxCntr % matrixSize) + SCENE_TAB,
                             boxWidth, boxHeight);
            _scene->addRect(lastBox);

            lastFamily = _district->citizens().at(i)->familyNumber();
        }

        QPointF startPos(QPointF(lastBox.x() + boxWidth / 2, lastBox.y() + boxHeight / 2) +
                         randVect() * (CITIZEN_RADIUS * 2));
        auto tempBall = new Ball(startPos, randVect(), CITIZEN_RADIUS, _district->citizens().at(i));

        tempBall->setRect(QRectF(boxWidth * (boxCntr / matrixSize) + SCENE_TAB + CITIZEN_RADIUS,
                                 boxHeight * (boxCntr % matrixSize) + SCENE_TAB + CITIZEN_RADIUS,
                                 boxWidth - 2 * CITIZEN_RADIUS, boxHeight - 2 * CITIZEN_RADIUS));        
        tempBall->setBasicVel(tempBall->basicVel() / HOME_SPEED_DECREASE);

        _scene->addItem(tempBall);
    }
}

void DistrictVisualizer::initNotHome(District *district)
{
    for (uint i = 0; i < _district->citizens().size(); ++i) {
        QPointF startPos(((CITIZEN_TAB + 2 * CITIZEN_RADIUS) * i) % (_districtWidth - CITIZEN_TAB) + BASE_TAB,
                         ((CITIZEN_TAB + 2 * CITIZEN_RADIUS) * i) % (_districtHeight - CITIZEN_TAB) + BASE_TAB);
        auto tempBall = new Ball(startPos, randVect(), CITIZEN_RADIUS, _district->citizens().at(i));
        if (district->type() == HOSPITAL) {
            tempBall->setBasicVel(tempBall->basicVel() / HOSPITAL_SPEED_DECREASE);
        }

        tempBall->setRect(QRectF(SCENE_TAB + CITIZEN_RADIUS, SCENE_TAB + CITIZEN_RADIUS,
                                 _districtWidth - 2 * CITIZEN_RADIUS, _districtHeight - 2 * CITIZEN_RADIUS));
        _scene->addItem(tempBall);
    }
}

void DistrictVisualizer::reset(District *district)
{
    _district = district;
    _districtWidth = (SCENE_WIDTH - 2 * SCENE_TAB) * district->size();
    _districtHeight = (SCENE_HEIGHT - 2 * SCENE_TAB) * district->size();
    _scene->clear();

    QRectF distRect(SCENE_TAB, SCENE_TAB, _districtWidth, _districtHeight);
    _scene->setSceneRect(0, 0, _districtWidth + 2 * SCENE_TAB, _districtHeight + 2 * SCENE_TAB);
    _scene->addRect(distRect);

    updateInfo();

    if (_district->citizens().isEmpty()) {
        return;
    }

    if (district->type() == HOME) {
        initHome();
    } else {
        initNotHome(district);
    }
}


void DistrictVisualizer::update()
{
    reset(_district);
}


void DistrictVisualizer::updateInfo()
{
    ui->asympInfLbl->setText(QString("Больных без симптомов: ") +
                             QString::number(_district->proportion().asymptomaticallyInf));
    ui->explInfLbl->setText(QString("Больных c симптомами: ") +
                             QString::number(_district->proportion().explicitlyInf));
    ui->nInfLbl->setText(QString("Здоровых: ") +
                             QString::number(_district->proportion().notInfected));
}


void DistrictVisualizer::backBtnClicked()
{
    emit backToMap();
}


void DistrictVisualizer::moveAll(ushort _speedMult)
{
    for (auto& now : _scene->items()) {
        if (dynamic_cast<Ball*>(now)) {
            auto tempBall = dynamic_cast<Ball*>(now);
            tempBall->move(_speedMult);
        }
    }
}
