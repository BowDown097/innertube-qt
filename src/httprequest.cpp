#include "httprequest.h"
#include <QNetworkDiskCache>
#include <QNetworkReply>
#include <QStandardPaths>

QByteArray HttpReply::header(const QByteArray& key) const
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(parent()))
        return reply->rawHeader(key);
    else
        throw std::runtime_error("Attempting to access reply when request has not been made");
}

const QList<std::pair<QByteArray, QByteArray>>& HttpReply::headers() const
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(parent()))
        return reply->rawHeaderPairs();
    else
        throw std::runtime_error("Attempting to access reply when request has not been made");
}

bool HttpReply::isSuccessful() const
{
    int status = statusCode();
    return status >= 200 && status < 300;
}

QByteArray HttpReply::readAll() const
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(parent()))
        return reply->readAll();
    else
        throw std::runtime_error("Attempting to access reply when request has not been made");
}

int HttpReply::statusCode() const
{
    if (QNetworkReply* reply = qobject_cast<QNetworkReply*>(parent()))
        return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    else
        throw std::runtime_error("Attempting to access reply when request has not been made");
}

QNetworkAccessManager* HttpReply::networkAccessManager()
{
    static thread_local QNetworkAccessManager* nam = [] {
        QNetworkAccessManager* nam = new QNetworkAccessManager;
        nam->setAutoDeleteReplies(true);
        nam->setRedirectPolicy(QNetworkRequest::NoLessSafeRedirectPolicy);

        QNetworkDiskCache* diskCache = new QNetworkDiskCache(nam);
        diskCache->setCacheDirectory(
            QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QLatin1String("/http/"));
        nam->setCache(diskCache);

        return nam;
    }();

    return nam;
}

QNetworkReply* HttpRequest::networkReply(
    const QNetworkRequest& request, HttpReply::Operation operation, const QByteArray& data)
{
    switch (operation)
    {
    case HttpReply::HeadOperation:
        return HttpReply::networkAccessManager()->head(request);
    case HttpReply::GetOperation:
        return HttpReply::networkAccessManager()->get(request);
    case HttpReply::PutOperation:
        return HttpReply::networkAccessManager()->put(request, data);
    case HttpReply::PostOperation:
        return HttpReply::networkAccessManager()->post(request, data);
    case HttpReply::DeleteOperation:
        return HttpReply::networkAccessManager()->deleteResource(request);
    default:
        throw std::runtime_error("Making request with invalid operation (value: " + std::to_string(operation));
    }
}

HttpReply* HttpRequest::request(
    const QUrl& url, HttpReply::Operation operation, const QByteArray& data)
{
    HttpReply* result = new HttpReply(std::move(m_headers));

    QNetworkRequest req(url);
    req.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    req.setAttribute(QNetworkRequest::CacheSaveControlAttribute, m_usingDiskCache);

    for (auto it = result->m_requestHeaders.cbegin(); it != result->m_requestHeaders.cend(); ++it)
        req.setRawHeader(it.key(), it.value());

    if (QNetworkReply* reply = networkReply(req, operation, data))
    {
        result->setParent(reply);
        QObject::connect(reply, &QNetworkReply::finished, result, [result] { emit result->finished(*result); });
    }

    return result;
}
