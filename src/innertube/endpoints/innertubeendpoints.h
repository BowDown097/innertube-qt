#ifndef INNERTUBEENDPOINTS_H
#define INNERTUBEENDPOINTS_H

// This header just serves to include every supported endpoint. Nothing more!
#include "browse/browsechannel.h"
#include "browse/browsehistory.h"
#include "browse/browsehome.h"
#include "browse/browsesubscriptions.h"
#include "browse/browsetrending.h"
#include "like/dislike.h"
#include "like/like.h"
#include "like/removelike.h"
#include "live_chat/getlivechat.h"
#include "live_chat/getlivechatreplay.h"
#include "live_chat/sendmessage.h"
#include "misc/accountmenu.h"
#include "misc/search.h"
#include "misc/unseencount.h"
#include "notification/getnotificationmenu.h"
#include "notification/modifychannelpreference.h"
#include "subscription/subscribe.h"
#include "subscription/unsubscribe.h"
#include "video/next.h"
#include "video/player.h"
#include "video/updatedmetadata.h"
#include <wobjectdefs.h>

W_REGISTER_ARGTYPE(InnertubeEndpoints::AccountMenu)
W_REGISTER_ARGTYPE(InnertubeEndpoints::BrowseChannel)
W_REGISTER_ARGTYPE(InnertubeEndpoints::BrowseHistory)
W_REGISTER_ARGTYPE(InnertubeEndpoints::BrowseHome)
W_REGISTER_ARGTYPE(InnertubeEndpoints::BrowseSubscriptions)
W_REGISTER_ARGTYPE(InnertubeEndpoints::BrowseTrending)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Dislike)
W_REGISTER_ARGTYPE(InnertubeEndpoints::GetLiveChat)
W_REGISTER_ARGTYPE(InnertubeEndpoints::GetLiveChatReplay)
W_REGISTER_ARGTYPE(InnertubeEndpoints::GetNotificationMenu)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Like)
W_REGISTER_ARGTYPE(InnertubeEndpoints::ModifyChannelPreference)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Next)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Player)
W_REGISTER_ARGTYPE(InnertubeEndpoints::RemoveLike)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Search)
W_REGISTER_ARGTYPE(InnertubeEndpoints::SendMessage)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Subscribe)
W_REGISTER_ARGTYPE(InnertubeEndpoints::UnseenCount)
W_REGISTER_ARGTYPE(InnertubeEndpoints::Unsubscribe)
W_REGISTER_ARGTYPE(InnertubeEndpoints::UpdatedMetadata)

#endif // INNERTUBEENDPOINTS_H
