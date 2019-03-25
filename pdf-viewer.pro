TARGET = pdf-viewer

CONFIG += sailfishapp

SOURCES += \
    src/pdf-viewer.cpp \
    src/PdfImageProvider.cpp \
    src/PdfHandler.cpp

HEADERS += \
    src/PdfImageProvider.h \
    src/PdfHandler.h

DISTFILES += \
    qml/pdf-viewer.qml \
    qml/cover/CoverPage.qml \
    qml/pages/ViewerPage.qml \
    rpm/pdf-viewer.yaml \
    translations/*.ts \
    pdf-viewer.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += sailfishapp_i18n
TRANSLATIONS += translations/pdf-viewer-ru.ts

LIBS += -lpoppler-qt5
INCLUDEPATH += /usr/include/poppler/qt5
