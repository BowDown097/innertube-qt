Getting this working is incredibly simple on everything BUT Windows. Here's how to get this guy set up:

## Linux
All you need is curl and Qt6 WebEngine.  
On Arch-based distros, the packages for these, respectively, will be:
- curl (there's no way you don't have this)
- qt6-webengine

For other distros, just look up the equivalents.

## macOS
You shouldn't have to do anything here at all. Just make sure you have curl and Qt6 WebEngine (the Homebrew version of Qt at least comes bundled with these).

## Windows
**Gonna break you some bad news. If you have WebEngine enabled in this build, you can't use the MinGW version of Qt to build this. It does not support WebEngine.** With that out of the way, this is a pain in the ass to get set up on Windows, because of course it is. As I don't use Windows, these instructions are essentially untested. Good luck, soldier.
- [Install vcpkg if you haven't already.](https://vcpkg.io/en/getting-started.html)
- If you are building under a 32-bit version of Qt, run ``vcpkg install curl``. If you are building under a 64-bit version of Qt, run ``vcpkg install curl:x64-windows``. Yes, it still assumes 32-bit by default in current year.
- Navigate to ``Projects > Build Environment`` and click the Details dropdown. Press Add.
- In your new entry, change ``<VARIABLE>`` to ``PKG_CONFIG_PATH`` and change ``<VALUE>`` to something along the lines of ``<vcpkg>/installed/x64-windows/lib/pkgconfig``, where \<vcpkg\> is, obviously, your vcpkg directory.
- Pray to God it works.

## Building without WebEngine
If you are not going to use the authentication features of this library, or just really want to disable WebEngine and do authentication manually, you can simply change ``DEFINES += INNERTUBE`` at the top of the ``innertube-qt.pri`` file to ``DEFINES += INNERTUBE NO_WEBENGINE`` and you should be good to go.
