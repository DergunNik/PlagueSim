#include "windowsmanager.h"

WindowsManager::WindowsManager(QObject *parent)
    : QObject{parent}
{
    _startMenu = new StartMenu();
    connect(_startMenu, &StartMenu::startSimulation, this, &WindowsManager::startSimulation);
    _startMenu->setWindowTitle(QCoreApplication::applicationName());
    _startMenu->show();
}


WindowsManager::~WindowsManager() {}


void WindowsManager::startSimulation()
{
    _mainWindow = new MainWindow(std::move(_startMenu->getGenerator()));
    connect(_mainWindow, &MainWindow::endSimulation, this, &WindowsManager::endSimulation);
    _mainWindow->setWindowTitle(QCoreApplication::applicationName());
    _mainWindow->show();
    _startMenu->hide();
    _startMenu->setEnabled(true);
}


void WindowsManager::endSimulation()
{
    _statWindow = new StatWindow(_mainWindow->statistics(), _mainWindow->cityManager());
    connect(_statWindow, &StatWindow::reset, this, &WindowsManager::resetSimulation);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0, 255, 100, 120));
    qApp->setPalette(palette);
    _statWindow->setWindowTitle(QCoreApplication::applicationName());
    _statWindow->show();
    _mainWindow->hide();
    _mainWindow->setEnabled(true);
}


void WindowsManager::resetSimulation()
{
    if (_startMenu != nullptr) {
        delete _startMenu;
    }
    if (_mainWindow != nullptr) {
        delete _mainWindow;
    }
    if (_statWindow != nullptr) {
        delete _statWindow;
    }
    _startMenu = new StartMenu();
    connect(_startMenu, &StartMenu::startSimulation, this, &WindowsManager::startSimulation);
    _startMenu->setWindowTitle(QCoreApplication::applicationName());
    _startMenu->show();
}
