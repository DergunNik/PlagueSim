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


void CityVisualizer::selectedItem(ushort x, ushort y)
{
    emit selectedDistrict(x, y);
}
