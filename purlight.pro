TEMPLATE = app

QT =

LIBS = -lX11

SOURCES = main.cpp


target.path = /opt/purelight/
INSTALLS += target


startstop.files = startstop.sh
startstop.path = /opt/purelight/
INSTALLS += startstop


desktop.files = purelight.desktop
desktop.path = /usr/share/applications
INSTALLS += desktop


onoff.files = on.desktop off.desktop
onoff.path = /opt/purelight/
INSTALLS += onoff


icons.files = purelight-on.png purelight-off.png
icons.path = /usr/share/icons/hicolor/64x64/apps
INSTALLS += icons
