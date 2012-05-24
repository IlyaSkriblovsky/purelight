#!/bin/sh

if pkill purelight; then
    echo "killed"
    cat /opt/purelight/off.desktop >/usr/share/applications/purelight.desktop
else
    echo "starting"
    cat /opt/purelight/on.desktop >/usr/share/applications/purelight.desktop
    /opt/purelight/purelight
fi
