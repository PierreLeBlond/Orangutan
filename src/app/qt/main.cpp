#include <QApplication>

#include "app/qt/screen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;

    QFile File("../src/style/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    a.setStyleSheet(StyleSheet);

    File.close();

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
