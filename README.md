# innertube-qt
A Qt library to interface with YouTube's InnerTube API.

## Building without WebEngine
If you are not going to use the authentication features of this library, or just really want to disable WebEngine and do authentication manually, you can simply change ``DEFINES += INNERTUBE`` at the top of the ``innertube-qt.pri`` file to ``DEFINES += INNERTUBE INNERTUBE_NO_WEBENGINE`` and you should be good to go.
