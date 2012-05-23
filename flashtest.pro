TEMPLATE = app

QT =

LIBS = -lX11

SOURCES = main.cpp


target.path = /opt/flashtest/
INSTALLS += target


startstop.files = startstop.sh
startstop.path = /opt/flashtest/
INSTALLS += startstop


desktop.files = flashtest.desktop
desktop.path = /usr/share/applications
INSTALLS += desktop


onoff.files = on.desktop off.desktop
onoff.path = /opt/flashtest/
INSTALLS += onoff


icons.files = flashtest-on.png flashtest-off.png
icons.path = /usr/share/icons/hicolor/64x64/apps
INSTALLS += icons
