#ifndef INNERTUBEREPLY_H
#define INNERTUBEREPLY_H
#include <wobjectimpl.h>
#include "endpoints/innertubeendpoints.h"
#include "innertubeexception.h"

template<class T, class... U>
static constexpr bool innertube_is_any_v = std::disjunction_v<std::is_same<T, U>...>;

/**
 * @brief An @ref InnertubeEndpoints::BaseEndpoint "Innertube endpoint" that returns data.
 * @details The @ref InnertubeEndpoints::Like "Like", @ref InnertubeEndpoints::SendMessage "SendMessage",
 * and @ref InnertubeEndpoints::Subscribe "Subscribe" endpoints cannot be used here.<br>
 * Use their respective methods in the InnerTube class as opposed to the
 * @ref InnerTube::get "get" and @ref InnerTube::getBlocking "getBlocking" methods.
 */
template<class C>
concept EndpointWithData = requires(C c)
{
    []<InnertubeEndpoints::CompTimeStr X>(InnertubeEndpoints::BaseEndpoint<X>&){}(c);
} && !innertube_is_any_v<C, InnertubeEndpoints::Like, InnertubeEndpoints::SendMessage, InnertubeEndpoints::Subscribe>;

/**
 * @brief An object that emits signals related to Innertube requests. Used by @ref InnerTube::get and @ref InnerTube::getRaw.
 */
template<EndpointWithData E>
class InnertubeReply : public QObject
{
    W_OBJECT(InnertubeReply)
public /* signals */:
    void exception(const InnertubeException& ex) W_SIGNAL(exception, ex)
    void finished(const E& endpoint) W_SIGNAL(finished, endpoint)
    void finishedRaw(const QJsonValue& value) W_SIGNAL(finishedRaw, value)
};

W_OBJECT_IMPL_INLINE(InnertubeReply<E>, template<EndpointWithData E>)

#endif // INNERTUBEREPLY_H
