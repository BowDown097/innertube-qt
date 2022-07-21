QT *= network webenginewidgets
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
DEFINES += INNERTUBE

HEADERS += \
    $$PWD/src/endpoints/accountmenu.h \
    $$PWD/src/endpoints/baseendpoint.h \
    $$PWD/src/endpoints/browse.h \
    $$PWD/src/endpoints/innertubeendpoints.h \
    $$PWD/src/itc-objects/innertubeauthstore.h \
    $$PWD/src/itc-objects/innertubeclicktracking.h \
    $$PWD/src/itc-objects/innertubeclient.h \
    $$PWD/src/itc-objects/innertubeconfiginfo.h \
    $$PWD/src/itc-objects/innertubecontext.h \
    $$PWD/src/itc-objects/innertuberequestconfig.h \
    $$PWD/src/itc-objects/innertubeuserconfig.h \
    $$PWD/src/innertube.hpp
