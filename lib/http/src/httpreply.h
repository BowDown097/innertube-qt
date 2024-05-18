#pragma once
#include <QObject>

class HttpReply : public QObject
{
    Q_OBJECT
public:
    HttpReply(QObject* parent = nullptr) {}
    virtual QByteArray body() const = 0;
    virtual QByteArray header([[maybe_unused]] const QByteArray& headerName) const { return QByteArray(); }
    virtual const QList<QPair<QByteArray, QByteArray>> headers() const { return QList<QPair<QByteArray, QByteArray>>(); }
    int isSuccessful() const { return statusCode() >= 200 && statusCode() < 300; }
    virtual QString reasonPhrase() const { return QString(); }
    virtual int statusCode() const = 0;
    virtual QUrl url() const = 0;

    template <typename Functor>
    HttpReply& onData(Functor lambda)
    {
        connect(this, &HttpReply::data, this, lambda);
        return *this;
    }

    template <typename Functor>
    HttpReply& onError(Functor lambda)
    {
        connect(this, &HttpReply::error, this, lambda);
        return *this;
    }

    template <typename Functor>
    HttpReply& onFinished(Functor lambda)
    {
        connect(this, &HttpReply::finished, this, lambda);
        return *this;
    }
signals:
    void data(const QByteArray& bytes);
    void error(const QString& message);
    void finished(const HttpReply& reply);
};
