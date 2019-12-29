#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

# Defaults
export EDITOR="vim"
export TERMINAL="st"
export BROWSER="firefox-developer-edition"

# If in tty1 and window manager not running, run xinitrc(startx)
[ "$(tty)" = "/dev/tty1" ] && ! pgrep -x dwm >/dev/null && exec startx -- vt1 &> /dev/null
