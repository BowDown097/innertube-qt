#ifndef NAVIGATIONENDPOINT_H
#define NAVIGATIONENDPOINT_H
#include "commandmetadata.h"
#include "navigationbrowseendpoint.h"
#include "urlendpoint.h"

namespace InnertubeObjects
{
    class NavigationEndpoint
    {
    public:
        NavigationBrowseEndpoint browseEndpoint;
        CommandMetadata commandMetadata;
        UrlEndpoint urlEndpoint;
        explicit NavigationEndpoint(const QJsonValue& endpoint)
            : browseEndpoint(endpoint["browseEndpoint"]), commandMetadata(endpoint["commandMetadata"]), urlEndpoint(endpoint["urlEndpoint"]) {}
    };
}

#endif // NAVIGATIONENDPOINT_H
