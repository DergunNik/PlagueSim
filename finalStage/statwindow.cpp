#include "statwindow.h"
#include "ui_statwindow.h"

StatWindow::StatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StatWindow)
{
    ui->setupUi(this);
}

StatWindow::StatWindow(Statistics *statistics, CityManager* manager, QWidget *parent) :
    StatWindow(parent)
{

}

StatWindow::~StatWindow()
{
    delete ui;
}
