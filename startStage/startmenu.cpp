#include "startmenu.h"
#include "ui_startmenu.h"


StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);

    connect(ui->action, &QAction::triggered, this, &StartMenu::showHint);
}


StartMenu::~StartMenu()
{
    delete ui;
}


void StartMenu::showHint()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Как корректно настроить симуляцию");
    msgBox->setText("Во-первых... Во-вторых...");
    msgBox->setWindowModality(Qt::NonModal);
    msgBox->show();
}


StartSettings StartMenu::fetchData()
{
    Disease disease;
    disease.incubationDays = ui->incubationSB->value();
    disease.latentDays = ui->latentSB->value();
    disease.recoveryDays = ui->recoverySB->value();
    disease.lethality = ui->lethalityDSB->value();
    disease.contagiousness = ui->contagiousDSB->value();

    StartSettings settings;
    settings.disease = disease;
    settings.districtsNumber = ui->districtsSB->value();
    settings.populationNumber = ui->citezensSB->value();
    settings.clinicCapacity = ui->clinicSB->value();
    settings.initialVaccination = ui->vaccineDSB->value();
    settings.responsiblePercent = ui->respDSB->value();
    settings.semiresponsiblePercent = ui->semirespDSB->value();
    settings.irresponsiblePercent =
        1 - ui->respDSB->value() - ui->semirespDSB->value();

    return settings;
}


GenHandler& StartMenu::getGenerator()
{
    return _generator;
}


void StartMenu::on_districtsSB_valueChanged(int arg1)
{
    ui->citezensSB->setMaximum(arg1 * DISTRICT_CAPACITY);
}


void StartMenu::on_recoverySB_valueChanged(int arg1)
{
    ushort delta = qMax(MIN_DELTA_HALFDAYS / 2U, static_cast<ushort>(arg1 * DELTA_PART));

    ui->incubationSB->setMaximum(qMax(arg1 - delta, 0));
    ui->latentSB->setMaximum(qMax(arg1 - delta, 0));
}


void StartMenu::on_respDSB_valueChanged(double arg1)
{
    ui->semirespDSB->setMaximum(1 - arg1);
    ui->irrespDSB->setMaximum(1 - arg1 - ui->semirespDSB->value());
    ui->irrespDSB->setValue(1 - arg1 - ui->semirespDSB->value());
}


void StartMenu::on_semirespDSB_valueChanged(double arg1)
{
    ui->irrespDSB->setMaximum(1 - arg1 - ui->respDSB->value());
    ui->irrespDSB->setValue(1 - arg1 - ui->respDSB->value());
}


void StartMenu::on_startBtn_clicked()
{
    _generator = GenHandler(fetchData());
    emit startSimulation();
}
