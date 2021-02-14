#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlProperty>
#include <QQuickItem>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject * rootObject = engine.rootObjects().first();

    //Show item count
    qDebug() << "Item count : " << rootObject->children().count();
    qDebug() << "Object name : " << rootObject->objectName();

    //Find the rectangles
    QList<QQuickItem*> list =rootObject->findChildren<QQuickItem*>("rect");
    if( list.count() > 0){
        qDebug() << "Rectangle count " << list.count();
        foreach (QQuickItem * item, list) {

            qDebug() << "-----------ITEM-------------";
            qDebug() << "The color is : "<< item->property("color").toString();

            QVariant varColor = item->property("color");

            QColor color = varColor.value<QColor>();

            qDebug() << "The color components : " << color.red() << " "
                     << color.green() << " "
                     << color.blue() ;

            if( color.green() > 0){
                item->setProperty("radius",30);
            }
            if(color.blue() > 0){
                item->setProperty("height",200);
            }

        }
    }

    //Find Text Area
    QQuickItem * quickItem = rootObject->findChild<QQuickItem *>("myTextArea");
    quickItem->setProperty("text","Text from C++");

    QQuickItem * greenRect = rootObject->findChild<QQuickItem *>("rect3");
    if( greenRect){
        //greenRect->setProperty("width",150);//Doesn't break the bindinig
        QQmlProperty::write(greenRect,"width",150);//Breaks the binding
    }
    return app.exec();
}
