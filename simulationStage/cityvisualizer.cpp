#include "cityvisualizer.h"
#include "ui_cityvisualizer.h"

CityVisualizer::CityVisualizer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CityVisualizer)
{
    ui->setupUi(this);
}


CityVisualizer::CityVisualizer(CityManager* cManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CityVisualizer),
    _scene(new QGraphicsScene())
{
    ui->setupUi(this);

    reset(cManager);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/nS")));
}


CityVisualizer::~CityVisualizer()
{
    delete ui;
}


void CityVisualizer::reset(CityManager* cManager)
{
    _scene->clear();

    for(auto now : cManager->districtsManager().getAllDistricts()) {
        auto item = new GraphicsDistrictItem(*now, DISTRICT_RADIUS);
        item->setPos(item->ID().first * (DISTRICT_RADIUS * 2 + DISTRICT_TAB),
                     item->ID().second * (DISTRICT_RADIUS * 2 + DISTRICT_TAB));
        _scene->addItem(item);
        connect(item, &GraphicsDistrictItem::selected, this, &CityVisualizer::selectedItem);
    }
}


void CityVisualizer::setDay(bool isDay)
{
    if (isDay) {
        ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/dS")));
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(70, 255, 0, 100));
        qApp->setPalette(palette);
    } else {
        ui->graphicsView->setBackgroundBrush(QBrush(QImage(":/nS")));
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(0, 255, 100, 50));
        palette.setColor(QPalette::WindowText, Qt::white);
        qApp->setPalette(palette);
    }
}


void CityVisualizer::selectedItem(ushort x, ushort y)
{
    emit selectedDistrict(x, y);
}
