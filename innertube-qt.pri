QT *= network webenginewidgets
INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src
DEFINES += INNERTUBE

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
    $$PWD/src/endpoints/accountmenu.h \
    $$PWD/src/endpoints/innertubeendpoints.h \
    $$PWD/src/itc-objects/innertubeauthstore.h \
    $$PWD/src/itc-objects/innertubeclicktracking.h \
    $$PWD/src/itc-objects/innertubeclient.h \
    $$PWD/src/itc-objects/innertubeconfiginfo.h \
    $$PWD/src/itc-objects/innertubecontext.h \
    $$PWD/src/itc-objects/innertuberequestconfig.h \
    $$PWD/src/itc-objects/innertubeuserconfig.h \
    $$PWD/src/innertube.hpp
