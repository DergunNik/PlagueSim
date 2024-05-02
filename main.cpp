#include <windowsmanager.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon"));
    a.setApplicationName("PlagueSim");

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(0, 255, 100, 120));
    a.setPalette(palette);

    WindowsManager windowsManager;
    return a.exec();
}
