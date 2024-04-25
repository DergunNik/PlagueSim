#include <windowsmanager.h>
#include <QApplication>
#include <QDockWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowsManager windowsManager;
    return a.exec();
}
