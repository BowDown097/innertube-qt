#ifndef NAVIGATIONBROWSEENDPOINT_H
#define NAVIGATIONBROWSEENDPOINT_H
#include <QJsonValue>

namespace InnertubeObjects
{
    class NavigationBrowseEndpoint
    {
    public:
        QString browseId;
        QString canonicalBaseUrl;
        QString params;
        explicit NavigationBrowseEndpoint(const QJsonValue& browseEndpoint)
            : browseId(browseEndpoint["browseId"].toString()),
              canonicalBaseUrl(browseEndpoint["canonicalBaseUrl"].toString()),
              params(browseEndpoint["params"].toString()) {}
    };
}

#endif // NAVIGATIONBROWSEENDPOINT_H
