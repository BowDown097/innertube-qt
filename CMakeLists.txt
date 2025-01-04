cmake_minimum_required(VERSION 3.23)
project(innertube-qt VERSION 1.0 LANGUAGES C CXX)
add_library(innertube-qt)

set_target_properties(innertube-qt
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED true)

# Compilation options
option(INNERTUBE_GET_STS "Fetch the signature timestamp for playback to avoid rate-limiting for custom player implementations." OFF)
option(INNERTUBE_NO_WEBENGINE "Disable usage of Qt WebEngine. Please look at the wiki before doing this." OFF)

# Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

set(INNERTUBE_QT_VERSION_MAJOR ${QT_VERSION_MAJOR} CACHE STRING "Qt version to use, defaults to ${QT_VERSION_MAJOR}")

find_package(Qt${INNERTUBE_QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network)
find_package(Qt${INNERTUBE_QT_VERSION_MAJOR} OPTIONAL_COMPONENTS WebEngineWidgets)

target_sources(innertube-qt
    PRIVATE
        src/innertube.cpp
        src/jsonutil.cpp
        src/sslhttprequest.cpp
        src/innertube/endpoints/base/basebrowseendpoint.cpp
        src/innertube/endpoints/base/baseendpoint.cpp
        src/innertube/endpoints/browse/browsechannel.cpp
        src/innertube/endpoints/browse/browsehistory.cpp
        src/innertube/endpoints/browse/browsehome.cpp
        src/innertube/endpoints/browse/browsesubscriptions.cpp
        src/innertube/endpoints/browse/browsetrending.cpp
        src/innertube/endpoints/comment/performcommentaction.cpp
        src/innertube/endpoints/live_chat/getlivechat.cpp
        src/innertube/endpoints/live_chat/getlivechatreplay.cpp
        src/innertube/endpoints/live_chat/sendmessage.cpp
        src/innertube/endpoints/misc/accountmenu.cpp
        src/innertube/endpoints/misc/search.cpp
        src/innertube/endpoints/misc/unseencount.cpp
        src/innertube/endpoints/navigation/resolveurl.cpp
        src/innertube/endpoints/notification/getnotificationmenu.cpp
        src/innertube/endpoints/notification/modifychannelpreference.cpp
        src/innertube/endpoints/subscription/subscribe.cpp
        src/innertube/endpoints/subscription/unsubscribe.cpp
        src/innertube/endpoints/video/next.cpp
        src/innertube/endpoints/video/player.cpp
        src/innertube/endpoints/video/updatedmetadata.cpp
        src/innertube/itc-objects/innertubeauthstore.cpp
        src/innertube/itc-objects/innertubeclicktracking.cpp
        src/innertube/itc-objects/innertubeclient.cpp
        src/innertube/itc-objects/innertubeconfiginfo.cpp
        src/innertube/itc-objects/innertubecontext.cpp
        src/innertube/itc-objects/innertubeplaybackcontext.cpp
        src/innertube/itc-objects/innertuberequestconfig.cpp
        src/innertube/itc-objects/innertubeuserconfig.cpp
        src/innertube/objects/innertubestring.cpp
        src/innertube/objects/backstage/backstagepost.cpp
        src/innertube/objects/backstage/poll/poll.cpp
        src/innertube/objects/channel/aboutfullmetadata.cpp
        src/innertube/objects/channel/channel.cpp
        src/innertube/objects/channel/channelc4header.cpp
        src/innertube/objects/channel/channelmetadata.cpp
        src/innertube/objects/channel/microformatdata.cpp
        src/innertube/objects/channel/notificationpreferencebutton.cpp
        src/innertube/objects/images/responsiveimage.cpp
        src/innertube/objects/items/sortfiltersubmenu.cpp
        src/innertube/objects/items/chipcloud/chipcloud.cpp
        src/innertube/objects/items/emoji/emoji.cpp
        src/innertube/objects/items/emoji/picker/emojipicker.cpp
        src/innertube/objects/items/emoji/picker/emojipickercategory.cpp
        src/innertube/objects/items/menu/menu.cpp
        src/innertube/objects/live_chat/livechat.cpp
        src/innertube/objects/notification/notification.cpp
        src/innertube/objects/player/playervideodetails.cpp
        src/innertube/objects/player/streamingdata.cpp
        src/innertube/objects/shelves/reelshelf.cpp
        src/innertube/objects/video/basevideo.cpp
        src/innertube/objects/video/compactvideo.cpp
        src/innertube/objects/video/upcomingeventdata.cpp
        src/innertube/objects/video/video.cpp
        src/innertube/objects/video/watchnext/watchnextprimaryresults.cpp
        src/innertube/objects/video/watchnext/watchnextsecondaryresults.cpp
        src/innertube/objects/video/watchnext/comments/commentreplies.cpp
        src/innertube/objects/video/watchnext/comments/commentsheader.cpp
        src/innertube/objects/video/watchnext/primaryinfo/videoactions.cpp
        src/innertube/objects/video/watchnext/secondaryinfo/metadatarow.cpp
        src/innertube/objects/video/watchnext/secondaryinfo/metadatarowcontainer.cpp
        src/innertube/objects/video/watchnext/secondaryinfo/secondaryinfoowner.cpp
        src/innertube/objects/viewmodels/contentmetadataviewmodel.cpp
        src/innertube/objects/viewmodels/lockupviewmodel.cpp
        src/innertube/objects/viewmodels/subscribebuttonviewmodel.cpp
        src/innertube/objects/viewmodels/thumbnailhoveroverlaytoggleactionsviewmodel.cpp
        src/innertube/objects/viewmodels/thumbnailoverlaybadgeviewmodel.cpp
        src/innertube/objects/viewmodels/thumbnailviewmodel.cpp
        src/innertube/responses/video/nextcontinuationdata.cpp
        src/protobuf/protobufcompiler.cpp
    PUBLIC
        FILE_SET HEADERS FILES
            src/innertube.h
            src/jsonutil.h
            src/sslhttprequest.h
            src/innertube/innertubeexception.h
            src/innertube/innertubereply.h
            src/innertube/endpoints/innertubeendpoints.h
            src/innertube/endpoints/base/basebrowseendpoint.h
            src/innertube/endpoints/base/baseendpoint.h
            src/innertube/endpoints/browse/browsechannel.h
            src/innertube/endpoints/browse/browsehistory.h
            src/innertube/endpoints/browse/browsehome.h
            src/innertube/endpoints/browse/browsesubscriptions.h
            src/innertube/endpoints/browse/browsetrending.h
            src/innertube/endpoints/comment/performcommentaction.h
            src/innertube/endpoints/like/baselikeendpoint.h
            src/innertube/endpoints/like/dislike.h
            src/innertube/endpoints/like/like.h
            src/innertube/endpoints/like/removelike.h
            src/innertube/endpoints/live_chat/getlivechat.h
            src/innertube/endpoints/live_chat/getlivechatreplay.h
            src/innertube/endpoints/live_chat/sendmessage.h
            src/innertube/endpoints/misc/accountmenu.h
            src/innertube/endpoints/misc/search.h
            src/innertube/endpoints/misc/unseencount.h
            src/innertube/endpoints/navigation/resolveurl.h
            src/innertube/endpoints/notification/getnotificationmenu.h
            src/innertube/endpoints/notification/modifychannelpreference.h
            src/innertube/endpoints/subscription/subscribe.h
            src/innertube/endpoints/subscription/unsubscribe.h
            src/innertube/endpoints/video/next.h
            src/innertube/endpoints/video/player.h
            src/innertube/endpoints/video/updatedmetadata.h
            src/innertube/itc-objects/innertubeauthstore.h
            src/innertube/itc-objects/innertubeclicktracking.h
            src/innertube/itc-objects/innertubeclient.h
            src/innertube/itc-objects/innertubeconfiginfo.h
            src/innertube/itc-objects/innertubecontext.h
            src/innertube/itc-objects/innertubeplaybackcontext.h
            src/innertube/itc-objects/innertuberequestconfig.h
            src/innertube/itc-objects/innertubeuserconfig.h
            src/innertube/objects/colorpalette.h
            src/innertube/objects/compactlink.h
            src/innertube/objects/dynamictext.h
            src/innertube/objects/entitymutation.h
            src/innertube/objects/innertubestring.h
            src/innertube/objects/lottiedata.h
            src/innertube/objects/account_menu/activeaccountheader.h
            src/innertube/objects/ad/adactiveview.h
            src/innertube/objects/ad/adlayoutmetadata.h
            src/innertube/objects/ad/adslot.h
            src/innertube/objects/ad/adslotmetadata.h
            src/innertube/objects/ad/displayad.h
            src/innertube/objects/ad/infeedadlayout.h
            src/innertube/objects/backstage/backstageimage.h
            src/innertube/objects/backstage/backstagepost.h
            src/innertube/objects/backstage/poll/poll.h
            src/innertube/objects/backstage/poll/pollchoice.h
            src/innertube/objects/channel/aboutfullmetadata.h
            src/innertube/objects/channel/channel.h
            src/innertube/objects/channel/channelc4header.h
            src/innertube/objects/channel/channelheaderlink.h
            src/innertube/objects/channel/channelmetadata.h
            src/innertube/objects/channel/channelpageheader.h
            src/innertube/objects/channel/metadatabadge.h
            src/innertube/objects/channel/microformatdata.h
            src/innertube/objects/channel/notificationpreferencebutton.h
            src/innertube/objects/channel/notificationstate.h
            src/innertube/objects/channel/subscribebutton.h
            src/innertube/objects/images/genericthumbnail.h
            src/innertube/objects/images/imagewithaccessibility.h
            src/innertube/objects/images/imagewithcolorpalette.h
            src/innertube/objects/images/movingthumbnail.h
            src/innertube/objects/images/responsiveimage.h
            src/innertube/objects/items/button.h
            src/innertube/objects/items/horizontallist.h
            src/innertube/objects/items/listbase.h
            src/innertube/objects/items/sortfiltersubmenu.h
            src/innertube/objects/items/togglebutton.h
            src/innertube/objects/items/verticallist.h
            src/innertube/objects/items/chipcloud/chipcloud.h
            src/innertube/objects/items/chipcloud/chipcloudchip.h
            src/innertube/objects/items/emoji/emoji.h
            src/innertube/objects/items/emoji/picker/emojipicker.h
            src/innertube/objects/items/emoji/picker/emojipickercategory.h
            src/innertube/objects/items/emoji/picker/emojipickercategorybutton.h
            src/innertube/objects/items/menu/menu.h
            src/innertube/objects/items/menu/menuflexibleitem.h
            src/innertube/objects/items/menu/menuserviceitem.h
            src/innertube/objects/live_chat/livechat.h
            src/innertube/objects/notification/notification.h
            src/innertube/objects/player/captiontrack.h
            src/innertube/objects/player/playbacktracking.h
            src/innertube/objects/player/playervideodetails.h
            src/innertube/objects/player/streamingdata.h
            src/innertube/objects/player/streamingformat.h
            src/innertube/objects/shelves/reelshelf.h
            src/innertube/objects/shelves/richshelf.h
            src/innertube/objects/shelves/shelf.h
            src/innertube/objects/shelves/videoshelves.h
            src/innertube/objects/video/basevideo.h
            src/innertube/objects/video/channelthumbnailwithlink.h
            src/innertube/objects/video/compactvideo.h
            src/innertube/objects/video/metadatasnippet.h
            src/innertube/objects/video/reel.h
            src/innertube/objects/video/upcomingeventdata.h
            src/innertube/objects/video/video.h
            src/innertube/objects/video/videodisplaybuttongroup.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlayendorsement.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlayinlineunplayable.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlayloadingpreview.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlaynowplaying.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlayresumeplayback.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlaytimestatus.h
            src/innertube/objects/video/thumbnail_overlays/thumbnailoverlaytogglebutton.h
            src/innertube/objects/video/watchnext/clarification.h
            src/innertube/objects/video/watchnext/relatedchipcloud.h
            src/innertube/objects/video/watchnext/twocolumnwatchnextresults.h
            src/innertube/objects/video/watchnext/watchnextprimaryresults.h
            src/innertube/objects/video/watchnext/watchnextsecondaryresults.h
            src/innertube/objects/video/watchnext/comments/authorcommentbadge.h
            src/innertube/objects/video/watchnext/comments/comment.h
            src/innertube/objects/video/watchnext/comments/commentactionbuttons.h
            src/innertube/objects/video/watchnext/comments/commentreplies.h
            src/innertube/objects/video/watchnext/comments/commentsheader.h
            src/innertube/objects/video/watchnext/comments/commentsimplebox.h
            src/innertube/objects/video/watchnext/comments/commentthread.h
            src/innertube/objects/video/watchnext/comments/pinnedcommentbadge.h
            src/innertube/objects/video/watchnext/comments/entrypoint/commentsentrypointheader.h
            src/innertube/objects/video/watchnext/comments/entrypoint/commentsentrypointteaser.h
            src/innertube/objects/video/watchnext/primaryinfo/videoactions.h
            src/innertube/objects/video/watchnext/primaryinfo/videoprimaryinfo.h
            src/innertube/objects/video/watchnext/primaryinfo/viewcount.h
            src/innertube/objects/video/watchnext/primaryinfo/likedislike/dislikebuttonviewmodel.h
            src/innertube/objects/video/watchnext/primaryinfo/likedislike/dynamiclikecountupdatedata.h
            src/innertube/objects/video/watchnext/primaryinfo/likedislike/likebuttonviewmodel.h
            src/innertube/objects/video/watchnext/primaryinfo/likedislike/likecountentity.h
            src/innertube/objects/video/watchnext/primaryinfo/likedislike/likedislikeviewmodel.h
            src/innertube/objects/video/watchnext/secondaryinfo/metadatarow.h
            src/innertube/objects/video/watchnext/secondaryinfo/metadatarowcontainer.h
            src/innertube/objects/video/watchnext/secondaryinfo/secondaryinfoowner.h
            src/innertube/objects/video/watchnext/secondaryinfo/videosecondaryinfo.h
            src/innertube/objects/viewmodels/avatarviewmodel.h
            src/innertube/objects/viewmodels/buttonviewmodel.h
            src/innertube/objects/viewmodels/contentmetadataviewmodel.h
            src/innertube/objects/viewmodels/decoratedavatarviewmodel.h
            src/innertube/objects/viewmodels/dynamictextviewmodel.h
            src/innertube/objects/viewmodels/flexibleactionsviewmodel.h
            src/innertube/objects/viewmodels/imagebannerviewmodel.h
            src/innertube/objects/viewmodels/lockupmetadataviewmodel.h
            src/innertube/objects/viewmodels/lockupviewmodel.h
            src/innertube/objects/viewmodels/shortslockupviewmodel.h
            src/innertube/objects/viewmodels/subscribebuttoncontent.h
            src/innertube/objects/viewmodels/subscribebuttonviewmodel.h
            src/innertube/objects/viewmodels/thumbnailbadgeviewmodel.h
            src/innertube/objects/viewmodels/thumbnailhoveroverlaytoggleactionsviewmodel.h
            src/innertube/objects/viewmodels/thumbnailoverlaybadgeviewmodel.h
            src/innertube/objects/viewmodels/thumbnailviewmodel.h
            src/innertube/objects/viewmodels/togglebuttonviewmodel.h
            src/innertube/responses/browse/channelresponse.h
            src/innertube/responses/browse/historyresponse.h
            src/innertube/responses/browse/homeresponse.h
            src/innertube/responses/browse/subscriptionsresponse.h
            src/innertube/responses/browse/trendingresponse.h
            src/innertube/responses/comment/commentactionresponse.h
            src/innertube/responses/misc/accountmenuresponse.h
            src/innertube/responses/misc/searchresponse.h
            src/innertube/responses/notification/notificationmenuresponse.h
            src/innertube/responses/video/nextcontinuationdata.h
            src/innertube/responses/video/nextresponse.h
            src/innertube/responses/video/playerresponse.h
            src/innertube/responses/video/updatedmetadataresponse.h
            src/protobuf/protobufcompiler.h)

# Define options in preprocessor
if(INNERTUBE_GET_STS)
    target_compile_definitions(innertube-qt PUBLIC INNERTUBE_GET_STS)
endif()

if(INNERTUBE_NO_WEBENGINE)
    target_compile_definitions(innertube-qt PUBLIC INNERTUBE_NO_WEBENGINE)
endif()

# expected-lite
find_package(expected-lite QUIET)
if(NOT expected-lite_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        expected-lite
        GIT_REPOSITORY https://github.com/martinmoene/expected-lite.git
        GIT_TAG v0.8.0)
    FetchContent_MakeAvailable(expected-lite)
endif()

# Include directories, libraries
add_subdirectory(lib/http)
target_include_directories(innertube-qt PUBLIC src lib/http/src lib/verdigris/src)
target_link_libraries(innertube-qt PUBLIC http nonstd::expected-lite Qt::Core Qt::Gui Qt::Network)

## Optional
if(NOT INNERTUBE_NO_WEBENGINE)
    target_link_libraries(innertube-qt PUBLIC Qt::WebEngineWidgets)
endif()
