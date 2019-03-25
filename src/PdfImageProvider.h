#ifndef PDFPROVIDER_H
#define PDFPROVIDER_H

#include <QQuickImageProvider>
#include <QUrl>
#include <poppler-qt5.h>

class PdfImageProvider : public QQuickImageProvider
{
public:
    PdfImageProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);

private:
    QScopedPointer<Poppler::Document> _popplerDocument;    
    QUrl _sourcePath;
};

#endif // PDFPROVIDER_H
