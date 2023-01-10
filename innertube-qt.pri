QT *= network webenginewidgets
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
DEFINES += INNERTUBE
LIBS += -lcurl
include(lib/qtcurl/qtcurl.pri)

PRECOMPILED_HEADER = $$PWD/src/innertube/endpoints/innertubeendpoints.h

HEADERS += \
    $$PWD/src/innertube/endpoints/base/basebrowseendpoint.h \
    $$PWD/src/innertube/endpoints/base/baseendpoint.h \
    $$PWD/src/innertube/endpoints/browse/browsechannel.h \
    $$PWD/src/innertube/endpoints/browse/browseexplore.h \
    $$PWD/src/innertube/endpoints/browse/browsehistory.h \
    $$PWD/src/innertube/endpoints/browse/browsehome.h \
    $$PWD/src/innertube/endpoints/browse/browsehomeshelves.h \
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
    $$PWD/src/innertube/innertubeexception.h \
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
    $$PWD/src/innertube/objects/channel/searchchannel.h \
    $$PWD/src/innertube/objects/channel/subscribebutton.h \
    $$PWD/src/innertube/objects/genericthumbnail.h \
    $$PWD/src/innertube/objects/navigation/commandmetadata.h \
    $$PWD/src/innertube/objects/navigation/navigationbrowseendpoint.h \
    $$PWD/src/innertube/objects/navigation/navigationendpoint.h \
    $$PWD/src/innertube/objects/navigation/navigationsubscribeendpoint.h \
    $$PWD/src/innertube/objects/navigation/urlendpoint.h \
    $$PWD/src/innertube/objects/notification/notification.h \
    $$PWD/src/innertube/objects/player/captiontrack.h \
    $$PWD/src/innertube/objects/player/playbacktracking.h \
    $$PWD/src/innertube/objects/player/playervideodetails.h \
    $$PWD/src/innertube/objects/player/streamingdata.h \
    $$PWD/src/innertube/objects/player/streamingformat.h \
    $$PWD/src/innertube/objects/video/video.h \
    $$PWD/src/innertube/objects/video/videoowner.h \
    $$PWD/src/innertube/objects/video/videoprimaryinfo.h \
    $$PWD/src/innertube/objects/video/videosecondaryinfo.h \
    $$PWD/src/innertube/objects/video/videothumbnail.h \
    $$PWD/src/innertube/objects/innertubestring.h \
    $$PWD/src/innertube.h \
    $$PWD/src/innertube.tpp \
    $$PWD/src/innertube/responses/browse/channelresponse.h \
    $$PWD/src/innertube/responses/browse/historyresponse.h \
    $$PWD/src/innertube/responses/browse/homeresponse.h \
    $$PWD/src/innertube/responses/browse/homeshelvesresponse.h \
    $$PWD/src/innertube/responses/browse/subscriptionsresponse.h \
    $$PWD/src/innertube/responses/browse/trendingresponse.h \
    $$PWD/src/innertube/responses/misc/notificationmenuresponse.h \
    $$PWD/src/innertube/responses/misc/searchresponse.h \
    $$PWD/src/innertube/responses/video/nextresponse.h \
    $$PWD/src/innertube/responses/video/playerresponse.h \
    $$PWD/src/jsonutil.h \
    $$PWD/src/protobuf/simpleprotobuf.h

SOURCES += \
    $$PWD/src/innertube/endpoints/base/basebrowseendpoint.cpp \
    $$PWD/src/innertube/endpoints/base/baseendpoint.cpp \
    $$PWD/src/innertube/endpoints/browse/browsechannel.cpp \
    $$PWD/src/innertube/endpoints/browse/browsehistory.cpp \
    $$PWD/src/innertube/endpoints/browse/browsehome.cpp \
    $$PWD/src/innertube/endpoints/browse/browsehomeshelves.cpp \
    $$PWD/src/innertube/endpoints/browse/browsesubscriptions.cpp \
    $$PWD/src/innertube/endpoints/browse/browsetrending.cpp \
    $$PWD/src/innertube/endpoints/misc/accountmenu.cpp \
    $$PWD/src/innertube/endpoints/misc/getnotificationmenu.cpp \
    $$PWD/src/innertube/endpoints/misc/search.cpp \
    $$PWD/src/innertube/endpoints/misc/unseencount.cpp \
    $$PWD/src/innertube/endpoints/subscription/subscribe.cpp \
    $$PWD/src/innertube/endpoints/video/next.cpp \
    $$PWD/src/innertube/endpoints/video/player.cpp \
    $$PWD/src/innertube/itc-objects/innertubeauthstore.cpp \
    $$PWD/src/innertube/itc-objects/innertubeclient.cpp \
    $$PWD/src/innertube/itc-objects/innertubecontext.cpp \
    $$PWD/src/innertube/itc-objects/innertubeplaybackcontext.cpp \
    $$PWD/src/innertube/objects/channel/channelheader.cpp \
    $$PWD/src/innertube/objects/channel/searchchannel.cpp \
    $$PWD/src/innertube/objects/channel/subscribebutton.cpp \
    $$PWD/src/innertube/objects/innertubestring.cpp \
    $$PWD/src/innertube/objects/navigation/commandmetadata.cpp \
    $$PWD/src/innertube/objects/navigation/navigationsubscribeendpoint.cpp \
    $$PWD/src/innertube/objects/notification/notification.cpp \
    $$PWD/src/innertube/objects/player/playervideodetails.cpp \
    $$PWD/src/innertube/objects/player/streamingdata.cpp \
    $$PWD/src/innertube/objects/video/video.cpp \
    $$PWD/src/innertube/objects/video/videoowner.cpp \
    $$PWD/src/innertube/objects/video/videoprimaryinfo.cpp \
    $$PWD/src/innertube/objects/video/videosecondaryinfo.cpp \
    $$PWD/src/jsonutil.cpp \
    $$PWD/src/protobuf/simpleprotobuf.cpp
