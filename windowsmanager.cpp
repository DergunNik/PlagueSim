#include "windowsmanager.h"

WindowsManager::WindowsManager(QObject *parent)
    : QObject{parent}
{
    _startMenu = new StartMenu();
    connect(_startMenu, &StartMenu::startSimulation, this, &WindowsManager::startSimulation);
    _startMenu->show();
}


WindowsManager::~WindowsManager()
{
    // if (_startMenu != nullptr) {
    //     delete _startMenu;
    // }
    // if (_mainWindow != nullptr) {
    //     delete _mainWindow;
    // }
    // if (_statWindow != nullptr) {
    //     delete _statWindow;
    // }
}


void WindowsManager::startSimulation()
{
    _mainWindow = new MainWindow(std::move(_startMenu->getGenerator()));
    connect(_mainWindow, &MainWindow::endSimulation, this, &WindowsManager::endSimulation);
    _mainWindow->show();
    _startMenu->hide();
    _startMenu->setEnabled(true);
}


void WindowsManager::endSimulation()
{
    _statWindow = new StatWindow(_mainWindow->statistics(), _mainWindow->cityManager());
    _statWindow->show();
    _mainWindow->hide();
    _mainWindow->setEnabled(true);
}
