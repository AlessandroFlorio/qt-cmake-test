# qt-cmake-test

Build testPlugin first, then build and execute testApp.

Tested on Linux Mint 22 Cinnamon and Android 11, compiled with Qt 6.8.2

The QML file is loaded in the main window and describes what is expected to be shown. On linux both tests pass, while on Android the plugin seems not to be loaded, although the library is available.
