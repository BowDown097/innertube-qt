QT *= network
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
DEFINES += INNERTUBE
CONFIG += c++2a

# WINDOWS USERS (windrones): PLEASE refer to build_instructions.md if you haven't already. You'll probably get some error here if you don't.
!win32: LIBS += -lcurl
win32: CONFIG += link_pkgconfig
win32: PKGCONFIG += libcurl

include(lib/qtcurl/qtcurl.pri)

!contains(DEFINES, NO_WEBENGINE) {
    QT *= webenginewidgets
}

PRECOMPILED_HEADER = $$PWD/src/innertube/endpoints/innertubeendpoints.h

HEADERS += \
    $$PWD/src/innertube/endpoints/base/basebrowseendpoint.h \
    $$PWD/src/innertube/endpoints/base/baseendpoint.h \
    $$PWD/src/innertube/endpoints/browse/browsechannel.h \
    $$PWD/src/innertube/endpoints/browse/browseexplore.h \
    $$PWD/src/innertube/endpoints/browse/browsehistory.h \
    $$PWD/src/innertube/endpoints/browse/browsehome.h \
    $$PWD/src/innertube/endpoints/browse/browselibrary.h \
    $$PWD/src/innertube/endpoints/browse/browsestorefront.h \
    $$PWD/src/innertube/endpoints/browse/browsesubscriptions.h \
    $$PWD/src/innertube/endpoints/browse/browsetrending.h \
    $$PWD/src/innertube/endpoints/misc/accountmenu.h \
    $$PWD/src/innertube/endpoints/misc/getnotificationmenu.h \
    $$PWD/src/innertube/endpoints/misc/search.h \
    $$PWD/src/innertube/endpoints/misc/unseencount.h \
    $$PWD/src/innertube/endpoints/subscription/subscribe.h \
    $$PWD/src/innertube/endpoints/video/next.h \
    $$PWD/src/innertube/endpoints/video/player.h \
    $$PWD/src/innertube/endpoints/innertubeendpoints.h \
    $$PWD/src/innertube/endpoints/video/updatedmetadata.h \
    $$PWD/src/innertube/innertubeexception.h \
    $$PWD/src/innertube/innertubereply.h \
    $$PWD/src/innertube/itc-objects/innertubeauthstore.h \
    $$PWD/src/innertube/itc-objects/innertubeclicktracking.h \
    $$PWD/src/innertube/itc-objects/innertubeclient.h \
    $$PWD/src/innertube/itc-objects/innertubeconfiginfo.h \
    $$PWD/src/innertube/itc-objects/innertubecontext.h \
    $$PWD/src/innertube/itc-objects/innertubeplaybackcontext.h \
    $$PWD/src/innertube/itc-objects/innertuberequestconfig.h \
    $$PWD/src/innertube/itc-objects/innertubeuserconfig.h \
    $$PWD/src/innertube/objects/channel/channelheader.h \
    $$PWD/src/innertube/objects/channel/channelheaderlink.h \
    $$PWD/src/innertube/objects/channel/channelmetadata.h \
    $$PWD/src/innertube/objects/channel/metadatabadge.h \
    $$PWD/src/innertube/objects/channel/microformatdata.h \
    $$PWD/src/innertube/objects/channel/searchchannel.h \
    $$PWD/src/innertube/objects/channel/subscribebutton.h \
    $$PWD/src/innertube/objects/genericthumbnail.h \
    $$PWD/src/innertube/objects/items/button.h \
    $$PWD/src/innertube/objects/items/menuflexibleitem.h \
    $$PWD/src/innertube/objects/items/menuserviceitem.h \
    $$PWD/src/innertube/objects/items/togglebutton.h \
    $$PWD/src/innertube/objects/notification/notification.h \
    $$PWD/src/innertube/objects/player/captiontrack.h \
    $$PWD/src/innertube/objects/player/playbacktracking.h \
    $$PWD/src/innertube/objects/player/playervideodetails.h \
    $$PWD/src/innertube/objects/player/streamingdata.h \
    $$PWD/src/innertube/objects/player/streamingformat.h \
    $$PWD/src/innertube/objects/video/primaryinfo/videoactions.h \
    $$PWD/src/innertube/objects/video/primaryinfo/videoprimaryinfo.h \
    $$PWD/src/innertube/objects/video/secondaryinfo/metadatarow.h \
    $$PWD/src/innertube/objects/video/secondaryinfo/metadatarowcontainer.h \
    $$PWD/src/innertube/objects/video/secondaryinfo/secondaryinfoowner.h \
    $$PWD/src/innertube/objects/video/secondaryinfo/videosecondaryinfo.h \
    $$PWD/src/innertube/objects/video/video.h \
    $$PWD/src/innertube/objects/video/videoowner.h \
    $$PWD/src/innertube/objects/video/videothumbnail.h \
    $$PWD/src/innertube/objects/innertubestring.h \
    $$PWD/src/innertube.h \
    $$PWD/src/innertube.tpp \
    $$PWD/src/innertube/responses/browse/channelresponse.h \
    $$PWD/src/innertube/responses/browse/historyresponse.h \
    $$PWD/src/innertube/responses/browse/homeresponse.h \
    $$PWD/src/innertube/responses/browse/subscriptionsresponse.h \
    $$PWD/src/innertube/responses/browse/trendingresponse.h \
    $$PWD/src/innertube/responses/misc/notificationmenuresponse.h \
    $$PWD/src/innertube/responses/misc/searchresponse.h \
    $$PWD/src/innertube/responses/video/nextresponse.h \
    $$PWD/src/innertube/responses/video/playerresponse.h \
    $$PWD/src/innertube/responses/video/updatedmetadataresponse.h \
    $$PWD/src/jsonutil.h \
    $$PWD/src/protobuf/simpleprotobuf.h

SOURCES += \
    $$PWD/src/innertube/endpoints/base/basebrowseendpoint.cpp \
    $$PWD/src/innertube/endpoints/base/baseendpoint.cpp \
    $$PWD/src/innertube/endpoints/browse/browsechannel.cpp \
    $$PWD/src/innertube/endpoints/browse/browsehistory.cpp \
    $$PWD/src/innertube/endpoints/browse/browsehome.cpp \
    $$PWD/src/innertube/endpoints/browse/browsesubscriptions.cpp \
    $$PWD/src/innertube/endpoints/browse/browsetrending.cpp \
    $$PWD/src/innertube/endpoints/misc/accountmenu.cpp \
    $$PWD/src/innertube/endpoints/misc/getnotificationmenu.cpp \
    $$PWD/src/innertube/endpoints/misc/search.cpp \
    $$PWD/src/innertube/endpoints/misc/unseencount.cpp \
    $$PWD/src/innertube/endpoints/subscription/subscribe.cpp \
    $$PWD/src/innertube/endpoints/video/next.cpp \
    $$PWD/src/innertube/endpoints/video/player.cpp \
    $$PWD/src/innertube/endpoints/video/updatedmetadata.cpp \
    $$PWD/src/innertube/itc-objects/innertubeauthstore.cpp \
    $$PWD/src/innertube/itc-objects/innertubeclient.cpp \
    $$PWD/src/innertube/itc-objects/innertubecontext.cpp \
    $$PWD/src/innertube/itc-objects/innertubeplaybackcontext.cpp \
    $$PWD/src/innertube/objects/channel/channelheader.cpp \
    $$PWD/src/innertube/objects/channel/channelmetadata.cpp \
    $$PWD/src/innertube/objects/channel/microformatdata.cpp \
    $$PWD/src/innertube/objects/channel/searchchannel.cpp \
    $$PWD/src/innertube/objects/innertubestring.cpp \
    $$PWD/src/innertube/objects/notification/notification.cpp \
    $$PWD/src/innertube/objects/player/playervideodetails.cpp \
    $$PWD/src/innertube/objects/player/streamingdata.cpp \
    $$PWD/src/innertube/objects/video/primaryinfo/videoactions.cpp \
    $$PWD/src/innertube/objects/video/secondaryinfo/metadatarow.cpp \
    $$PWD/src/innertube/objects/video/secondaryinfo/metadatarowcontainer.cpp \
    $$PWD/src/innertube/objects/video/secondaryinfo/secondaryinfoowner.cpp \
    $$PWD/src/innertube/objects/video/video.cpp \
    $$PWD/src/innertube/objects/video/videoowner.cpp \
    $$PWD/src/jsonutil.cpp \
    $$PWD/src/protobuf/simpleprotobuf.cpp
