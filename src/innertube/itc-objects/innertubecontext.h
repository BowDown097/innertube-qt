#ifndef INNERTUBECONTEXT_H
#define INNERTUBECONTEXT_H
#include "innertubeclicktracking.h"
#include "innertubeclient.h"
#include "innertuberequestconfig.h"
#include "innertubeuserconfig.h"

class InnertubeContext
{
public:
    InnertubeClickTracking clickTracking;
    InnertubeClient client;
    InnertubeRequestConfig request;
    InnertubeUserConfig user;

    InnertubeContext() = default;
    explicit InnertubeContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                              const InnertubeRequestConfig& request = InnertubeRequestConfig(),
                              const InnertubeUserConfig& user = InnertubeUserConfig())
        : clickTracking(clickTracking), client(client), request(request), user(user) {}
    QJsonObject toJson() const;
};

#endif // INNERTUBECONTEXT_H
