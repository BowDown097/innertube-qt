#pragma once
#include <wobjectimpl.h>
#include "endpoints/innertubeendpoints.h"
#include "innertubeexception.h"

template<class T, class... U>
concept innertube_is_any_v = std::disjunction_v<std::is_same<T, U>...>;

template<class Derived, template<auto...> class Base>
concept innertube_derived_from_templated = requires(Derived& t) { []<auto... X>(Base<X...>&){}(t); };

/**
 * @brief An @ref InnertubeEndpoints::BaseEndpoint "Innertube endpoint" that returns data.
 * @details The @ref InnertubeEndpoints::SendMessage "SendMessage" endpoint
 * and any of the like or subscribe endpoints cannot be used here.<br>
 * Use their respective methods in the InnerTube class as opposed to the
 * @ref InnerTube::get "get" and @ref InnerTube::getBlocking "getBlocking" methods.
 */
template<class C>
concept EndpointWithData =
    innertube_derived_from_templated<C, InnertubeEndpoints::BaseEndpoint> &&
    !innertube_derived_from_templated<C, InnertubeEndpoints::BaseLikeEndpoint> &&
    !innertube_is_any_v<C, InnertubeEndpoints::SendMessage, InnertubeEndpoints::Subscribe, InnertubeEndpoints::Unsubscribe>;

/**
 * @brief An object that emits signals related to Innertube requests. Used by @ref InnerTube::get and @ref InnerTube::getRaw.
 */
template<typename T> requires (EndpointWithData<T> || std::same_as<T, void>)
class InnertubeReply : public QObject
{
    W_OBJECT(InnertubeReply)
public /* signals */:
    void exception(const InnertubeException& ex) W_SIGNAL(exception, ex)
    void finished(const T& endpoint) W_SIGNAL(finished, endpoint)
    void finishedRaw(const QJsonValue& value) W_SIGNAL(finishedRaw, value)
};

template<>
class InnertubeReply<void> : public QObject
{
    W_OBJECT(InnertubeReply<void>)
public /* signals */:
    void finished() W_SIGNAL(finished)
};

W_OBJECT_IMPL_INLINE(InnertubeReply<T>, template<typename T> requires (EndpointWithData<T> || std::same_as<T, void>))
W_OBJECT_IMPL_INLINE(InnertubeReply<void>)
