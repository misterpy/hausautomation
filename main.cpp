#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtGui/QGuiApplication>
#include <QQmlContext>

#include "controllogic.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("controlLogic",new ControlLogic);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
