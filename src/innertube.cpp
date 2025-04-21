#include "innertube.h"
#include "jsonutil.h"

InnerTube* InnerTube::instance()
{
    std::call_once(m_onceFlag, [] { m_instance = new InnerTube; });
    return m_instance;
}

void InnerTube::addContext(QJsonObject& body, const QString& browseId)
{
    // merge unique properties from context, so that properties can be overriden by the user
    if (body["context"].isObject())
    {
        QJsonObject contextObj = m_context->toJson();
        const QJsonObject bodyContext = body["context"].toObject();
        JsonUtil::deepMerge(contextObj, bodyContext);
        body["context"] = contextObj;
    }
    else
    {
        body.insert("context", m_context->toJson());
    }

    if (!browseId.isEmpty())
        body.insert("browseId", browseId);
}

void InnerTube::like(const QJsonValue& endpoint, bool liking)
{
    if (endpoint["removeLikeParams"].isString())
    {
        InnerTube::getPlain<InnertubeEndpoints::RemoveLike>(
            endpoint["target"]["videoId"].toString(), endpoint["removeLikeParams"].toString());
    }
    else if (liking)
    {
        InnerTube::getPlain<InnertubeEndpoints::Like>(
            endpoint["target"]["videoId"].toString(), endpoint["likeParams"].toString());
    }
    else
    {
        InnerTube::getPlain<InnertubeEndpoints::Dislike>(
            endpoint["target"]["videoId"].toString(), endpoint["likeParams"].toString());
    }
}

void InnerTube::sendMessage(const QJsonArray& textSegments, const QString& clientMessageId, const QString& params)
{
    InnerTube::getPlain<InnertubeEndpoints::SendMessage>(textSegments, clientMessageId, params);
}

void InnerTube::sendMessage(const QString& message, const QString& clientMessageId, const QString& params)
{
    InnerTube::getPlain<InnertubeEndpoints::SendMessage>(message, clientMessageId, params);
}

void InnerTube::subscribe(const QJsonValue& endpoint, bool subscribing)
{
    subscribeImpl(endpoint, subscribing, false);
}

void InnerTube::subscribe(const QStringList& channelIds, bool subscribing)
{
    subscribe(QJsonObject { { "channelIds", QJsonArray::fromStringList(channelIds) } }, subscribing);
}

void InnerTube::subscribeBlocking(const QJsonValue& endpoint, bool subscribing)
{
    subscribeImpl(endpoint, subscribing, true);
}

void InnerTube::subscribeBlocking(const QStringList& channelIds, bool subscribing)
{
    subscribeBlocking(QJsonObject { { "channelIds", QJsonArray::fromStringList(channelIds) } }, subscribing);
}

void InnerTube::subscribeImpl(const QJsonValue& endpoint, bool subscribing, bool blocking)
{
    QStringList channelIds;
    const QJsonArray channelIdsJson = endpoint["channelIds"].toArray();
    for (const QJsonValue& v : channelIdsJson)
        channelIds.append(v.toString());

    if (subscribing)
    {
        if (blocking)
            InnerTube::getPlainBlocking<InnertubeEndpoints::Subscribe>(channelIds, endpoint["params"].toString());
        else
            InnerTube::getPlain<InnertubeEndpoints::Subscribe>(channelIds, endpoint["params"].toString());
    }
    else
    {
        if (blocking)
            InnerTube::getPlainBlocking<InnertubeEndpoints::Unsubscribe>(channelIds, endpoint["params"].toString());
        else
            InnerTube::getPlain<InnertubeEndpoints::Unsubscribe>(channelIds, endpoint["params"].toString());
    }
}
