#ifndef SSLHTTPREQUEST_H
#define SSLHTTPREQUEST_H
#include <QJsonObject>
#include <QSslSocket>
#include <QUrl>
#include <wobjectimpl.h>

struct SslHttpRequestError
{
    enum class ErrorType { Success, SocketError, SslError };
    ErrorType errorType;

    union
    {
        QAbstractSocket::SocketError socketError;
        QSslError::SslError sslError;
    };

    explicit SslHttpRequestError(QAbstractSocket::SocketError error) : errorType(ErrorType::SocketError), socketError(error) {}
    explicit SslHttpRequestError(QSslError::SslError error) : errorType(ErrorType::SslError), sslError(error) {}
    SslHttpRequestError() = default;
};

class SslHttpRequest : public QObject
{
    W_OBJECT(SslHttpRequest)
public:
    enum class RequestMethod { Get, Post };
    explicit SslHttpRequest(const QString& url, RequestMethod method = RequestMethod::Get, QObject* parent = nullptr);
    void send(bool emitPayload = true);

    QByteArray body() const { return m_requestBody; }
    QVariantMap headers() const { return m_headers; }
    QByteArray payload() const;
    QByteArray response() const { return m_response; }

    void setBody(const QByteArray& requestBody, const QString& contentType) { m_contentType = contentType; m_requestBody = requestBody; }
    void setBody(const QJsonObject& json);
    void setHeaders(const QVariantMap& headers) { m_headers = headers; }

    void finished(const QByteArray& response, const SslHttpRequestError& error = SslHttpRequestError())
    W_SIGNAL(finished, response, error)
private:
    QString m_contentType;
    bool m_emitPayload;
    QVariantMap m_headers;
    QByteArray m_requestBody;
    RequestMethod m_requestMethod;
    QByteArray m_response;
    QSslSocket* m_sslSocket;
    QUrl m_url;

    void disconnected(); W_SLOT(disconnected)
    void errorOccurred(QAbstractSocket::SocketError error); W_SLOT(errorOccurred)
    void makeRequest(); W_SLOT(makeRequest)
    void readyRead(); W_SLOT(readyRead)
    void sslErrors(const QList<QSslError>& errors); W_SLOT(sslErrors)
};

W_REGISTER_ARGTYPE(QAbstractSocket::SocketError)
W_REGISTER_ARGTYPE(QList<QSslError>)
W_REGISTER_ARGTYPE(SslHttpRequestError)
W_OBJECT_IMPL_INLINE(SslHttpRequest)

#endif // SSLHTTPREQUEST_H
