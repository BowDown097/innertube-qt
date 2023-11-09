#ifndef INNERTUBEREPLY_H
#define INNERTUBEREPLY_H
#include "endpoints/innertubeendpoints.h"
#include "innertubeexception.h"

/**
 * @brief An object that emits signals related to Innertube requests. Used by @ref InnerTube::get.
 */
class InnertubeReply : public QObject
{
    Q_OBJECT
signals:
    void exception(const InnertubeException&);
    void finished(const InnertubeEndpoints::AccountMenu&);
    void finished(const InnertubeEndpoints::BrowseChannel&);
    void finished(const InnertubeEndpoints::BrowseHistory&);
    void finished(const InnertubeEndpoints::BrowseHome&);
    void finished(const InnertubeEndpoints::BrowseSubscriptions&);
    void finished(const InnertubeEndpoints::BrowseTrending&);
    void finished(const InnertubeEndpoints::GetLiveChat&);
    void finished(const InnertubeEndpoints::GetLiveChatReplay&);
    void finished(const InnertubeEndpoints::GetNotificationMenu&);
    void finished(const InnertubeEndpoints::ModifyChannelPreference&);
    void finished(const InnertubeEndpoints::Next&);
    void finished(const InnertubeEndpoints::Player&);
    void finished(const InnertubeEndpoints::Search&);
    void finished(const InnertubeEndpoints::SendMessage&);
    void finished(const InnertubeEndpoints::Subscribe&);
    void finished(const InnertubeEndpoints::UnseenCount&);
    void finished(const InnertubeEndpoints::UpdatedMetadata&);
};

#endif // INNERTUBEREPLY_H
