#ifndef SSLHTTPREQUEST_H
#define SSLHTTPREQUEST_H
#include <QJsonObject>
#include <QSslSocket>
#include <QUrl>

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
    Q_OBJECT
public:
    enum class RequestMethod { Get, Post };
    explicit SslHttpRequest(const QString& url, RequestMethod method = RequestMethod::Get, QObject* parent = nullptr);
    void send();

    QByteArray body() const { return m_requestBody; }
    QMap<QString, QString> headers() const { return m_headers; }
    QByteArray payload() const;
    QByteArray response() const { return m_response; }

    void setBody(const QByteArray& requestBody, const QString& contentType) { m_contentType = contentType; m_requestBody = requestBody; }
    void setBody(const QJsonObject& json);
    void setHeaders(const QMap<QString, QString>& headers) { m_headers = headers; }
signals:
    void finished(const QByteArray& response, const SslHttpRequestError& error = SslHttpRequestError());
private:
    QString m_contentType;
    QMap<QString, QString> m_headers;
    QByteArray m_requestBody;
    RequestMethod m_requestMethod;
    QByteArray m_response;
    QSslSocket* m_sslSocket;
    QUrl m_url;
private slots:
    void disconnected();
    void errorOccurred(QAbstractSocket::SocketError error);
    void makeRequest();
    void readyRead();
    void sslErrors(const QList<QSslError>& errors);
};

#endif // SSLHTTPREQUEST_H
