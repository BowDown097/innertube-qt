QT *= network webenginewidgets
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
DEFINES += INNERTUBE
LIBS += -lcurl
include(lib/qtcurl/qtcurl.pri)

PRECOMPILED_HEADER = $$PWD/src/endpoints/innertubeendpoints.h

HEADERS += \
    $$PWD/src/endpoints/base/basebrowseendpoint.h \
    $$PWD/src/endpoints/base/baseendpoint.h \
    $$PWD/src/endpoints/browse/browsechannel.h \
    $$PWD/src/endpoints/browse/browseexplore.h \
    $$PWD/src/endpoints/browse/browsehistory.h \
    $$PWD/src/endpoints/browse/browsehome.h \
    $$PWD/src/endpoints/browse/browselibrary.h \
    $$PWD/src/endpoints/browse/browsestorefront.h \
    $$PWD/src/endpoints/browse/browsesubscriptions.h \
    $$PWD/src/endpoints/browse/browsetrending.h \
    $$PWD/src/endpoints/misc/accountmenu.h \
    $$PWD/src/endpoints/misc/search.h \
    $$PWD/src/endpoints/video/next.h \
    $$PWD/src/endpoints/video/player.h \
    $$PWD/src/endpoints/innertubeendpoints.h \
    $$PWD/src/itc-objects/innertubeauthstore.h \
    $$PWD/src/itc-objects/innertubeclicktracking.h \
    $$PWD/src/itc-objects/innertubeclient.h \
    $$PWD/src/itc-objects/innertubeconfiginfo.h \
    $$PWD/src/itc-objects/innertubecontext.h \
    $$PWD/src/itc-objects/innertubeplaybackcontext.h \
    $$PWD/src/itc-objects/innertuberequestconfig.h \
    $$PWD/src/itc-objects/innertubeuserconfig.h \
    $$PWD/src/objects/channel/channel.h \
    $$PWD/src/objects/genericthumbnail.h \
    $$PWD/src/objects/video/video.h \
    $$PWD/src/objects/video/videoowner.h \
    $$PWD/src/objects/video/videothumbnail.h \
    $$PWD/src/objects/innertubestring.h \
    $$PWD/src/innertube.hpp \
    $$PWD/src/innertubeexception.hpp
