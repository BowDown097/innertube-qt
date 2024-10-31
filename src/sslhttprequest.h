#pragma once
#include <QAbstractSocket>
#include <QSslError>
#include <QUrl>
#include <wobjectimpl.h>

class QJsonObject;
class QSslSocket;

class SslHttpRequest : public QObject
{
    W_OBJECT(SslHttpRequest)
public:
    struct Error : std::variant<std::monostate, QAbstractSocket::SocketError, QSslError::SslError>
    {
        bool isSuccess() const
        { return std::holds_alternative<std::monostate>(*this); }
        const QAbstractSocket::SocketError* socketError() const
        { return std::get_if<QAbstractSocket::SocketError>(this); }
        const QSslError::SslError* sslError() const
        { return std::get_if<QSslError::SslError>(this); }
    };

    enum class RequestMethod { Get, Post };

    explicit SslHttpRequest(const QString& url, RequestMethod method = RequestMethod::Get, QObject* parent = nullptr);
    void send(bool emitPayload = true);

    const QByteArray& body() const { return m_requestBody; }
    QByteArray contentType() const;
    QVariantMap headers() const { return m_headers; }
    QByteArray methodName() const;
    QByteArray payload() const;
    const QByteArray& response() const { return m_response; }

    void setBody(const QByteArray& requestBody, const QByteArray& contentType);
    void setBody(const QJsonObject& json);
    void setHeaders(const QVariantMap& headers) { m_headers = headers; }

    void finished(const QByteArray& response, const Error& error = Error()) W_SIGNAL(finished, response, error)
private:
    QByteArray m_contentType;
    bool m_emitPayload;
    QVariantMap m_headers;
    QByteArray m_requestBody;
    RequestMethod m_requestMethod;
    QByteArray m_response;
    QSslSocket* m_socket;
    QUrl m_url;

    void disconnected(); W_SLOT(disconnected)
    void errorOccurred(QAbstractSocket::SocketError error); W_SLOT(errorOccurred)
    void makeRequest(); W_SLOT(makeRequest)
    void readyRead(); W_SLOT(readyRead)
    void sslErrors(const QList<QSslError>& errors); W_SLOT(sslErrors)
};

W_REGISTER_ARGTYPE(QAbstractSocket::SocketError)
W_REGISTER_ARGTYPE(QList<QSslError>)
W_REGISTER_ARGTYPE(SslHttpRequest::Error)
W_OBJECT_IMPL_INLINE(SslHttpRequest)
