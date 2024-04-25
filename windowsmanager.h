#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H

#include <startmenu.h>
#include <mainwindow.h>
#include <statwindow.h>

#include <QObject>


class WindowsManager : public QObject
{
    Q_OBJECT

private:
    StartMenu* _startMenu = nullptr;
    MainWindow* _mainWindow = nullptr;
    StatWindow* _statWindow = nullptr;

public:
    explicit WindowsManager(QObject *parent = nullptr);
    ~WindowsManager();

private slots:
    void startSimulation();
    void endSimulation();
    void resetSimulation();
};

#endif // WINDOWSMANAGER_H
