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
    a.setWindowIcon(QIcon(":/icon"));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0, 255, 100, 120));
    qApp->setPalette(palette);

    WindowsManager windowsManager;
    return a.exec();
}
