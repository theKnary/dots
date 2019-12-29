#!/bin/sh
# runs when startx is called

# check .dwm/autostart.sh for what dwm auto starts

# hide cursor when there is keyboard input (not if mod key)
xbanish -i mod4 &
# set auto keyboard repeat to shorter delay and higher speed
xset r rate 220 40
# start screensaver
xscreensaver &
# finally, start the WM
exec dwm
