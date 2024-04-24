#ifndef STARTMENU_H
#define STARTMENU_H

#include <generations.h>
#include <basicstructs.h>

#include <QMainWindow>
#include <QMessageBox>


namespace Ui {
class StartMenu;
}


const int DISTRICT_CAPACITY = 50;


class StartMenu : public QMainWindow
{
    Q_OBJECT

private:
    Ui::StartMenu *ui;
    GenHandler _generator;

    StartSettings fetchData();

public:
    explicit StartMenu(QWidget *parent = nullptr);
    ~StartMenu() override;

    GenHandler& getGenerator();

private slots:
    void showHint();

    // Qt Creator generated slots
    void on_districtsSB_valueChanged(int arg1);
    void on_recoverySB_valueChanged(int arg1);
    void on_respDSB_valueChanged(double arg1);
    void on_semirespDSB_valueChanged(double arg1);
    void on_startBtn_clicked();

signals:
    void startSimulation();
};

#endif // STARTMENU_H
