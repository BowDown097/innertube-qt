#include "sslhttprequest.h"
#include <QJsonDocument>
#include <QSslSocket>

SslHttpRequest::SslHttpRequest(const QString& url, RequestMethod method, QObject* parent)
    : QObject(parent), m_requestMethod(method), m_socket(new QSslSocket(this)), m_url(QUrl(url))
{
    connect(m_socket, &QSslSocket::disconnected, this, &SslHttpRequest::disconnected);
    connect(m_socket, &QSslSocket::encrypted, this, &SslHttpRequest::makeRequest);
    connect(m_socket, &QSslSocket::errorOccurred, this, &SslHttpRequest::errorOccurred);
    connect(m_socket, &QSslSocket::readyRead, this, &SslHttpRequest::readyRead);
    connect(m_socket, qOverload<const QList<QSslError>&>(&QSslSocket::sslErrors), this, &SslHttpRequest::sslErrors);
}

QByteArray SslHttpRequest::contentType() const
{
    if (m_requestMethod != RequestMethod::Post)
        return QByteArray();
    if (!m_contentType.isEmpty())
        return m_contentType;
    return "application/x-www-form-urlencoded";
}

void SslHttpRequest::disconnected()
{
    emit finished(m_emitPayload ? payload() : m_response);
}

void SslHttpRequest::errorOccurred(QAbstractSocket::SocketError error)
{
    // Connection: close header throws a RemoteHostClosedError; this mitigates it.
    if (error != QAbstractSocket::RemoteHostClosedError && m_socket->sslHandshakeErrors().isEmpty())
        emit finished(m_socket->errorString().toUtf8(), Error(error));
}

void SslHttpRequest::makeRequest()
{
    QString path = m_url.hasQuery() ? m_url.path() + "?" + m_url.query(QUrl::FullyEncoded) : m_url.path();
    if (path.isEmpty())
        path = "/";

    QByteArray request;
    request += methodName();
    request += ' ';
    request += path.toUtf8();
    request += " HTTP/1.0\r\n";
    request += "Host: ";
    request += m_url.host().toUtf8();
    request += "\r\n";

    for (auto it = m_headers.cbegin(); it != m_headers.cend(); ++it)
    {
        request += it.key().toUtf8();
        request += ": ";
        request += it.value().toByteArray();
        request += "\r\n";
    }

    if (m_requestMethod == RequestMethod::Post)
    {
        request += "Content-Type: ";
        request += contentType();
        request += "\r\n";
        request += "Content-Length: ";
        request += QByteArray::number(m_requestBody.size());
        request += "\r\n";
        request += "Connection: close\r\n\r\n";
        request += m_requestBody;
    }
    else
    {
        request += "Connection: close\r\n\r\n";
    }

    m_socket->write(request);
}

QByteArray SslHttpRequest::methodName() const
{
    switch (m_requestMethod)
    {
    case RequestMethod::Get:
        return "GET";
    case RequestMethod::Post:
        return "POST";
    default:
        return QByteArray();
    }
}

QByteArray SslHttpRequest::payload() const
{
    return m_response.mid(m_response.indexOf("\r\n\r\n") + 4);
}

void SslHttpRequest::readyRead()
{
    m_response.append(m_socket->readAll());
}

void SslHttpRequest::send(bool emitPayload)
{
    if (!m_url.isValid())
    {
        emit finished("Invalid URL", Error(QAbstractSocket::HostNotFoundError));
        return;
    }

    m_emitPayload = emitPayload;
    m_socket->connectToHostEncrypted(m_url.host(), m_url.scheme() == "http" ? m_url.port(80) : m_url.port(443));
}

void SslHttpRequest::setBody(const QByteArray& requestBody, const QByteArray& contentType)
{
    m_contentType = contentType;
    m_requestBody = requestBody;
}

void SslHttpRequest::setBody(const QJsonObject& json)
{
    m_contentType = "application/json";
    m_requestBody = QJsonDocument(json).toJson(QJsonDocument::Compact);
}

void SslHttpRequest::sslErrors(const QList<QSslError>& errors)
{
    emit finished(errors[0].errorString().toUtf8(), Error(errors[0].error()));
}
