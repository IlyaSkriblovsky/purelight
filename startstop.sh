#!/bin/sh

if pkill flashtest; then
    echo "killed"
    cat /opt/flashtest/off.desktop >/usr/share/applications/flashtest.desktop
else
    echo "starting"
    cat /opt/flashtest/on.desktop >/usr/share/applications/flashtest.desktop
    /opt/flashtest/flashtest
fi
