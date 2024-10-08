#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include <QThread>

#include "Router.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const int numRouters = 24;

    Router routers[numRouters];

    for (int i = 0; i < numRouters; i++) {
        QThread* thread = new QThread();
        routers[i].moveToThread(thread);
        QObject::connect(thread, &QThread::started, &routers[i], &Router::start);
        thread->start();
    }

    QTimer::singleShot(2000, [&]() {
        for (int i = 0; i < numRouters; ++i) {
            QThread* thread = routers[i].thread();
            thread->quit();
            thread->wait();
        }
        QCoreApplication::quit();
    });

    return a.exec();
}
