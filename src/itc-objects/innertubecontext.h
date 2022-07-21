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

    InnertubeContext() {}
    InnertubeContext(const InnertubeClient& ic, const InnertubeClickTracking& ict = InnertubeClickTracking(),
                     const InnertubeRequestConfig& irc = InnertubeRequestConfig(), const InnertubeUserConfig& iuc = InnertubeUserConfig())
        : clickTracking(ict), client(ic), request(irc), user(iuc) {}

    QJsonObject toJson() const
    {
        return {
            { "clickTracking", clickTracking.toJson() },
            { "client", client.toJson() },
            { "request", request.toJson() },
            { "user", user.toJson() }
        };
    }
};

#endif // INNERTUBECONTEXT_H
