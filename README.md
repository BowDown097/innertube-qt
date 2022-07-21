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
