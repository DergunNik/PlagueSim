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

    // QMainWindow window;

    // // Создайте новое меню
    // QMenu *fileMenu = new QMenu("&File");

    // // Добавьте действия в меню
    // fileMenu->addAction("&Save");

    // // Добавьте меню в строку меню
    // window.menuBar()->addMenu(fileMenu);
    // window.show();


    return a.exec();
}
