# innertube-qt
A Qt library to interface with YouTube's InnerTube API.

## How To Use
This library is best used as a Git submodule. Here's the recommended way to do so:
<br><br>
Start by adding the library to your project in the "lib" subdirectory:
```
git submodule add -b master https://github.com/BowDown097/innertube-qt lib/innertube-qt
```
Then reference it in your project's .pro file:
```qmake
include(lib/innertube-qt/innertube-qt.pri)
```
And that's all! Quite simple, isn't it?

## Building without WebEngine
If you are not going to use the authentication features of this library, or just really want to disable WebEngine and do authentication manually, you can simply change ``DEFINES += INNERTUBE`` at the top of the ``innertube-qt.pri`` file to ``DEFINES += INNERTUBE INNERTUBE_NO_WEBENGINE`` and you should be good to go.
