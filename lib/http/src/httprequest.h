#pragma once
#include <QNetworkAccessManager>

struct HttpRequest
{
    QByteArray body;
    QMap<QByteArray, QByteArray> headers;
    uint offset{};
    QNetworkAccessManager::Operation operation = QNetworkAccessManager::GetOperation;
    QUrl url;
};
