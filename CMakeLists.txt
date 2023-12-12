cmake_minimum_required(VERSION 3.16)
project(innertube-qt VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(GNUInstallDirs)

# Compiler flags
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

# Compilation options
option(INNERTUBE_GET_STS "Fetch the signature timestamp for playback to avoid rate-limiting for custom player implementations." OFF)
option(INNERTUBE_NO_WEBENGINE "Disable usage of Qt WebEngine. Please look at the wiki before doing this." OFF)

# Qt packages
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)

set(INNERTUBE_QT_VERSION_MAJOR ${QT_VERSION_MAJOR} CACHE STRING "Qt version to use, defaults to ${QT_VERSION_MAJOR}")

find_package(Qt${INNERTUBE_QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network)
find_package(Qt${INNERTUBE_QT_VERSION_MAJOR} OPTIONAL_COMPONENTS WebEngineWidgets)

add_library(innertube-qt
    src/innertube.cpp src/innertube.h
    src/jsonutil.cpp src/jsonutil.h
    src/sslhttprequest.cpp src/sslhttprequest.h
    src/innertube/innertubeexception.h
    src/innertube/innertubereply.h
    src/innertube/endpoints/base/basebrowseendpoint.cpp src/innertube/endpoints/base/basebrowseendpoint.h
    src/innertube/endpoints/base/baseendpoint.h
    src/innertube/endpoints/browse/browsechannel.cpp src/innertube/endpoints/browse/browsechannel.h
    src/innertube/endpoints/browse/browsehistory.cpp src/innertube/endpoints/browse/browsehistory.h
    src/innertube/endpoints/browse/browsehome.cpp src/innertube/endpoints/browse/browsehome.h
    src/innertube/endpoints/browse/browsesubscriptions.cpp src/innertube/endpoints/browse/browsesubscriptions.h
    src/innertube/endpoints/browse/browsetrending.cpp src/innertube/endpoints/browse/browsetrending.h
    src/innertube/endpoints/comment/performcommentaction.cpp src/innertube/endpoints/comment/performcommentaction.h
    src/innertube/endpoints/innertubeendpoints.h
    src/innertube/endpoints/like/baselikeendpoint.h
    src/innertube/endpoints/like/dislike.h
    src/innertube/endpoints/like/like.h
    src/innertube/endpoints/like/removelike.h
    src/innertube/endpoints/live_chat/getlivechat.cpp src/innertube/endpoints/live_chat/getlivechat.h
    src/innertube/endpoints/live_chat/getlivechatreplay.cpp src/innertube/endpoints/live_chat/getlivechatreplay.h
    src/innertube/endpoints/live_chat/sendmessage.cpp src/innertube/endpoints/live_chat/sendmessage.h
    src/innertube/endpoints/misc/accountmenu.cpp src/innertube/endpoints/misc/accountmenu.h
    src/innertube/endpoints/misc/search.cpp src/innertube/endpoints/misc/search.h
    src/innertube/endpoints/misc/unseencount.cpp src/innertube/endpoints/misc/unseencount.h
    src/innertube/endpoints/notification/getnotificationmenu.cpp src/innertube/endpoints/notification/getnotificationmenu.h
    src/innertube/endpoints/notification/modifychannelpreference.cpp src/innertube/endpoints/notification/modifychannelpreference.h
    src/innertube/endpoints/subscription/subscribe.cpp src/innertube/endpoints/subscription/subscribe.h
    src/innertube/endpoints/subscription/unsubscribe.cpp src/innertube/endpoints/subscription/unsubscribe.h
    src/innertube/endpoints/video/next.cpp src/innertube/endpoints/video/next.h
    src/innertube/endpoints/video/player.cpp src/innertube/endpoints/video/player.h
    src/innertube/endpoints/video/updatedmetadata.cpp src/innertube/endpoints/video/updatedmetadata.h
    src/innertube/itc-objects/innertubeauthstore.cpp src/innertube/itc-objects/innertubeauthstore.h
    src/innertube/itc-objects/innertubeclicktracking.h
    src/innertube/itc-objects/innertubeclient.cpp src/innertube/itc-objects/innertubeclient.h
    src/innertube/itc-objects/innertubeconfiginfo.h
    src/innertube/itc-objects/innertubecontext.cpp src/innertube/itc-objects/innertubecontext.h
    src/innertube/itc-objects/innertubeplaybackcontext.cpp src/innertube/itc-objects/innertubeplaybackcontext.h
    src/innertube/itc-objects/innertuberequestconfig.h
    src/innertube/itc-objects/innertubeuserconfig.h
    src/innertube/objects/compactlink.h
    src/innertube/objects/genericthumbnail.h
    src/innertube/objects/innertubestring.cpp src/innertube/objects/innertubestring.h
    src/innertube/objects/responsiveimage.h src/innertube/objects/responsiveimage.cpp
    src/innertube/objects/account_menu/activeaccountheader.h
    src/innertube/objects/backstage/backstageimage.h
    src/innertube/objects/backstage/backstagepost.cpp src/innertube/objects/backstage/backstagepost.h
    src/innertube/objects/backstage/commentactionbuttons.h
    src/innertube/objects/backstage/poll/poll.cpp src/innertube/objects/backstage/poll/poll.h
    src/innertube/objects/backstage/poll/pollchoice.h
    src/innertube/objects/channel/aboutfullmetadata.cpp src/innertube/objects/channel/aboutfullmetadata.h
    src/innertube/objects/channel/channel.h
    src/innertube/objects/channel/channelheader.cpp src/innertube/objects/channel/channelheader.h
    src/innertube/objects/channel/channelheaderlink.h
    src/innertube/objects/channel/channelmetadata.cpp src/innertube/objects/channel/channelmetadata.h
    src/innertube/objects/channel/metadatabadge.h
    src/innertube/objects/channel/microformatdata.cpp src/innertube/objects/channel/microformatdata.h
    src/innertube/objects/channel/notificationpreferencebutton.cpp src/innertube/objects/channel/notificationpreferencebutton.h
    src/innertube/objects/channel/notificationstate.h
    src/innertube/objects/channel/subscribebutton.h
    src/innertube/objects/items/button.h
    src/innertube/objects/items/menuflexibleitem.h
    src/innertube/objects/items/menuserviceitem.h
    src/innertube/objects/items/togglebutton.h
    src/innertube/objects/live_chat/livechat.cpp src/innertube/objects/live_chat/livechat.h
    src/innertube/objects/notification/notification.cpp src/innertube/objects/notification/notification.h
    src/innertube/objects/player/captiontrack.h
    src/innertube/objects/player/playbacktracking.h
    src/innertube/objects/player/playervideodetails.cpp src/innertube/objects/player/playervideodetails.h
    src/innertube/objects/player/streamingdata.cpp src/innertube/objects/player/streamingdata.h
    src/innertube/objects/player/streamingformat.h
    src/innertube/objects/video/primaryinfo/likedislike/dislikebuttonviewmodel.h
    src/innertube/objects/video/primaryinfo/likedislike/dynamiclikecountupdatedata.h
    src/innertube/objects/video/primaryinfo/likedislike/likebuttonviewmodel.h
    src/innertube/objects/video/primaryinfo/likedislike/likecountentity.h
    src/innertube/objects/video/primaryinfo/likedislike/likedislikeviewmodel.h
    src/innertube/objects/video/primaryinfo/videoactions.cpp src/innertube/objects/video/primaryinfo/videoactions.h
    src/innertube/objects/video/primaryinfo/videoprimaryinfo.h
    src/innertube/objects/video/primaryinfo/viewcount.h
    src/innertube/objects/video/reel.h
    src/innertube/objects/video/secondaryinfo/metadatarow.cpp src/innertube/objects/video/secondaryinfo/metadatarow.h
    src/innertube/objects/video/secondaryinfo/metadatarowcontainer.cpp src/innertube/objects/video/secondaryinfo/metadatarowcontainer.h
    src/innertube/objects/video/secondaryinfo/secondaryinfoowner.cpp src/innertube/objects/video/secondaryinfo/secondaryinfoowner.h
    src/innertube/objects/video/secondaryinfo/videosecondaryinfo.h
    src/innertube/objects/video/video.cpp src/innertube/objects/video/video.h
    src/innertube/objects/video/videoowner.cpp src/innertube/objects/video/videoowner.h
    src/innertube/objects/video/videothumbnail.h
    src/innertube/objects/viewmodels/buttonviewmodel.h
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
    src/innertube/responses/video/nextresponse.h
    src/innertube/responses/video/playerresponse.h
    src/innertube/responses/video/updatedmetadataresponse.h
    src/protobuf/simpleprotobuf.cpp src/protobuf/simpleprotobuf.h
)

target_include_directories(innertube-qt PUBLIC lib/verdigris/src)

# Define options in preprocessor
if(INNERTUBE_GET_STS)
    target_compile_definitions(innertube-qt PUBLIC INNERTUBE_GET_STS)
endif()

if(INNERTUBE_NO_WEBENGINE)
    target_compile_definitions(innertube-qt PUBLIC INNERTUBE_NO_WEBENGINE)
endif()

# Include directories, libraries
target_include_directories(innertube-qt PUBLIC src)
target_link_libraries(innertube-qt PUBLIC Qt::Core Qt::Gui Qt::Network)

## Optional
if(NOT INNERTUBE_NO_WEBENGINE)
    target_link_libraries(innertube-qt PUBLIC Qt::WebEngineWidgets)
endif()

install(TARGETS innertube-qt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
