#ifndef INNERTUBEREPLY_H
#define INNERTUBEREPLY_H
#include "endpoints/innertubeendpoints.h"
#include "innertubeexception.h"

class InnertubeReply : public QObject
{
    Q_OBJECT
signals:
    void exception(const InnertubeException&);
    void finished(InnertubeEndpoints::AccountMenu);
    void finished(InnertubeEndpoints::BrowseChannel);
    void finished(InnertubeEndpoints::BrowseExplore);
    void finished(InnertubeEndpoints::BrowseHistory);
    void finished(InnertubeEndpoints::BrowseHome);
    void finished(InnertubeEndpoints::BrowseLibrary);
    void finished(InnertubeEndpoints::BrowseStorefront);
    void finished(InnertubeEndpoints::BrowseSubscriptions);
    void finished(InnertubeEndpoints::BrowseTrending);
    void finished(InnertubeEndpoints::GetNotificationMenu);
    void finished(InnertubeEndpoints::ModifyChannelPreference);
    void finished(InnertubeEndpoints::Next);
    void finished(InnertubeEndpoints::Player);
    void finished(InnertubeEndpoints::Search);
    void finished(InnertubeEndpoints::Subscribe);
    void finished(InnertubeEndpoints::UnseenCount);
    void finished(InnertubeEndpoints::UpdatedMetadata);
};

#endif // INNERTUBEREPLY_H
