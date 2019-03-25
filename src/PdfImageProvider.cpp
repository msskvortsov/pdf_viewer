#include "PdfImageProvider.h"

#include <QDebug>
#include <QRegExp>

PdfImageProvider::PdfImageProvider()  : QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage PdfImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size);
    Q_UNUSED(requestedSize);

    qDebug() << "Image requested: " << id;
    QRegExp rx("^(.*)[?]p=(\\d+)[&]dpi=(\\d+)", Qt::CaseInsensitive, QRegExp::RegExp2);

    if (rx.indexIn(id) == -1) {
        qDebug() << "Bad request. Expected format: image://pdf/<path>?p=<page number>&dpi=<resolution>";
        return QImage();
    }

    QUrl path(rx.cap(1));
    uint page = rx.cap(2).toUInt();
    uint dpi = rx.cap(3).toUInt();
    dpi = dpi == 0 ? 150 : dpi;

    if (path.isLocalFile() && path != _sourcePath)
        this->_popplerDocument.reset(Poppler::Document::load(path.toLocalFile()));

    if (this->_popplerDocument.isNull() || this->_popplerDocument->isLocked()) {
        qDebug() << "Can not process file:" << path.toString();
    } else {        
        this->_popplerDocument->setRenderHint(Poppler::Document::TextAntialiasing);
        this->_popplerDocument->setRenderHint(Poppler::Document::Antialiasing);
        this->_popplerDocument->setRenderHint(Poppler::Document::TextHinting);
        _sourcePath = path;

        qDebug() << "Trying to load page with index: " << (page);      
        QScopedPointer<Poppler::Page> popplerPage(this->_popplerDocument->page(page));
        if (popplerPage.isNull()) {
            qDebug() << "Cannot read page with index:" << (page);
        } else {
            qDebug() << "Loading was successful";
            return popplerPage->renderToImage(dpi, dpi);
        }
    }

    return QImage();
}
