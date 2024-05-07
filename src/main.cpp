#include "interface/login/login.h"
#include "interface/main/mainwindow.h"
#include "route/route.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login loginObj;

//    w.show();
//    return a.exec();

    w.setLogin(&loginObj);

    Route* route = Route::NewInstance();
    route->setLoginInterface(&loginObj);
    route->setMainWindowInterface(&w);

    if (loginObj.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }
}
