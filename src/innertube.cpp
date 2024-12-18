#include "innertube.h"

InnerTube* InnerTube::instance()
{
    std::call_once(m_onceFlag, [] { m_instance = new InnerTube; });
    return m_instance;
}

void InnerTube::like(const QJsonValue& endpoint, bool liking)
{
    QThreadPool::globalInstance()->start([this, endpoint, liking] {
        if (endpoint["removeLikeParams"].isString())
            InnertubeEndpoints::RemoveLike(m_context, m_authStore, endpoint["target"]["videoId"].toString(), endpoint["removeLikeParams"].toString());
        else if (liking)
            InnertubeEndpoints::Like(m_context, m_authStore, endpoint["target"]["videoId"].toString(), endpoint["likeParams"].toString());
        else if (!liking)
            InnertubeEndpoints::Dislike(m_context, m_authStore, endpoint["target"]["videoId"].toString(), endpoint["likeParams"].toString());
    });
}

void InnerTube::sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params)
{
    QThreadPool::globalInstance()->start([this, textSegments, clientMessageId, params] {
        InnertubeEndpoints::SendMessage(textSegments, m_context, m_authStore, clientMessageId, params);
    });
}

void InnerTube::sendMessage(const QString& message, const QString& clientMessageId, const QString& params)
{
    QThreadPool::globalInstance()->start([this, message, clientMessageId, params] {
        InnertubeEndpoints::SendMessage(message, m_context, m_authStore, clientMessageId, params);
    });
}

void InnerTube::subscribe(const QJsonValue& endpoint, bool subscribing)
{
    QThreadPool::globalInstance()->start([this, endpoint, subscribing] { subscribeBlocking(endpoint, subscribing); });
}

void InnerTube::subscribe(const QStringList& channelIds, bool subscribing)
{
    QThreadPool::globalInstance()->start([this, channelIds, subscribing] { subscribeBlocking(channelIds, subscribing); });
}

void InnerTube::subscribeBlocking(const QJsonValue& endpoint, bool subscribing)
{
    QStringList channelIds;
    const QJsonArray channelIdsJson = endpoint["channelIds"].toArray();
    for (const QJsonValue& v : channelIdsJson)
        channelIds.append(v.toString());

    if (subscribing)
        InnertubeEndpoints::Subscribe(m_context, m_authStore, channelIds, endpoint["params"].toString());
    else
        InnertubeEndpoints::Unsubscribe(m_context, m_authStore, channelIds, endpoint["params"].toString());
}

void InnerTube::subscribeBlocking(const QStringList& channelIds, bool subscribing)
{
    subscribeBlocking(QJsonObject { { "channelIds", QJsonArray::fromStringList(channelIds) } }, subscribing);
}
