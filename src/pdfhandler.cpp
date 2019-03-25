#include "PdfHandler.h"

#include <QDebug>
#include <QPointer>
#include <poppler-qt5.h>

PdfHandler::PdfHandler(QObject *parent) : QObject(parent)
{
    connect(this, &PdfHandler::sourceChanged,
            this, &PdfHandler::pageCountChanged);
    connect(this, &PdfHandler::sourceChanged,
            this, &PdfHandler::emptyChanged);
}

QUrl PdfHandler::source() const
{
    return this->_source;
}

uint PdfHandler::resolution() const
{
    return this->_resolution;
}

uint PdfHandler::pageCount() const
{
    return this->_pageCount;
}

uint PdfHandler::currentPage() const
{
    return this->_currentPage;
}

bool PdfHandler::isEmpty() const
{
    return this->_source.isEmpty() || (this->_pageCount == 0);
}

void PdfHandler::setSource(const QUrl &path)
{
    if (path.isLocalFile()) {
        QScopedPointer<Poppler::Document> popplerDocument(Poppler::Document::load(path.toLocalFile()));
        if (popplerDocument.isNull() || popplerDocument->isLocked()) {
            qDebug() << "Can not process file:" << path;
            return;
        } else {
            _source = path;
            _pageCount = popplerDocument->numPages();
            _currentPage = 0;
            popplerDocument.reset();
            qDebug()<<"File: " << path << ". Was succesfuly handled";
            emit sourceChanged();
            emit currentPageChanged();
        }
    }
}

void PdfHandler::setCurrentPage(const uint &number)
{
    if (_currentPage == number)
        return;

    if (number >= _pageCount)
        _currentPage = _pageCount - 1;
    else
        _currentPage = number;

    emit currentPageChanged();
}

void PdfHandler::setResolution(const uint &dpi)
{
    _resolution = dpi;
    emit resolutionChanged();
}

void PdfHandler::nextPage()
{
    if (_currentPage + 1 < _pageCount) {
        _currentPage++;
        emit currentPageChanged();
    }
}

void PdfHandler::previousPage()
{
    if (_currentPage >= 1) {
        _currentPage--;
        emit currentPageChanged();
    }
}

QString PdfHandler::pageRequest(const uint &page)
{
    if (page >= _pageCount)
        return QString();
    QString pageRequest = "image://pdf/" + _source.toString() +
            "?p=" + QString::number(page) +
            "&dpi=" + QString::number(_resolution);
    if (page != _currentPage) {
        _currentPage = page;
        emit currentPageChanged();
    }
    return pageRequest;
}
