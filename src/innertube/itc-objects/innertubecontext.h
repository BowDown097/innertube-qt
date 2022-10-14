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
    explicit InnertubeContext(const InnertubeClient& ic, const InnertubeClickTracking& ict = InnertubeClickTracking(),
                              const InnertubeRequestConfig& irc = InnertubeRequestConfig(), const InnertubeUserConfig& iuc = InnertubeUserConfig())
        : clickTracking(ict), client(ic), request(irc), user(iuc) {}
    QJsonObject toJson() const;
};

#endif // INNERTUBECONTEXT_H
