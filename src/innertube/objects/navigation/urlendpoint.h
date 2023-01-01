#ifndef URLENDPOINT_H
#define URLENDPOINT_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class UrlEndpoint
    {
    public:
        bool noFollow;
        QString target;
        QString url;
        explicit UrlEndpoint(const QJsonValue& urlEndpoint)
            : noFollow(urlEndpoint["nofollow"].toBool()), target(urlEndpoint["target"].toString()), url(urlEndpoint["url"].toString()) {}
    };
}

#endif // URLENDPOINT_H
