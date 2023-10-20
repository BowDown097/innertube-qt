#include "innertube.h"

void InnerTube::like(const QJsonValue& endpoint, bool liking)
{
    QThreadPool::globalInstance()->start([this, endpoint, liking] {
        if (endpoint["removeLikeParams"].isObject())
        {
            InnertubeEndpoints::Like(
                endpoint["target"]["videoId"].toString(),
                endpoint["removeLikeParams"].toString(),
                liking, true, m_context, m_authStore
            );
        }
        else
        {
            InnertubeEndpoints::Like(
                endpoint["target"]["videoId"].toString(),
                liking ? endpoint["likeParams"].toString() : endpoint["dislikeParams"].toString(),
                liking, false, m_context, m_authStore
            );
        }
    });
}

void InnerTube::sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params)
{
    QThreadPool::globalInstance()->start([this, textSegments, clientMessageId, params] {
        InnertubeEndpoints::SendMessage(textSegments, m_context, m_authStore, clientMessageId, params);
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
    QList<QString> channelIds;
    const QJsonArray channelIdsJson = endpoint["channelIds"].toArray();
    for (const QJsonValue& v : channelIdsJson)
        channelIds.append(v.toString());
    InnertubeEndpoints::Subscribe(channelIds, endpoint["params"].toString(), subscribing, m_context, m_authStore);
}

void InnerTube::subscribeBlocking(const QStringList& channelIds, bool subscribing)
{
    subscribeBlocking(QJsonObject { { "channelIds", QJsonArray::fromStringList(channelIds) } }, subscribing);
}
