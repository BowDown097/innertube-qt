#include "sslhttprequest.h"

SslHttpRequest::SslHttpRequest(const QString& url, RequestMethod method, QObject* parent)
    : QObject(parent), m_requestMethod(method), m_sslSocket(new QSslSocket(this)), m_url(QUrl(url))
{
    connect(m_sslSocket, &QSslSocket::disconnected, this, &SslHttpRequest::disconnected);
    connect(m_sslSocket, &QSslSocket::encrypted, this, &SslHttpRequest::makeRequest);
    connect(m_sslSocket, &QSslSocket::errorOccurred, this, &SslHttpRequest::errorOccurred);
    connect(m_sslSocket, &QSslSocket::readyRead, this, &SslHttpRequest::readyRead);
    connect(m_sslSocket, &QSslSocket::sslErrors, this, &SslHttpRequest::sslErrors);
}

void SslHttpRequest::disconnected()
{
    emit finished(m_response);
}

void SslHttpRequest::errorOccurred(QAbstractSocket::SocketError error)
{
    // Connection: close header throws a RemoteHostClosedError; this mitigates it.
    if (error != QAbstractSocket::RemoteHostClosedError && m_sslSocket->sslHandshakeErrors().isEmpty())
        emit finished(m_sslSocket->errorString().toUtf8(), SslHttpRequestError(error));
}

void SslHttpRequest::makeRequest()
{
    QString path = m_url.path();
    if (path.isEmpty())
        path = "/";

    QString request;
    request += QStringLiteral("%1 %2 HTTP/1.0\r\n").arg(m_requestMethod == RequestMethod::Get ? "GET" : "POST", path);
    request += "Host: " + m_url.host() + "\r\n";
    for (auto it = m_headers.cbegin(); it != m_headers.cend(); ++it)
        request += it.key() + ": " + it.value() + "\r\n";

    if (m_requestMethod == RequestMethod::Post)
    {
        request += "Content-Type: " + m_contentType + "\r\n";
        request += "Content-Length: " + QByteArray::number(m_requestBody.size()) + "\r\n";
        request += "Connection: close\r\n\r\n";
        request += m_requestBody;
    }
    else
    {
        request += "Connection: close\r\n\r\n";
    }

    m_sslSocket->write(request.toUtf8());
}

QByteArray SslHttpRequest::payload() const
{
    return m_response.mid(m_response.indexOf("\r\n\r\n") + 4);
}

void SslHttpRequest::readyRead()
{
    m_response.append(m_sslSocket->readAll());
}

void SslHttpRequest::send()
{
    if (!m_url.isValid())
    {
        emit finished("Invalid URL", SslHttpRequestError(QAbstractSocket::HostNotFoundError));
        return;
    }

    m_sslSocket->connectToHostEncrypted(m_url.host(), m_url.scheme() == "http" ? m_url.port(80) : m_url.port(443));
    m_sslSocket->waitForConnected();
}

void SslHttpRequest::sslErrors(const QList<QSslError>& errors)
{
    emit finished(errors[0].errorString().toUtf8(), SslHttpRequestError(errors[0].error()));
}
