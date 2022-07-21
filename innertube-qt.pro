TEMPLATE = lib
include(innertube-qt.pri)

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
