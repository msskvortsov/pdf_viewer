#ifndef PDFHANDLER_H
#define PDFHANDLER_H

#include <QObject>
#include <QUrl>

class PdfHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(uint pageCount READ pageCount NOTIFY pageCountChanged)
    Q_PROPERTY(uint currentPage READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(uint resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
    Q_PROPERTY(bool empty READ isEmpty NOTIFY emptyChanged)

public:
    PdfHandler(QObject* parent = nullptr);

    QUrl source() const;
    uint resolution() const;
    uint pageCount() const;
    uint currentPage() const;
    bool isEmpty() const;

    void setSource(const QUrl& path);
    void setCurrentPage(const uint& number);
    void setResolution(const uint& dpi);

    Q_INVOKABLE QString pageRequest(const uint& page);
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void previousPage();

signals:
    void sourceChanged();
    void pageCountChanged();
    void emptyChanged();
    void currentPageChanged();
    void resolutionChanged();

private:
    QUrl _source;
    QString _lastPageRequest;
    uint _resolution = 150;
    uint _pageCount = 0;
    uint _currentPage = 0;


};

#endif // PDFHANDLER_H
