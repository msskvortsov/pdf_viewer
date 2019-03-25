#include <QtQuick/QtQuick>
#include <sailfishapp.h>

#include "PdfImageProvider.h"
#include "PdfHandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView* view = SailfishApp::createView();

    QQmlEngine* engine = view->engine();
    engine->addImageProvider(QLatin1String("pdf"), new PdfImageProvider);
    engine->rootContext()->setContextProperty("pdfHandler", QVariant::fromValue(new PdfHandler()));

    view->setSource(SailfishApp::pathToMainQml());
    view->show();
    return app->exec();
}
