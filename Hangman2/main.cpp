#include <QApplication>
#include <screenmanager.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenManager sm;
    return a.exec();
}
