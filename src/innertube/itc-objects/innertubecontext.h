#pragma once
#include "innertubeclicktracking.h"
#include "innertubeclient.h"
#include "innertuberequestconfig.h"
#include "innertubeuserconfig.h"

struct InnertubeContext : public QObject
{
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
