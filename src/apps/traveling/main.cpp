/*
 * Application start-up
 *
 * Frank Cieslok, Aug. 2011
 */

#include <QtGui/QApplication>

#include <GEPScopeMainWindow.h>

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);
    GEP::Scope::MainWindow main_window;
    main_window.show();

    return app.exec();
}
