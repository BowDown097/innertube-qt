#ifndef INNERTUBECONTEXT_H
#define INNERTUBECONTEXT_H
#include "innertubeclicktracking.h"
#include "innertubeclient.h"
#include "innertuberequestconfig.h"
#include "innertubeuserconfig.h"

class InnertubeContext : public QObject
{
public:
    InnertubeClickTracking clickTracking;
    InnertubeClient client;
    InnertubeRequestConfig request;
    InnertubeUserConfig user;

    explicit InnertubeContext(QObject* parent = nullptr) : QObject(parent) {}
    explicit InnertubeContext(const InnertubeClient& client, const InnertubeClickTracking& clickTracking = InnertubeClickTracking(),
                              const InnertubeRequestConfig& request = InnertubeRequestConfig(),
                              const InnertubeUserConfig& user = InnertubeUserConfig(),
                              QObject* parent = nullptr)
        : clickTracking(clickTracking), client(client), request(request), user(user), QObject(parent) {}
    QJsonObject toJson() const;
};

#endif // INNERTUBECONTEXT_H
